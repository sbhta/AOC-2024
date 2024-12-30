#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

int part1(std::vector<std::string> inp){
   int width = 101, height = 103;
   std::regex number_regex(R"(-?\d+)");
   std::vector<std::pair<int, int>> robots;
   for (std::string block : inp){
      std::vector<int> numbers;
      for (std::sregex_iterator it(block.begin(), block.end(), number_regex), end; it != end; ++it) {
         numbers.push_back(std::stoi(it->str()));
      }

      robots.push_back({
         (numbers[0]+numbers[2]*100)%width,
         (numbers[1]+numbers[3]*100)%height
      });
   }
   for (auto& r : robots){
      if (r.first < 0)r.first += width;
      if (r.second< 0)r.second += height;
   }
   int MH = std::floor(height/2.0);
   int MW = std::floor(width/2);
   int upLeft = 0, upRight = 0, downLeft = 0, downRight = 0;
   for (auto [px, py] : robots){
      if (px == MW || py == MH) continue;
      if (py < MH){
         if (px < MW) upLeft++;
         else upRight++;
      }
      else {
         if (px < MW) downLeft++;
         else downRight++;
      }
   }
   return upLeft*upRight*downLeft*downRight;
}
int part2(std::vector<std::string> inp){
   int width = 101, height = 103;
   std::regex number_regex(R"(-?\d+)");
   int i = 0;
   while (true && i < 9000){
      bool found = false;
      i++;
      std::vector<std::pair<int, int>> robots;
      for (std::string block : inp){
         std::vector<int> numbers;
         for (std::sregex_iterator it(block.begin(), block.end(), number_regex), end; it != end; ++it) {
            numbers.push_back(std::stoi(it->str()));
         }

         robots.push_back({
            (numbers[0]+numbers[2]*i)%width,
            (numbers[1]+numbers[3]*i)%height
         });
      }
      for (auto& r : robots){
         if (r.first < 0)r.first += width;
         if (r.second< 0)r.second += height;
      }
      for (int j = 0; j < robots.size(); ++j){
         for (int k = 0; k < robots.size(); ++k){
            if (j != k){
               if (robots[j].first == robots[k].first && robots[j].second == robots[k].second){
                  found = true;
               }
            }
         }
      }
      if (!found) return i;
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
