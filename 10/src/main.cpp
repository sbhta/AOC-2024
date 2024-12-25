#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
int sum = 0;
int sumOfRatings = 0;
std::vector<std::pair<int ,int>>dirs = {
   {-1, 0},
{0, -1}, {0, 1},
   {1, 0}
};
bool inBounds(int rows, int cols, std::pair<int, int> pos){
   if (pos.first < 0 || pos.first >= rows) return false;
   if (pos.second < 0 || pos.second >= cols) return false;
   return true;
}
int findPath(std::vector<std::vector<int>>& map, int row, int col){
   if (map[row][col] == 9) {
      sum += 1;
      map[row][col] = -1;
      return 0;
   }
   else {
      for (auto d : dirs){
         if (inBounds(map.size(), map[0].size(),{row+d.first, col+d.second})){
            if (map[row+d.first][col+d.second] == map[row][col]+1){
               findPath(map, row+d.first, col+d.second);
            }
         }
      }
   }
   return -1;
}
int findPathRating(std::vector<std::vector<int>> map, int row, int col){
   if (map[row][col] == 9) {
      sumOfRatings += 1;
      return 0;
   }
   else {
      for (auto d : dirs){
         if (inBounds(map.size(), map[0].size(),{row+d.first, col+d.second})){
            if (map[row+d.first][col+d.second] == map[row][col]+1){
               findPathRating(map, row+d.first, col+d.second);
            }
         }
      }
   }
   return -1;
}

int part1(std::vector<std::string> inp){
   std::vector<std::vector<int>> map;
   std::vector<int> temp;
   for (std::string s : inp){
      for (char c : s){
         temp.push_back(c-'0');
      }
      map.push_back(temp);
      temp.clear();
   }
   for (int i = 0; i < map.size(); ++i){
      for (int j = 0; j < map[0].size(); ++j){
         if (map[i][j] == 0) {
            std::vector<std::vector<int>> copy_map = map;
            findPath(copy_map, i, j);
         }
      }
   }
   return sum;
}
int part2(std::vector<std::string> inp){
   std::vector<std::vector<int>> map;
   std::vector<int> temp;
   for (std::string s : inp){
      for (char c : s){
         temp.push_back(c-'0');
      }
      map.push_back(temp);
      temp.clear();
   }
   for (int i = 0; i < map.size(); ++i){
      for (int j = 0; j < map[0].size(); ++j){
         if (map[i][j] == 0) {
            std::vector<std::vector<int>> copy_map = map;
            findPathRating(copy_map, i, j);
         }
      }
   }
   return sumOfRatings;
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
