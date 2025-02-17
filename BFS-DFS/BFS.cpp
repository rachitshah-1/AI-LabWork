#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

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
        cout << "Source or destination node does not exist." << endl;
        return 1;
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