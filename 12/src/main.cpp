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

int part(std::vector<std::string> inputGrid) {
    std::vector<std::vector<char>> grid;
    for (const auto& row : inputGrid) {
        grid.push_back(std::vector<char>(row.begin(), row.end()));
    }

    std::cout << "Total price: " << calculateTotalPrice(grid) << std::endl;

    return 0;
}

int main (int argc, char *argv[]) {
   std::vector<std::string> sample;
   std::vector<std::string> input;
   std::string temp;
   std::ifstream fileSample(argv[1]);
   std::ifstream fileInput(argv[2]);
   while (std::getline(fileSample, temp)){sample.push_back(temp);}
   while (std::getline(fileInput, temp)){input.push_back(temp);}
   fileSample.close();
   fileInput.close();

   std::cout << part(sample) << std::endl;
   return 0;
}
