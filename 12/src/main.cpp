#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <queue>

struct Corner {
   double row;
   double col;
   bool operator<(const Corner& other) const { return row < other.row || (row == other.row && col < other.col); }
   bool operator==(const Corner& other) const { return row == other.row && col == other.col; }
};
struct Point {
   int row;
   int col;
   bool operator<(const Point& other) const { return row < other.row || (row == other.row && col < other.col); }
   bool operator==(const Point& other) const { return row == other.row && col == other.col; }
};
bool isValid(int row, int col, const std::vector<std::string>& grid) {
   return row >= 0 && row < grid.size() && col >= 0 && col < grid[0].size();
}
const std::vector<Point> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int calculateRegionPricePart1(int area, int perimeter) { return area * perimeter; }
int part1(std::vector<std::string> inputGrid) {
   int rows = inputGrid.size();
   int cols = inputGrid[0].size();
   std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

   int totalPrice = 0;
   
   // Lambda for BFS
   auto bfs = [&](int startRow, int startCol, char plantType) {
      int area = 0;
      int perimeter = 0;
      std::queue<Point> q;
      q.push({startRow, startCol});
      visited[startRow][startCol] = true;

      while (!q.empty()) {
         Point current = q.front();
         q.pop();
         area++;
         for (const Point& dir : directions) {
            int newRow = current.row + dir.row;
            int newCol = current.col + dir.col;

            if (isValid(newRow, newCol, inputGrid)) {
               if (inputGrid[newRow][newCol] == plantType) {
                  if (!visited[newRow][newCol]) {
                     visited[newRow][newCol] = true;
                     q.push({newRow, newCol});
                  }
               } else {
                  // Neighbor is a different type
                  perimeter++;
               }
            } else {
               // Out of bounds contributes to the perimeter
               perimeter++;
            }
         }
      }
      return calculateRegionPricePart1(area, perimeter);
   };

   // Traverse the grid
   for (int row = 0; row < rows; ++row) {
      for (int col = 0; col < cols; ++col) {
         if (!visited[row][col]) {
            // Start BFS for a new region
            totalPrice += bfs(row, col, inputGrid[row][col]);
         }
      }
   }
   return totalPrice;
}

std::vector<std::set<Point>> getRegions(const std::vector<std::string> &inputGrid) {
    std::vector<std::set<Point>> regions;
    int rows = inputGrid.size();
    if (rows == 0) return regions;
    int cols = inputGrid[0].size();

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    auto isValid = [&](int row, int col, char target) {
        return row >= 0 && row < rows && col >= 0 && col < cols &&
               !visited[row][col] && inputGrid[row][col] == target;
    };

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (!visited[r][c]) {
                char target = inputGrid[r][c];
                std::set<Point> region;
                std::queue<Point> toVisit;

                toVisit.push({r, c});
                visited[r][c] = true;

                while (!toVisit.empty()) {
                    Point current = toVisit.front();
                    toVisit.pop();
                    region.insert(current);

                    // Check neighbors
                    for (const auto &[dr, dc] : std::vector<std::pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
                        int newRow = current.row + dr;
                        int newCol = current.col + dc;

                        if (isValid(newRow, newCol, target)) {
                            toVisit.push({newRow, newCol});
                            visited[newRow][newCol] = true;
                        }
                    }
                }

                regions.push_back(region);
            }
        }
    }

    return regions;
}
int part2(std::vector<std::string> inputGrid){
   std::vector<std::set<Point>> regions = getRegions(inputGrid);
   std::vector<int> cornersPerRegion;
   for (const std::set<Point>& reg : regions){
      std::set<Corner> cornersCands;
      for (auto [r, c] : reg){
         for (auto [cr, cc] : std::vector<std::pair<double, double>>{{r-0.5, c-0.5},{r+0.5, c+0.5},{r+0.5, c-0.5},{r-0.5, c+0.5}}){
            cornersCands.insert({cr, cc});
         }
      }
      int corners = 0;
      for (const auto& [cr, cc] : cornersCands){
         int adjecent = 0;
         for (auto [sr, sc] : std::vector<std::pair<int, int>>{{cr-0.5, cc-0.5},{cr+0.5, cc+0.5},{cr+0.5, cc-0.5},{cr-0.5, cc+0.5}}){
            if (reg.find({sr, sc}) != reg.end()) adjecent++;
         }
         if (adjecent == 1 || adjecent == 3) corners++;
      }
      cornersPerRegion.push_back(corners);
   }
   int totalCost = 0;
   for (int i = 0; i < regions.size(); ++i){
      totalCost += regions[i].size()*cornersPerRegion[i];
   }
   return totalCost;
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
