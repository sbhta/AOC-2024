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
   std::vector<std::string> sample;
   std::vector<std::string> input;
   std::string temp;
   std::ifstream fileSample(argv[1]);
   std::ifstream fileInput(argv[2]);
   while (std::getline(fileSample, temp)){sample.push_back(temp);}
   while (std::getline(fileInput, temp)){input.push_back(temp);}
   fileSample.close();
   fileInput.close();

   std::cout << part2(input) << std::endl;
   return 0;
}
