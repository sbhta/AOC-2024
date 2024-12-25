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
   std::cout << "before: " << std::endl;
   for (int i = 0; i < map.size(); ++i){ std::cout << map[i] << std::endl; }
   for (char act : actions){ moveRobot(map, dirs[act]); }
   std::cout << "after: " << std::endl;
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
   std::vector<std::string> sample;
   std::vector<std::string> input;
   std::string temp;
   std::ifstream fileSample(argv[1]);
   std::ifstream fileInput(argv[2]);
   while (std::getline(fileSample, temp)){sample.push_back(temp);}
   while (std::getline(fileInput, temp)){input.push_back(temp);}
   fileSample.close();
   fileInput.close();

   std::cout << part1(sample) << std::endl;
   std::cout << part1(input) << std::endl;
   return 0;
}
