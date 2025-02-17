#include <bits/stdc++.h>
using namespace std;

// Counter to keep track of stages explored
int counter = 0;

// Possible moves (up, down, left, right) for 0
const vector<vector<int>> DIRECTIONS = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
const string GOAL = "123804765";

// Count inversions in a 1D vector (ignoring 0)
int countInversions(const vector<int>& puzzle) {
    int invCount = 0;
    int n = puzzle.size();
    for (int i = 0; i < n; i++) {
        if (puzzle[i] == 0) continue;
        for (int j = i + 1; j < n; j++) {
            if (puzzle[j] != 0 && puzzle[i] > puzzle[j])
                invCount++;
        }
    }
    return invCount;
}

// To check if a given puzzle state is solvable
bool isSolvable(const vector<int>& initPuzzle, const vector<int>& goalPuzzle) {
    int initInv = countInversions(initPuzzle);
    int goalInv = countInversions(goalPuzzle);
    // Puzzle is solvable if inversion parities match
    return (initInv % 2 == goalInv % 2);
}

// Heuristic: Manhattan distance
int heuristic(const string& state) {
    int distance = 0;
    vector<pair<int, int>> goalPos(9);
    // Converting string into matrix
    for (int i = 0; i < 9; i++) {
        int num = GOAL[i] - '0';
        goalPos[num] = make_pair(i / 3, i % 3);
    }
    for (int i = 0; i < 9; i++) {
        int num = state[i] - '0';
        if (num != 0)
            // Calculating distance if number is not 0
            distance += abs(goalPos[num].first - i / 3) + abs(goalPos[num].second - i % 3);
    }
    return distance;
}

// To Check if the move is within the board and is not illegal
bool isValid(int x, int y) {
    return x >= 0 && x < 3 && y >= 0 && y < 3;
}

// Conversion into string
string matrixToString(const vector<vector<int>>& matrix) {
    string result;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result += to_string(matrix[i][j]);
    return result;
}

// To swap numbers in string format itself
string swapBox(const string& state, int x1, int y1, int x2, int y2) {
    string nextState = state;
    int idx1 = x1 * 3 + y1;
    int idx2 = x2 * 3 + y2;
    swap(nextState[idx1], nextState[idx2]);
    return nextState;
}

// To print state
void printState(const string& state) {
    for (int i = 0; i < (int)state.size(); i++) {
        if (i > 0 && i % 3 == 0) cout << endl;
        cout << state[i] << " ";
    }
    cout << "\n------";
    cout << endl;
}

// To print the reconstructed path
void printSolution(int goalIndex, const vector<string>& states, const vector<int>& parent) {
    vector<string> path;
    int current = goalIndex;
    while (current != -1) {
        path.push_back(states[current]);
        current = parent[current];
    }
    reverse(path.begin(), path.end());
    for (const auto &s : path) {
        printState(s);
        cout << endl;
    }
    cout << "Number of steps required: " << path.size() - 1 << endl;
}

// Implementation of A*
void solveKaro(const vector<vector<int>>& start) {

    // Convert start matrix into a vector for inversion counting.
    vector<int> initPuzzle;
    for (const auto &row : start)
        for (int num : row)
            initPuzzle.push_back(num);
            
    // Convert goal state string into a vector.
    vector<int> goalPuzzle;
    for (char ch : GOAL)
        goalPuzzle.push_back(ch - '0');

    // Check solvability
    if (!isSolvable(initPuzzle, goalPuzzle)) {
        cout << "The given puzzle is unsolvable." << endl;
        return;
    }
    
    // Representation of initial state
    string startState = matrixToString(start);
    
    // (f = g + heuristic, g, state index)
    typedef tuple<int, int, int> Node;

    // To order nodes by the smallest 'f' value using greater<Node>
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    // To map state string to its respective State index
    unordered_map<string, int> stateIndex;

    // To store all the state strings ever encountered
    vector<string> states;

    // Cost to reach each state
    vector<int> g_values;
    
    // To store parent index of the state
    vector<int> parent;
    
    // Entering the start state in the priority queue
    states.push_back(startState);
    g_values.push_back(0);
    parent.push_back(-1);
    stateIndex[startState] = 0;
    pq.push(make_tuple(heuristic(startState), 0, 0));
    
    // Closed set to avoid re-exploring states.
    unordered_set<string> closed;

    // A* Loop
    while (!pq.empty()) {
        int f, g, currentIdx;
        // Node with the smallest 'f' is popped
        tie(f, g, currentIdx) = pq.top();
        pq.pop();
        
        // Checking if the state is in the closed list 
        string currentState = states[currentIdx];
        if (closed.find(currentState) != closed.end())
            continue;
        closed.insert(currentState);
        
        // Checking for the current state to be the goal state
        if (currentState == GOAL) {
            printSolution(currentIdx, states, parent);
            cout << "Goal state reached Successfully!" << endl;
            return;
        }
        
        // Finding 0 in the current state string
        int zeroIndex = currentState.find('0');
        // Getting its co-ordinates
        int x = zeroIndex / 3, y = zeroIndex % 3;
        
        // Move in possible 4 directions and check and update f,g,h
        for (int i = 0; i < 4; i++) {
            int newX = x + DIRECTIONS[i][0];
            int newY = y + DIRECTIONS[i][1];
            
            if (isValid(newX, newY)) {
                string nextState = swapBox(currentState, x, y, newX, newY);
                int newG = g + 1;
                int newF = newG + heuristic(nextState);
                counter++;
                
                // New state found then add it in the list and queue
                if (stateIndex.find(nextState) == stateIndex.end()) {
                    int newIdx = states.size();
                    states.push_back(nextState);
                    g_values.push_back(newG);
                    parent.push_back(currentIdx);
                    stateIndex[nextState] = newIdx;
                    pq.push(make_tuple(newF, newG, newIdx));
                } else {
                    // Old state but lower cost so reconsidering 
                    int existingIdx = stateIndex[nextState];
                    if (newG < g_values[existingIdx]) {
                        g_values[existingIdx] = newG;
                        parent[existingIdx] = currentIdx;
                        pq.push(make_tuple(newF, newG, existingIdx));
                    }
                }
            }
        }
    }
    cout << "No solution found:(" << endl;
}

int main() {
    // vector<vector<int>> start = {
    //     {8, 3, 5},
    //     {4, 1, 6},
    //     {2, 7, 0}
    // };

    vector<vector<int>> start(3, vector<int>(3));
    
    cout << "Enter the initial state matrix:" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> start[i][j];
        }
    }

    // Printing start state
    cout << "Initial state:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << start[i][j];
            cout << " ";
        }
        cout << "\n";
    }
    cout << endl;
    solveKaro(start);
    cout << "States Explored = " << counter;
    return 0;
}