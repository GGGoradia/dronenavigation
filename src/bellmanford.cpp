#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>

using namespace std;

const double INF = numeric_limits<double>::infinity();

// Bellman-Ford algorithm implementation
vector<pair<int, int>> bellmanFord(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal) {
    int rows = grid.size();
    int cols = grid[0].size();
    
    vector<vector<double>> dist(rows, vector<double>(cols, INF));
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));
    
    dist[start.first][start.second] = 0;
    
    // Relax edges up to (rows * cols - 1) times
    for (int i = 0; i < rows * cols - 1; i++) {
        for (int x = 0; x < rows; x++) {
            for (int y = 0; y < cols; y++) {
                if (grid[x][y] == -1) continue;  // Skip obstacles
                
                vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                for (auto& d : directions) {
                    int nx = x + d.first;
                    int ny = y + d.second;
                    
                    if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] != -1) {
                        double newDist = dist[x][y] + 1;
                        if (newDist < dist[nx][ny]) {
                            dist[nx][ny] = newDist;
                            parent[nx][ny] = {x, y};
                        }
                    }
                }
            }
        }
    }
    
    // Trace path from goal to start
    vector<pair<int, int>> path;
    pair<int, int> current = goal;
    
    while (current != start) {
        path.push_back(current);
        current = parent[current.first][current.second];
    }
    path.push_back(start);
    
    reverse(path.begin(), path.end());
    return path;
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
    
    vector<pair<int, int>> path = bellmanFord(grid, start, goal);
    savePathToCSV(path, "../output/bellman_ford_path.csv");

    return 0;
}
