#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int part1(std::vector<std::string> inp){
   std::vector<std::vector<int>> locks, keys;
   std::vector<std::vector<std::string>> tempVector;
   std::vector<std::string> temp;
   for (std::string s : inp){ if (s == "") {tempVector.push_back(temp); temp.clear();} else { temp.push_back(s); } } tempVector.push_back(temp);
   for (std::vector<std::string> v : tempVector){
      if (v[0] == "#####"){
         std::vector<int> l = {0, 0, 0, 0, 0};
         for (int row = 1; row < v.size(); ++row){
            for (int i = 0; i < 5; ++i){
               if (v[row][i] == '#') l[i]++;
            }
         }
         locks.push_back(l);
      }
      else {
         std::vector<int> k = {5, 5, 5, 5, 5};
         for (int row = 1; row < v.size(); ++row){
            for (int i = 0; i < 5; ++i){
               if (v[row][i] == '.') k[i]--;
            }
         }
         keys.push_back(k);
      }
   }
   int result = 0;
   for (auto k : keys){
      for (auto l : locks){
         bool fits = true;
         for (int i = 0; i < 5; ++i){
            if (k[i]+l[i] > 5) fits = false;
         }
         if (fits) result++;
      }
   }
   return result;
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
   return 0;
}
