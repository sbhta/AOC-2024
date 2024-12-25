#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <set>

struct State {
    int score, x, y, dir;
    bool operator>(const State& other) const { return score > other.score; }
};

// Directions: {dx, dy} for up, right, down, left
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

// Find the minimum score and return visited states for backtracking
int findBestPath(const std::vector<std::string>& maze, std::unordered_map<std::string, int>& visitedStates) {
    int rows = maze.size(), cols = maze[0].size();
    std::pair<int, int> start, end;

    // Locate start (S) and end (E)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] == 'S') start = {i, j};
            if (maze[i][j] == 'E') end = {i, j};
        }
    }

    // Priority queue: (score, x, y, direction)
    std::priority_queue<State, std::vector<State>, std::greater<>> pq;

    // Push initial states for all 4 directions
    for (int dir = 0; dir < 4; ++dir) {
        pq.push({0, start.first, start.second, dir});
    }

    int minScore = -1;

    while (!pq.empty()) {
        auto [score, x, y, dir] = pq.top();
        pq.pop();

        // If we reach the end, record the minimum score
        if (maze[x][y] == 'E') {
            if (minScore == -1) minScore = score;
            if (score > minScore) continue; // Ignore higher scores to the end
        }

        // Unique state key
        std::string key = std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(dir);
        if (visitedStates.count(key) && visitedStates[key] <= score) continue;
        visitedStates[key] = score;

        // Move forward
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && maze[nx][ny] != '#') {
            pq.push({score + 1, nx, ny, dir});
        }

        // Turn left
        int leftDir = (dir + 3) % 4; // (dir - 1 + 4) % 4
        pq.push({score + 1000, x, y, leftDir});

        // Turn right
        int rightDir = (dir + 1) % 4;
        pq.push({score + 1000, x, y, rightDir});
    }

    return minScore;
}

// Backtrack to find tiles part of the optimal paths
void backtrackOptimalTiles(const std::vector<std::string>& maze, const std::unordered_map<std::string, int>& visitedStates,
                           int minScore, std::set<std::pair<int, int>>& optimalTiles) {
    int rows = maze.size(), cols = maze[0].size();
    std::pair<int, int> end;

    // Locate end (E)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] == 'E') {
                end = {i, j};
                break;
            }
        }
    }

    // Queue for backtracking
    std::queue<std::tuple<int, int, int>> q;
    for (int dir = 0; dir < 4; ++dir) {
        std::string key = std::to_string(end.first) + "," + std::to_string(end.second) + "," + std::to_string(dir);
        if (visitedStates.count(key) && visitedStates.at(key) == minScore) {
            q.push({end.first, end.second, dir});
            optimalTiles.insert({end.first, end.second});
        }
    }

    while (!q.empty()) {
        auto [x, y, dir] = q.front();
        q.pop();

        int currentScore = visitedStates.at(std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(dir));

        // Check moves that could have led to this state
        // 1. Move backward
        int bx = x - dx[dir];
        int by = y - dy[dir];
        if (bx >= 0 && by >= 0 && bx < rows && by < cols && maze[bx][by] != '#') {
            std::string backKey = std::to_string(bx) + "," + std::to_string(by) + "," + std::to_string(dir);
            if (visitedStates.count(backKey) && visitedStates.at(backKey) + 1 == currentScore) {
                q.push({bx, by, dir});
                optimalTiles.insert({bx, by});
            }
        }

        // 2. Turn left
        int leftDir = (dir + 3) % 4;
        std::string leftKey = std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(leftDir);
        if (visitedStates.count(leftKey) && visitedStates.at(leftKey) + 1000 == currentScore) {
            q.push({x, y, leftDir});
            optimalTiles.insert({x, y});
        }

        // 3. Turn right
        int rightDir = (dir + 1) % 4;
        std::string rightKey = std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(rightDir);
        if (visitedStates.count(rightKey) && visitedStates.at(rightKey) + 1000 == currentScore) {
            q.push({x, y, rightDir});
            optimalTiles.insert({x, y});
        }
    }
}

int part1(std::vector<std::string> inp){
    std::unordered_map<std::string, int> visitedStates;
    std::set<std::pair<int, int>> optimalTiles;

    return findBestPath(inp, visitedStates);
}
int part2(std::vector<std::string> inp){
    std::unordered_map<std::string, int> visitedStates;
    std::set<std::pair<int, int>> optimalTiles;

    int minScore = findBestPath(inp, visitedStates);
    backtrackOptimalTiles(inp, visitedStates, minScore, optimalTiles);

    // Mark the maze with optimal tiles
    for (auto& [x, y] : optimalTiles) {
        if (inp[x][y] == '.') inp[x][y] = 'O';
    }
   return optimalTiles.size();
}

int main (int argc, char *argv[]) {
   if (argc < 2) {
      std::cerr << "Error: No file path provided.\n";
      std::cerr << "Usage: " << argv[0] << " <filename>\n";
      return 1;
   }
   std::string filePath = argv[1];
   if (filePath.empty()) {
      std::cerr << "Error: File path is empty.\n";
      return 1;
   }
   std::vector<std::string> input;
   std::ifstream file(filePath);
   std::string temp;
   while (std::getline(file, temp)){
      input.push_back(temp);
   }
   file.close();
   std::cout << "Part 1: " << part1(input) << std::endl;
   std::cout << "Part 2: " << part2(input) << std::endl;
    return 0;
}

