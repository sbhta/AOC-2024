#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int part1(std::string fileName){
   int result = 0;
   std::vector<int> arr1;
   std::vector<int> arr2;
   std::ifstream file(fileName);
   std::string temp;

   while (std::getline(file, temp)){
      std::string nS = "";
      for (char ch : temp){
         if (ch == ','){
            arr1.push_back(std::stoi(nS));
            nS = "";
         }
         else {nS += ch;}
      }
      arr2.push_back(std::stoi(nS));
   }
   file.close();
   std::stable_sort(arr1.begin(), arr1.end());
   std::stable_sort(arr2.begin(), arr2.end());
   for (int i = 0; i < arr1.size(); ++i){
      result += std::abs(arr1[i]-arr2[i]);
   }
   return result;
}
int part2(std::string fileName){
int result = 0;
   std::vector<int> arr1;
   std::vector<int> arr2;
   std::ifstream file(fileName);
   std::string temp;

   bool rightSide = true;
   while (std::getline(file, temp)){
      std::string nS = "";
      for (char ch : temp){
         if (ch == ','){
            arr1.push_back(std::stoi(nS));
            nS = "";
         }
         else {nS += ch;}
      }
      arr2.push_back(std::stoi(nS));
   }
   file.close();
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
   std::cout << "sample:\npart 1:";
   std::cout << part1(argv[1]) << std::endl;
   std::cout << "part 2:";
   std::cout << part2(argv[1]) << std::endl;
   std::cout << "input:\npart 1:";
   std::cout << part1(argv[2]) << std::endl;
   std::cout << "part 2:";
   std::cout << part2(argv[2]) << std::endl;
   return 0;
}
