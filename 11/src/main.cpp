#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <cmath>
int getLength(long long number) {
    return static_cast<int>(std::log10(std::abs(number))) + 1;
}
std::pair<long long, long long> splitNumber(long long number) {
    int length = static_cast<int>(std::log10(number)) + 1;
    int halfLength = length / 2;
    long long divisor = static_cast<long long>(std::pow(10, halfLength));

    long long firstHalf = number / divisor;
    long long secondHalf = number % divisor;

    return {firstHalf, secondHalf};
}

std::map<long long, long long> mapSingle;
std::map<long long, std::pair<long long, long long>> mapDoubles;

void changeStones(std::vector<long long>& stones){
   for (int i = 0; i < stones.size(); ++i){
      if (stones[i] == 0) stones[i] = 1;
      else if (getLength(stones[i])%2 == 0){
         if (mapDoubles.find(stones[i]) != mapDoubles.end()){
            stones.insert(stones.begin()+i+1, mapDoubles[stones[i]].second);
            stones[i] = mapDoubles[stones[i]].first;
            i++;
         }
         else {
            mapDoubles[stones[i]] = splitNumber(stones[i]);
            stones.insert(stones.begin()+i+1, mapDoubles[stones[i]].second);
            stones[i] = mapDoubles[stones[i]].first;
            i++;
         }
      }
      else {
         if (mapSingle.find(stones[i]) != mapSingle.end()){
            stones[i] = mapSingle[stones[i]];
         }
         else {
            mapSingle[stones[i]] = stones[i]*2024;
            stones[i] = mapSingle[stones[i]];
         }
      }
   }
}

int part1(std::vector<std::string> inp){
   std::vector<long long> stones;
   std::string temp = "";
   for (char ch : inp[0]){
      if (ch == ' ') {
         stones.push_back(std::stoll(temp));
         temp = "";
      }
      else { temp += ch; }
   }
   stones.push_back(std::stoll(temp));
   for (int i = 0; i < 75; ++i){
      changeStones(stones);
      std::cout << i << std::endl;
   }

   return stones.size();
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
