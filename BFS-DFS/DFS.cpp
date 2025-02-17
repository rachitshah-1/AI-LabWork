#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

bool dfs(const unordered_map<int, vector<int>> &graph, int current, int destination, unordered_map<int, bool> &visited, unordered_map<int, int> &parent) {
    visited[current] = true;

    // End search if current node is destination node
    if (current == destination) {
        return true;
    }

    // Explore node which are adajcent
    for (int neighbor : graph.at(current)) {
        if (!visited[neighbor]) {
            // Parent tracking
            parent[neighbor] = current;
            if (dfs(graph, neighbor, destination, visited, parent)) {
                //Return when the path is found
                return true;
            }
        }
    }
    // No path in this route
    return false;
}

void findPathDFS(const unordered_map<int, vector<int>> &graph, int source, int destination) {
    
    // For tracking of the visited nodes
    unordered_map<int, bool> visited;

    // For storing parent child relation
    unordered_map<int, int> parent;

    parent[source] = -1;

    // DFS to check for a path
    if (dfs(graph, source, destination, visited, parent)) {
        stack<int> path;
        int current = destination;
        // Travel from destination to parent
        while (current != -1) {
            path.push(current); 
            current = parent[current];
        }

        // Printing path from Source to Destination
        cout << "Path from " << source << " to " << destination << ": ";
        while (!path.empty()) {
            cout << path.top();
            path.pop();
            if (!path.empty()) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "No path exists from " << source << " to " << destination << "." << endl;
    }
}

int main() {
    // Graph 
    unordered_map<int, vector<int>> graph = {
        {0, {1, 2}},
        {1, {0, 2, 3}},
        {2, {0, 1, 4}},
        {3, {1, 4}},
        {4, {2, 3}}
    };

    // Input of source and destination
    int source, destination;
    cout << "Enter source node: ";
    cin >> source;
    cout << "Enter destination node: ";
    cin >> destination;

    // Checking if source and destination exists
    if (graph.find(source) == graph.end() || graph.find(destination) == graph.end()) {
        cout << "Source or destination node does not exist." << endl;
        return 1;
    }

    // Finding and printing path using DFS
    findPathDFS(graph, source, destination);

    return 0;
}
