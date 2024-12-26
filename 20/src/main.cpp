#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <unordered_map>

struct Point {
    int x, y;
};

// Directions for moving in the grid: up, down, left, right.
const std::vector<Point> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int findShortestPath(const std::vector<std::string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    Point start, end;

    // Locate 'S' and 'E' in the grid.
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 'S') start = {i, j};
            if (grid[i][j] == 'E') end = {i, j};
        }
    }

    // BFS setup
    std::queue<Point> q;
    q.push(start);

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    visited[start.x][start.y] = true;

    int steps = 0;

    while (!q.empty()) {
        int qSize = q.size();
        for (int i = 0; i < qSize; ++i) {
            Point current = q.front();
            q.pop();

            // If we reach the endpoint, return the number of steps.
            if (current.x == end.x && current.y == end.y) return steps;

            // Explore neighbors.
            for (const auto& dir : directions) {
                int newX = current.x + dir.x;
                int newY = current.y + dir.y;

                // Check boundaries and if the cell is a path and not visited.
                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
                    grid[newX][newY] != '#' && !visited[newX][newY]) {
                    visited[newX][newY] = true;
                    q.push({newX, newY});
                }
            }
        }
        ++steps;
    }

    // If we exhaust the search and don't find 'E', return -1 (no path exists).
    return -1;
}
int part1(std::vector<std::string> inp){
   int baseTime = findShortestPath(inp);
   std::map<int, int> results;
   int k = 0;
   for (int i = 0; i < inp.size(); ++i){
      for (int j = 0; j < inp[0].size(); ++j){
         k++;
         std::cout << k << std::endl;
         std::vector<std::string> temp = inp;
         if (temp[i][j] == '#'){
            temp[i][j] = '.';
            int tempTime = findShortestPath(temp);
            if (tempTime < baseTime){
               if (results.find(tempTime) == results.end()){
                  results[tempTime] = 1;
               }
               else {
                  results[tempTime]++;
               }
            }
         }
      }
   }
   int count = 0;
   for (auto [time, c] : results){
      if (time <= baseTime-100){
         count += c;
      }
   }
   return count;
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
   //std::cout << "Part 2: " << part2(input) << std::endl;
   return 0;
}
