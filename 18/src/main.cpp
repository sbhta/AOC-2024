#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <tuple>

int shortestPath(const std::vector<std::vector<char>>& grid) {
    int height = grid.size();
    int width = grid[0].size();
    
    // Directions for moving up, down, left, and right
    const std::vector<std::pair<int, int>> directions = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}
    };
    
    std::queue<std::tuple<int, int, int>> q; // (row, col, steps)
    q.emplace(0, 0, 0);
    
    // Visited grid
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    visited[0][0] = true;
    
    while (!q.empty()) {
        auto [row, col, steps] = q.front();
        q.pop();
        
        // Check if we've reached the destination
        if (row == height - 1 && col == width - 1) {
            return steps;
        }
        
        for (const auto& [dr, dc] : directions) {
            int newRow = row + dr;
            int newCol = col + dc;
            
            // Check bounds and if the cell is a path ('.') and not visited
            if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width &&
                grid[newRow][newCol] == '.' && !visited[newRow][newCol]) {
                visited[newRow][newCol] = true;
                q.emplace(newRow, newCol, steps + 1);
            }
        }
    }
    
    // The function will always return from within the loop since there's always a path
    return -1; // This will never execute
}
int part1(std::vector<std::string> inp, int mapS, int bytesA){
   std::vector<std::vector<char>> map;
   int mapSize = mapS; mapSize++;
   int amountOfBytes = bytesA;
   std::vector<std::pair<int, int>> bytes;
   // parse input into bytes
   for (int i = 0; i < inp.size(); ++i){
      int one = 0;
      int two = 0;
      std::string temp = "";
      for (int j = 0; j < inp[i].length(); ++j){
         if (inp[i][j] == ','){
            one = std::stoi(temp);
            temp = "";
         }
         else {
            temp += inp[i][j];
         }
      }
      two = std::stoi(temp);
      bytes.push_back({one, two});
   }
   // initialize map with '.'
   for (int i = 0; i < mapSize; ++i){
      map.push_back(std::vector<char>(mapSize, '.'));
   }
   // make bytes up to the specified amount to 'fall'
   for (int i = 0; i < amountOfBytes; ++i){
      map[bytes[i].second][bytes[i].first] = '#';
   }
   // print the map
   for (int i = 0; i < mapSize; ++i){
      for (int j = 0; j < mapSize; ++j){
      }
   }

   return shortestPath(map);
}
int part2(std::vector<std::string> inp, int mapS) {
   std::vector<std::vector<char>> map;
   int mapSize = mapS; mapSize++;
   std::vector<std::pair<int, int>> bytes;

   // Parse input into bytes
   for (int i = 0; i < inp.size(); ++i) {
      int one = 0, two = 0;
      std::string temp = "";
      for (int j = 0; j < inp[i].length(); ++j) {
         if (inp[i][j] == ',') {
            if (!temp.empty()) {
               one = std::stoi(temp);
               temp = "";
            } else {
               std::cerr << "Invalid input format: " << inp[i] << std::endl;
               return -1;
            }
         } else {
            temp += inp[i][j];
         }
      }
      if (!temp.empty()) {
         two = std::stoi(temp);
         bytes.push_back({one, two});
      } else {
         std::cerr << "Invalid input format: " << inp[i] << std::endl;
         return -1;
      }
   }
   // Initialize map with '.'
   for (int i = 0; i < mapSize; ++i) {
      map.push_back(std::vector<char>(mapSize, '.'));
   }
   // Add bytes to the map and check reachability
   for (int i = 0; i < bytes.size(); ++i) {
      map[bytes[i].second][bytes[i].first] = '#';
      // Check if the exit is still reachable
      int pathLength = shortestPath(map);
      if (pathLength == -1) {
         std::cout  << bytes[i].first <<','<<bytes[i].second << std::endl;
         return -1;
      }
   }

   // Print the map
   for (int i = 0; i < mapSize; ++i) {
      for (int j = 0; j < mapSize; ++j) {
         std::cout << map[i][j];
      }
      std::cout << std::endl;
   }

   return shortestPath(map);
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
   std::cout << "Part 1: " << part1(input, 70, 1024) << std::endl;
   std::cout << "Part 2: ";   part2(input, 70);  
   return 0;
}
