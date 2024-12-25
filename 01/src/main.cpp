#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int part1(std::vector<std::string> inp){
   int result = 0;
   std::vector<int> arr1;
   std::vector<int> arr2;
   for (std::string s : inp){
      std::string nS = "";
      for (char ch : s){
         if (ch == ','){
            arr1.push_back(std::stoi(nS));
            nS = "";
         }
         else {nS += ch;}
      }
      arr2.push_back(std::stoi(nS));
   }
   std::stable_sort(arr1.begin(), arr1.end());
   std::stable_sort(arr2.begin(), arr2.end());
   for (int i = 0; i < arr1.size(); ++i){
      result += std::abs(arr1[i]-arr2[i]);
   }
   return result;
}
int part2(std::vector<std::string> inp){
   int result = 0;
   std::vector<int> arr1;
   std::vector<int> arr2;
   bool rightSide = true;
   for (std::string s : inp){
      std::string nS = "";
      for (char ch : s){
         if (ch == ','){
            arr1.push_back(std::stoi(nS));
            nS = "";
         }
         else {nS += ch;}
      }
      arr2.push_back(std::stoi(nS));
   }
   for (int left : arr1){
      int count = 0;
      for (int right : arr2){
         if (right == left){
            count++;
         }
      }
      result += count*left;
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
   std::cout << "Part 2: " << part2(input) << std::endl;

   return 0;
}
