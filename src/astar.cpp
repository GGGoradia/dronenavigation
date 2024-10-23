#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
using namespace std;

struct Node {
    int x, y;
    double g, h, f;  // g: cost from start, h: heuristic, f: total cost (g + h)
    Node* parent;
    
    bool operator<(const Node& other) const {
        return f > other.f;  // for priority queue (min-heap)
    }
};

// Heuristic (Manhattan Distance)
double heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// A* algorithm implementation
vector<pair<int, int>> aStar(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal) {
    priority_queue<Node> openSet;
    vector<vector<bool>> closedSet(grid.size(), vector<bool>(grid[0].size(), false));
    vector<pair<int, int>> path;
    
    openSet.push({start.first, start.second, 0, heuristic(start.first, start.second, goal.first, goal.second), 0, nullptr});
    
    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();
        
        if (current.x == goal.first && current.y == goal.second) {
            // Path found, trace back using parent pointers
            while (current.parent != nullptr) {
                path.push_back({current.x, current.y});
                current = *current.parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }
        
        closedSet[current.x][current.y] = true;
        
        // Explore neighbors (up, down, left, right)
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (auto& d : directions) {
            int nx = current.x + d.first;
            int ny = current.y + d.second;
            
            if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() && grid[nx][ny] != -1 && !closedSet[nx][ny]) {
                double gScore = current.g + 1;
                double hScore = heuristic(nx, ny, goal.first, goal.second);
                openSet.push({nx, ny, gScore, hScore, gScore + hScore, new Node(current)});
            }
        }
    }
    
    return {};  // No path found
}

// Save the path to a CSV file
void savePathToCSV(const vector<pair<int, int>>& path, const string& filename) {
    ofstream file(filename);
    for (const auto& p : path) {
        file << p.first << "," << p.second << "\n";
    }
    file.close();
}

int main() {
    // Example 5x5 grid with obstacles (-1 represents an obstacle)
    vector<vector<int>> grid = {
        { 0,  0,  0, -1,  0},
        { 0, -1,  0, -1,  0},
        { 0, -1,  0,  0,  0},
        { 0,  0,  0, -1,  0},
        { 0,  0,  0,  0,  0}
    };
    
    pair<int, int> start = {0, 0};
    pair<int, int> goal = {4, 4};
    
    vector<pair<int, int>> path = aStar(grid, start, goal);
    savePathToCSV(path, "../output/a_star_path.csv");

    return 0;
}
