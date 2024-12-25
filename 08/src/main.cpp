#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>


bool outOfBounds(std::pair<int, int> cord, std::vector<std::string> inp){
   if (cord.first < 0 || cord.first >= inp.size()) return true;
   if (cord.second < 0 || cord.second >= inp[0].length()) return true;
   return false;
}

int part1(std::vector<std::string> inp){
   std::unordered_map<char, std::vector<std::pair<int, int>>> antenas;
   for (int i = 0; i < inp.size(); ++i){
      for (int j = 0; j < inp[0].length(); ++j){
         if (inp[i][j] != '.') antenas[inp[i][j]].push_back({i, j});
      }
   }
   for (int i = 0; i < inp.size(); ++i){
      for (int j = 0; j < inp[0].length(); ++j){
         inp[i][j] = '.';
      }
   }
   for (const auto& [freq, coords] : antenas){
      for (int i = 0; i < coords.size(); ++i){
         for (int j = 0; j < coords.size(); ++j){
            if (i == j) continue;
            std::pair<int, int> p1 = coords[i];
            std::pair<int, int> p2 = coords[j];
            int r_diff = p1.first - p2.first;
            int c_diff = p1.second - p2.second;
            int new_r = p1.first + r_diff;
            int new_c = p1.second + c_diff;
            if (!outOfBounds({new_r, new_c},inp)){
               inp[new_r][new_c] = '#';
            }
         }
      }
   }
   int sum = 0;
   for (std::string x : inp){
      for (char y : x){
         if (y == '#') sum++;
      }
   }
   return sum;
}
int part2(std::vector<std::string> inp){
   std::unordered_map<char, std::vector<std::pair<int, int>>> antenas;
   for (int i = 0; i < inp.size(); ++i){
      for (int j = 0; j < inp[0].length(); ++j){
         if (inp[i][j] != '.') antenas[inp[i][j]].push_back({i, j});
      }
   }
   for (int i = 0; i < inp.size(); ++i){
      for (int j = 0; j < inp[0].length(); ++j){
         inp[i][j] = '.';
      }
   }
   for (const auto& [freq, coords] : antenas){
      for (int i = 0; i < coords.size(); ++i){
         inp[coords[i].first][coords[i].second] = '#';
         for (int j = 0; j < coords.size(); ++j){
            if (i == j) continue;
            std::pair<int, int> p1 = coords[i];
            std::pair<int, int> p2 = coords[j];
            int r_diff = p1.first - p2.first;
            int c_diff = p1.second - p2.second;
            int new_r = p1.first + r_diff;
            int new_c = p1.second + c_diff;
            while (!outOfBounds({new_r, new_c},inp)){
               inp[new_r][new_c] = '#';
               new_r += r_diff;
               new_c += c_diff;
            }
         }
      }
   }
   int sum = 0;
   for (std::string x : inp){
      std::cout << x << std::endl;
      for (char y : x){
         if (y != '.') sum++;
      }
   }
   return sum;
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