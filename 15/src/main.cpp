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
bool moveBox(std::vector<std::string>& map, int row, int col, std::pair<int, int> dir){
   if (map[row][col] == '#') return false;
   else if (map[row][col] == 'O'){
      if (moveBox(map,row+dir.first,col+dir.second,dir)){
         map[row][col] = '.';
         map[row+dir.first][col+dir.second] = 'O';
         return true;
      }
      else return false;
   }
   else return true;
}
bool moveRobot(std::vector<std::string>& map, std::pair<int, int> dir){
   bool run = true;
   std::pair<int, int> pos;
   for (int i = 0; i < map.size() && run; ++i){
      for (int j = 0; j < map[0].length(); ++j){
        if (map[i][j] == '@'){
            pos.first = i;
            pos.second = j;
            run = false;
            break;
         }
      }
   }
   if (map[pos.first+dir.first][pos.second+dir.second] == '#') return false;
   else if (map[pos.first+dir.first][pos.second+dir.second] == 'O'){
      if (moveBox(map, pos.first+dir.first, pos.second+dir.second, dir)){
         map[pos.first][pos.second] = '.';
         map[pos.first+dir.first][pos.second+dir.second] = '@';
         return true;
      }
   }
   else {
      map[pos.first][pos.second] = '.';
      map[pos.first+dir.first][pos.second+dir.second] = '@';
      return true;
   }
   return false;
}

int part1(std::vector<std::string> inp){
   std::vector<std::string> map;
   std::vector<char> actions;
   //sorting the input into the map and the actions that will have to be taken
   int start;
   for (int i = 0; i < inp.size(); ++i){
      if (inp[i] == "") {start = i;break;}
      else{
         map.push_back(inp[i]);
      }
   }
   for (int i = start+1; i < inp.size(); ++i){
      for (char c : inp[i]){
         actions.push_back(c);
      }
   }
   //printing the before and after
   for (int i = 0; i < map.size(); ++i){ std::cout << map[i] << std::endl; }
   for (char act : actions){ moveRobot(map, dirs[act]); }
   for (int i = 0; i < map.size(); ++i){ std::cout << map[i] << std::endl; }

   int sum = 0;
   for (int i = 0; i < map.size(); ++i){
      for (int j = 0; j < map[0].length(); ++j){
         if (map[i][j] == 'O') sum += (i*100)+j;
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
   //std::cout << "Part 2: " << part2(input) << std::endl; 
   return 0;
}
