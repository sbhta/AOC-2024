#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

std::map<char, std::pair<int, int>> dirs = {
   {'^', {-1, 0}},
   {'>', {0, 1}},
   {'v', {1, 0}},
   {'<', {0, -1}}
};

int part1(std::vector<std::string> inp){
   std::vector<std::string> grid;
   std::string moves = "";
   bool t = false;
   for (std::string s : inp){
      if (s == ""){
         t = true;
         continue;
      }
      if (t) moves += s;
      else grid.push_back(s);
   }
   int r, c; bool run = true;
   for (int i = 0; i < grid.size() && run; ++i){
      for (int j = 0; j < grid.size(); ++j){
         if (grid[i][j] == '@') {r = i, c =j, run = false; break;}
      }
   }
   for (const char& m : moves){
      int dr = dirs[m].first, dc = dirs[m].second;
      std::vector<std::pair<int, int>> targets;
      int cr = r;int cc = c;
      bool move = true;
      while (true){
         cr += dr;
         cc += dc;
         char current = grid[cr][cc];
         if (current == '#'){
            move = false;
            break;
         }
         if (current == 'O'){ targets.push_back({cr, cc}); }
         if (current == '.'){
            break;
         }
      }
      if (!move){ continue; }
      grid[r][c] = '.';
      grid[r+dr][c+dc] = '@';
      for (auto [br, bc] : targets){
         grid[br+dr][bc+dc] = 'O';
      }
      r+=dr;
      c+=dc;
   }
   int sum = 0;
   for (int i = 0; i < grid.size(); ++i){
      for (int j = 0; j < grid.size(); ++j){
         if (grid[i][j] == 'O') sum+=i*100+j;
      }
   }
   return sum;
}
std::map<char, std::string> expension = {
   {'#', "##"},
   {'O', "[]"},
   {'.', ".."},
   {'@', "@."},
};
int part2(std::vector<std::string> inp){
   std::vector<std::string> grid;
   std::string moves = "";
   bool t = false;
   for (std::string s : inp){
      if (s == ""){
         t = true;
         continue;
      }
      if (t) moves += s;
      else {
         std::string temp = "";
         for (char ch : s){
            temp+=expension[ch];
         }
         grid.push_back(temp);
      }
   }
   int r, c; bool run = true;
   for (int i = 0; i < grid.size() && run; ++i){
      for (int j = 0; j < grid.size(); ++j){
         if (grid[i][j] == '@') {r = i, c =j, run = false; break;}
      }
   }
   for (const char& m : moves){
      int dr = dirs[m].first, dc = dirs[m].second;
      std::vector<std::pair<int, int>> targets = {{r, c}};
      bool move = true;
      for (int i = 0; i < targets.size(); ++i){
         int nr = targets[i].first + dr;
         int nc = targets[i].second + dc;
         if (std::find(targets.begin(), targets.end(), std::pair<int, int>{nr, nc}) != targets.end()){
            continue;
         }
         char ch = grid[nr][nc];
         if (ch == '#'){
            move = false;
            break;
         }
         if (ch == '['){
            targets.push_back({nr, nc});
            targets.push_back({nr, nc+1});
         }
         if (ch == ']'){
            targets.push_back({nr, nc});
            targets.push_back({nr, nc-1});
         }
      }
      if (!move) continue;
      std::vector<std::string> copy = grid;
      grid[r][c] = '.';
      grid[r+dr][c+dc] = '@';
      for (int i = 1; i < targets.size(); ++i){
         int br = targets[i].first, bc = targets[i].second;
         grid[br][bc] = '.';
      }
      for (int i = 1; i < targets.size(); ++i){
         int br = targets[i].first, bc = targets[i].second;
         grid[br+dr][bc+dc] = copy[br][bc];
      }
      r += dr;
      c += dc;
   }
   int sum = 0;
   for (int i = 0; i < grid.size(); ++i){
      for (int j = 0; j < grid[0].size(); ++j){
         if (grid[i][j] == '[') sum+=i*100+j;
      }
   }
   return sum;
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
