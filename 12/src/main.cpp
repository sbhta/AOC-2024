#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <vector>
#include <queue>

#include <unordered_map>
#include <unordered_set>
#include <queue>

struct RegionInfo {
    int area;
    int sides;
};

std::vector<std::pair<int, int>> directions = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};

bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

RegionInfo bfsRegionInfo(std::vector<std::vector<char>>& grid, std::vector<std::vector<bool>>& visited, int startX, int startY) {
    char plantType = grid[startX][startY];
    int rows = grid.size(), cols = grid[0].size();

    std::queue<std::pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = true;

    int area = 0;
    int sides = 0;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        area++;
        int localSides = 0;

        for (auto [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            if (!isValid(nx, ny, rows, cols) || grid[nx][ny] != plantType) {
                localSides++; // Edge to another type or out of bounds counts as a side.
            } else if (!visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }

        sides += localSides;
    }

    return {area, sides};
}

int calculateTotalPrice(std::vector<std::vector<char>>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::unordered_map<char, std::vector<RegionInfo>> regionInfo;

    int totalPrice = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!visited[i][j]) {
                RegionInfo info = bfsRegionInfo(grid, visited, i, j);
                regionInfo[grid[i][j]].push_back(info);
                totalPrice += info.area * info.sides;
            }
        }
    }

    return totalPrice;
}

int part1(std::vector<std::string> inputGrid) {
    std::vector<std::vector<char>> grid;
    for (const auto& row : inputGrid) {
        grid.push_back(std::vector<char>(row.begin(), row.end()));
    }

    return calculateTotalPrice(grid);
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
