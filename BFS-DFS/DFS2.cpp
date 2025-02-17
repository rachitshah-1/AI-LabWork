#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void findAllPathsDFS(const unordered_map<int, vector<int>> &graph, int current, int destination, vector<int> &path, vector<vector<int>> &allPaths, unordered_map<int, bool> &visited) {
    visited[current] = true;
    path.push_back(current);
    
    if (current == destination) {
        allPaths.push_back(path);
    } else {
        for (int neighbor : graph.at(current)) {
            if (!visited[neighbor]) {
                findAllPathsDFS(graph, neighbor, destination, path, allPaths, visited);
            }
        }
    }

    path.pop_back();
    visited[current] = false;
}

void findPaths(const unordered_map<int, vector<int>> &graph, int source, int destination) {
    vector<int> path;
    vector<vector<int>> allPaths;
    unordered_map<int, bool> visited;

    findAllPathsDFS(graph, source, destination, path, allPaths, visited);

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

    findPaths(graph, source, destination);

    return 0;
}
