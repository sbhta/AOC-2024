#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>


int part1(std::vector<std::string> inp){
   std::vector<std::string> board = inp;
   int xG, yG;
   char currentDir = 'u';
   std::map<char, std::pair<int, int>> dir = {
      {'r', {1, 0}},
      {'l', {-1, 0}},
      {'u', {0, -1}},
      {'d', {0, 1}},
   }; 
   int dxG = dir[currentDir].first, dyG = dir[currentDir].second;
   for (int i = 0; i < board.size(); ++i){ for (int j = 0; j < board[0].length(); ++j){ if (board[i][j] == '^') {xG = j; yG = i;break;} } }

   int visited = 1;
   while (xG+dxG < board[0].length() && xG+dxG > -1 &&
      yG+dyG < board.size() && yG+dyG > -1){
      int fyG = yG+dyG, fxG = xG+dxG;
      if (board[fyG][fxG] == '#'){
         if (currentDir == 'u') currentDir = 'r';
         else if (currentDir == 'r') currentDir = 'd';
         else if (currentDir == 'd') currentDir = 'l';
         else if (currentDir == 'l') currentDir = 'u';
         dxG = dir[currentDir].first;
         dyG = dir[currentDir].second;
         continue;
      }
      else {
         xG = fxG;
         yG = fyG;
         if (board[yG][xG] != 'X'){
            visited++;
            board[yG][xG] = 'X';
         }
      }
   }
   return visited;
}
int part2(std::vector<std::string> inp) {
   std::vector<std::string> board = inp;
   int x, y;
   for (int i = 0; i < inp.size(); ++i){ for (int j = 0; j < inp.size(); ++j){ if (inp[i][j] == '^') {y = i; x = j; break;} } }
   char currentDir = 'u';
   std::map<char, std::pair<int, int>> dir = {
      {'r', {1, 0}},
      {'l', {-1, 0}},
      {'u', {0, -1}},
      {'d', {0, 1}},
   }; 
   int dx = dir[currentDir].first, dy = dir[currentDir].second;
   for (int i = 0; i < board.size(); ++i){ for (int j = 0; j < board[0].length(); ++j){ if (board[i][j] == '^') {x = j; y = i;break;} } }
   while (x+dx < board[0].length() && x+dx > -1 &&
      y+dy < board.size() && y+dy > -1){
      int fy = y+dy, fx = x+dx;
      if (board[fy][fx] == '#'){
         if (currentDir == 'u') currentDir = 'r';
         else if (currentDir == 'r') currentDir = 'd';
         else if (currentDir == 'd') currentDir = 'l';
         else if (currentDir == 'l') currentDir = 'u';
         dx = dir[currentDir].first;
         dy = dir[currentDir].second;
         continue;
      }
      else {
         x = fx;
         y = fy;
         if (board[y][x] != 'X'){
            board[y][x] = 'X';
         }
      }
   }
   std::vector<std::pair<int, int>> visited;
   for (int i = 0; i < board.size(); ++i){ for (int j = 0; j < board[0].length(); ++j){ 
      if (board[i][j] == 'X') {
         visited.push_back({i, j});
      } 
   } }
   int count = 0;
   int index = 0;
   for (auto v : visited){
      index++;
      std::vector<std::string> b2 = inp; b2[v.first][v.second] = '#';
      for (int i = 0; i < inp.size(); ++i){ for (int j = 0; j < inp.size(); ++j){ if (inp[i][j] == '^') {y = i; x = j; break;} } }
      char currentDir = 'u';
      int dx = dir[currentDir].first, dy = dir[currentDir].second;
      while (x+dx < b2[0].length() && x+dx > -1 &&
         y+dy < b2.size() && y+dy > -1){
         int fy = y+dy, fx = x+dx;
         if (b2[fy][fx] == '#'){
            if (currentDir == 'u') currentDir = 'r';
            else if (currentDir == 'r') currentDir = 'd';
            else if (currentDir == 'd') currentDir = 'l';
            else if (currentDir == 'l') currentDir = 'u';
            dx = dir[currentDir].first;
            dy = dir[currentDir].second;
            continue;
         }
         else {
            x = fx;
            y = fy;
            if (b2[y][x] == '.'){
               b2[y][x] = currentDir;
            }
            else {
               if (b2[y][x] == currentDir){
                  count++;
                  break;
               }
            }
         }
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
   std::cout << "Part 2: " << part2(input) << std::endl;
   return 0;
}
