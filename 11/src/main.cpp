#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <cmath>
std::vector<long long> splitNumber(long long number) {
    // Count the digits
    int numDigits = static_cast<int>(std::log10(number)) + 1;

    // Calculate the divisor
    long long divisor = std::pow(10, numDigits / 2);

    // Split the number
    long long firstHalf = number / divisor;
    long long secondHalf = number % divisor;

    return {firstHalf, secondHalf};
}
bool hasEvenNumberOfDigits(long long number) {
    if (number == 0) {
        return false; // 0 has 1 digit, which is odd
    }
    int numDigits = static_cast<int>(std::log10(number)) + 1;
    return numDigits % 2 == 0;
}
std::vector<unsigned long long> evolveStones(std::vector<unsigned long long> stones){
   std::vector<unsigned long long> result;
   for (unsigned long long s : stones){
      if (s == 0) result.push_back(1);
      else if (hasEvenNumberOfDigits(s)) {
         std::vector<long long> twoS = splitNumber(s);
         result.push_back(twoS[0]);
         result.push_back(twoS[1]);
      }
      else {
         result.push_back(s*2024);
      }
   }
   return result;
}

// defining the functions in advance
long long countDescendants(long long num, int iterations);
long long fullCountDescendants(long long num, int iterations);
long long countDescendants(std::vector<long long> numbers, int iterations);
std::vector<long long> expand(long long num);

static std::map<std::tuple<long long, int>, long long> myCache;
long long countDescendants(std::vector<long long> numbers, int iterations){
   long long result = 0;
   for (long long num : numbers){
      result += countDescendants(num,iterations);
   }
   return result;
}
long long countDescendants(long long num, int iterations){
   if (myCache.find({num, iterations}) != myCache.end()){
      return myCache[{num, iterations}];
   }
   else{
      myCache[{num, iterations}] = fullCountDescendants(num, iterations);
      return myCache[{num, iterations}];
   }
}
long long fullCountDescendants(long long num, int iterations){
      if (iterations == 0) return 1;
      else {return countDescendants(expand(num),iterations-1);}
}
std::vector<long long> expand(long long num){
   if (num == 0) return {1};
   else {
      if (hasEvenNumberOfDigits(num)){
         return splitNumber(num);
      }
      else {
         return {num*2024};
      }
   }
}

long long part1(std::vector<std::string> inp){
   std::vector<unsigned long long> stones;
   std::string temp = "";
   for (char c : inp[0]){
      if (c == ' '){
         stones.push_back(std::stoull(temp));
         temp = "";
      }
      else temp += c;
   }
   stones.push_back(std::stoull(temp));
   for (int i = 0; i < 25; ++i){
      stones = evolveStones(stones);
   }
   return stones.size();
}
long long part2(std::vector<std::string> inp){
   std::vector<long long> stones;
   std::string temp = "";
   for (char c : inp[0]){
      if (c == ' '){
         stones.push_back(std::stoull(temp));
         temp = "";
      }
      else temp += c;
   }
   stones.push_back(std::stoull(temp));
   
   return countDescendants(stones, 75);
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
