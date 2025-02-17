// Including header files and Namespace
#include <bits/stdc++.h>
using namespace std;

// Counter to keep track of stages explored
int counter = 0;

// Initialising the goal state
const vector<vector<int>> goal = {
    {1, 2, 3},
    {8, 0, 4},
    {7, 6, 5}
};

// Function to print the puzzle
void printPuzzle(const vector<vector<int>>& state) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << state[i][j] << " ";
        cout << endl;
    }
    cout << "-------------\n";
}

// Function to provide co-ordinates of '0'
pair<int, int> findBlank(const vector<vector<int>>& state) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; ++j) {
            if (state[i][j] == 0)
                return {i, j};
        }
    }
    return {-1, -1}; // Impossible 
}

// Function to check if the state is the goal state
bool isGoal(const vector<vector<int>>& state) {
    counter++;
    return state == goal;
}

// To generate all possible moves from the current state
vector<vector<vector<int>>> getNeighbors(const vector<vector<int>>& state) {
    
    vector<vector<vector<int>>> neighbors;
    pair<int, int> blank = findBlank(state);
    int x = blank.first;
    int y = blank.second;

    // Possible moves (up, down, left, right) for 0
    vector<pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (const auto& move : moves) {
        int nx = x + move.first;
        int ny = y + move.second;

        // Checking if the move is within the board and is not illegal
        if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
            vector<vector<int>> newState = state;
            swap(newState[x][y], newState[nx][ny]);
            neighbors.push_back(newState);
        }
    }
    return neighbors;
}

// BFS implementation
void solvePuzzle(const vector<vector<int>>& initial) {
    queue<vector<vector<int>>> q;

    // To track the visited nodes
    vector<vector<vector<int>>> visited;
    
    // To track parent child relation
    vector<pair<vector<vector<int>>, vector<vector<int>>>> parent;

    // Start of BFS
    q.push(initial);
    visited.push_back(initial);

    // Root will have no parent
    parent.push_back({initial, {}}); 

    while (!q.empty()) {
        vector<vector<int>> current = q.front();
        q.pop();

        // Checking if goal is reached
        if (isGoal(current)) {
            cout << "Goal state reached!" << endl;

            // Counting the number of moves
            int steps = 0;
            while (true) {
                auto it = find_if(parent.begin(), parent.end(), [&](const auto& p) {
                    return p.first == current;
                });

                if (it == parent.end() || it->second.empty())
                    break;

                current = it->second;
                steps++;
            }

            printPuzzle(goal);
            cout << "\nNo. of moves: " << steps << endl;
            return;
        }

        // Explore neighbors
        for (const auto& neighbor : getNeighbors(current)) {
            if (find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                q.push(neighbor);
                visited.push_back(neighbor);
                parent.push_back({neighbor, current}); // To track the parent
            }
        }
    }

    cout << "No solution found for this initial state!" << endl;
}

int main() {
    vector<vector<int>> initial(3, vector<int>(3));
    
    cout << "Enter the initial state matrix:" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> initial[i][j];
        }
    }

    cout << "\nInitial State:" << endl;
    printPuzzle(initial);

    cout << "\nWork in progess...\n" << endl;
    cout << "-------------\n";
    solvePuzzle(initial);
    cout << "States Explored = " << counter;
    return 0;
}