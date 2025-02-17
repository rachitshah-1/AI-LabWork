#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <unordered_set>

using namespace std;

void findAllPaths(const unordered_map<int, vector<int>> &graph, int source, int destination, vector<int> &path, vector<vector<int>> &allPaths, unordered_map<int, bool> &visited) {
    visited[source] = true;
    path.push_back(source);

    if (source == destination) {
        allPaths.push_back(path);
    } else {
        for (int neighbor : graph.at(source)) {
            if (!visited[neighbor]) {
                findAllPaths(graph, neighbor, destination, path, allPaths, visited);
            }
        }
    }

    path.pop_back();
    visited[source] = false;
}

bool hasCycleUtil(const unordered_map<int, vector<int>> &graph, int node, unordered_map<int, bool> &visited, int parent) {
    visited[node] = true;

    for (int neighbor : graph.at(node)) {
        if (!visited[neighbor]) {
            if (hasCycleUtil(graph, neighbor, visited, node)) {
                return true;
            }
        } else if (neighbor != parent) {
            return true;
        }
    }

    return false;
}

bool hasCycle(const unordered_map<int, vector<int>> &graph) {
    unordered_map<int, bool> visited;

    for (const auto &node : graph) {
        if (!visited[node.first]) {
            if (hasCycleUtil(graph, node.first, visited, -1)) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    unordered_map<int, vector<int>> graph = {
        {0, {1, 2}},
        {1, {0, 2, 3}},
        {2, {0, 1, 4}},
        {3, {1, 4}},
        {4, {2, 3}}
    };

    int source, destination;
    cout << "Enter source node: ";
    cin >> source;
    cout << "Enter destination node: ";
    cin >> destination;

    if (graph.find(source) == graph.end() || graph.find(destination) == graph.end()) {
        cout << "Source or destination node does not exist in the graph." << endl;
        return 1;
    }

    if (hasCycle(graph)) {
        cout << "The graph contains a cycle." << endl;
    } else {
        cout << "The graph does not contain any cycles." << endl;
    }

    vector<int> path;
    vector<vector<int>> allPaths;
    unordered_map<int, bool> visited;

    findAllPaths(graph, source, destination, path, allPaths, visited);

    if (allPaths.empty()) {
        cout << "No paths exist from " << source << " to " << destination << "." << endl;
    } else {
        cout << "All paths from " << source << " to " << destination << ":" << endl;
        for (const auto &p : allPaths) {
            for (size_t i = 0; i < p.size(); ++i) {
                cout << p[i];
                if (i < p.size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    }

    return 0;
}
