#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::pair<int, int> parsePair(const std::string& str, size_t startPos) {
    // Find the positions of the commas and parse the numbers
    size_t commaPos = str.find(',', startPos);
    size_t spacePos = str.find(' ', startPos);

    int first = std::stoi(str.substr(startPos, commaPos - startPos));
    int second = std::stoi(str.substr(commaPos + 1, (spacePos == std::string::npos ? str.size() : spacePos) - (commaPos + 1)));

    return {first, second};
}
void moveRobot(int width, int height, std::pair<std::pair<int, int>, std::pair<int, int>>& robot){
   if (robot.first.first + robot.second.first >= width){robot.first.first = (robot.first.first+robot.second.first)-width;}
   else if (robot.first.first + robot.second.first < 0){robot.first.first = width+(robot.first.first+robot.second.first);}
   else {robot.first.first += robot.second.first;}
   if (robot.first.second + robot.second.second >= height){robot.first.second = (robot.first.second+robot.second.second)-height;}
   else if (robot.first.second + robot.second.second < 0){robot.first.second = height+(robot.first.second+robot.second.second);}
   else {robot.first.second += robot.second.second;}
}
int part1(std::vector<std::string> inp){
   // vector{ {pos, vel}, {pos, vel}..... }
   std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> robots;
   // p=0,4 v=3,-3
   // size of map is 101x103
   std::string temp = "";
   for (int i = 0; i < inp.size(); ++i){
      std::pair<int, int> pos = parsePair(inp[i], inp[i].find("p=")+2);
      std::pair<int, int> vel = parsePair(inp[i], inp[i].find("v=")+2);
      robots.push_back({pos, vel});
   }
   int width = 101, heigth = 103;
   for (int i = 0; i < 100; ++i){ for (int j = 0; j < robots.size(); ++j){ moveRobot(width, heigth, robots[j]); } }
   std::vector<std::pair<int, int>> quad1;
   std::vector<std::pair<int, int>> quad2;
   std::vector<std::pair<int, int>> quad3;
   std::vector<std::pair<int, int>> quad4;
   for (int i = 0; i < robots.size(); ++i){
      if (robots[i].first.first == width/2)continue;
      if (robots[i].first.second == heigth/2)continue;
      if (robots[i].first.first < width/2 && robots[i].first.second < heigth/2) quad1.push_back(robots[i].first);
      if (robots[i].first.first > width/2 && robots[i].first.second < heigth/2) quad2.push_back(robots[i].first);
      if (robots[i].first.first > width/2 && robots[i].first.second > heigth/2) quad3.push_back(robots[i].first);
      if (robots[i].first.first < width/2 && robots[i].first.second > heigth/2) quad4.push_back(robots[i].first);
      //std::cout<< robots[i].first.first << ',' << robots[i].first.second << std::endl;
   }

   return quad1.size()*quad2.size()*quad3.size()*quad4.size();
}
int part2(std::vector<std::string> inp){
   // vector{ {pos, vel}, {pos, vel}..... }
   std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> robots;
   // p=0,4 v=3,-3
   // size of map is 101x103
   std::string temp = "";
   for (int i = 0; i < inp.size(); ++i){
      std::pair<int, int> pos = parsePair(inp[i], inp[i].find("p=")+2);
      std::pair<int, int> vel = parsePair(inp[i], inp[i].find("v=")+2);
      robots.push_back({pos, vel});
   }
   int width = 101, heigth = 103;
   for (int i = 0; i < 100; ++i){
      for (int j = 0; j < robots.size(); ++j){
         moveRobot(width, heigth, robots[j]); 
      }
      for (int y = 0; y < heigth; ++y){
         for (int x = 0; x < width; ++x){
            // to tedious no point
         }
      }
   }
   return 0;
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
