#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

std::pair<long long, long long> parseCoordinates(const std::string& input) {
    // Find the position of "X" and determine the separator ('+' or '=')
    std::size_t xPos = input.find("X");
    std::size_t yPos = input.find("Y");

    if (xPos == std::string::npos || yPos == std::string::npos) {
        throw std::invalid_argument("Invalid format: Coordinates not found");
    }

    // Determine the separator for X and Y
    char xSeparator = input[xPos + 1];
    char ySeparator = input[yPos + 1];

    if ((xSeparator != '+' && xSeparator != '=') || (ySeparator != '+' && ySeparator != '=')) {
        throw std::invalid_argument("Invalid format: Separators not found");
    }

    // Extract the long longegers using substr and stoi
    long long x = std::stoll(input.substr(xPos + 2, yPos - (xPos + 2)));
    long long y = std::stoll(input.substr(yPos + 2));

    return {x, y};
}
bool overShot(std::pair<long long, long long> prize, long long x, long long y){
   if (x > prize.first || y > prize.second) return true;
   return false;
}
long long costOfMachine(std::tuple<std::pair<long long, long long>, std::pair<long long, long long>, std::pair<long long, long long>> machine){
   std::pair<long long, long long> A = std::get<0>(machine);
   std::pair<long long, long long> B = std::get<1>(machine);
   std::pair<long long, long long> P = std::get<2>(machine);
   for (long long i = 100; i >= 0; --i){
      if (overShot(P, B.first*i, B.second*2)){continue;}
      long long sum = i*1;
      for (long long j = 0;j <= 100; ++j){
         if (B.first*i + A.first*j == P.first && B.second*i + A.second*j == P.second){
            return sum+(j*3);
         }
         if (overShot(P, B.first*i+A.first*j, B.second*i+A.second*j)) {break;}
      }
   }
   return 0;
}
long long costOfMachine2(std::tuple<std::pair<long long, long long>, std::pair<long long, long long>, std::pair<long long, long long>> machine){
   std::pair<long long, long long> A = std::get<0>(machine);
   std::pair<long long, long long> B = std::get<1>(machine);
   std::pair<long long, long long> P = std::get<2>(machine);
   for (long long i = 100000; i >= 0; --i){
      std::cout << i << std::endl;
      if (overShot(P, B.first*i, B.second*2)){continue;}
      long long sum = i*1;
      for (long long j = 0;j <= 100; ++j){
         if (B.first*i + A.first*j == P.first && B.second*i + A.second*j == P.second){
            return sum+(j*3);
         }
         if (overShot(P, B.first*i+A.first*j, B.second*i+A.second*j)) {break;}
      }
   }
   return 0;
}
long long part1(std::vector<std::string> inp){
   std::vector<std::tuple<std::pair<long long, long long>, std::pair<long long, long long>, std::pair<long long, long long>>> machines;
   for (long long i = 0; i < inp.size(); i+=3){
      std::pair<long long, long long> A = parseCoordinates(inp[i]);
      std::pair<long long, long long> B = parseCoordinates(inp[i+1]);
      std::pair<long long, long long> P = parseCoordinates(inp[i+2]);
      machines.push_back(std::make_tuple(A, B, P));
   }
   long long finalSum = 0;
   for (long long i = 0; i < machines.size(); ++i){
      finalSum += costOfMachine(machines[i]);
   }
   return finalSum;
}
long long part2(std::vector<std::string> inp){
   std::vector<std::tuple<std::pair<long long, long long>, std::pair<long long, long long>, std::pair<long long, long long>>> machines;
   for (long long i = 0; i < inp.size(); i+=3){
      std::pair<long long, long long> A = parseCoordinates(inp[i]);
      std::pair<long long, long long> B = parseCoordinates(inp[i+1]);
      std::pair<long long, long long> P = parseCoordinates(inp[i+2]);
      P.first += 10000000000000;
      P.second += 10000000000000;
      machines.push_back(std::make_tuple(A, B, P));
   }
   long long finalSum = 0;
   for (long long i = 0; i < machines.size(); ++i){
      finalSum += costOfMachine2(machines[i]);
   }
   return finalSum;
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
