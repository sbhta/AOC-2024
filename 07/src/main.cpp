#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <cmath>


bool hasSolution(std::pair<long long, std::vector<int>> eq){
   long long value = eq.first;
   std::vector<int> nums = eq.second;
   std::vector<char> ops;
   for (int i = 0; i < nums.size()-1; ++i){ ops.push_back('+'); }
   long long sum = 0;
   for (int i = 0; i < nums.size(); ++i) {sum += nums[i];}
   if (sum == value) return true;

   for (int i = 0; i < ops.size(); ++i){
      ops[i] = '*';
      do {
         long long r = nums[0];
         for (int j = 0; j < ops.size(); ++j){
            if (ops[j] == '+') r += nums[j+1];
            if (ops[j] == '*') r *= nums[j+1];
         }
         if (r == value) return true;
      }while(std::next_permutation(ops.begin(), ops.end()));
   }

   return false;
}

// Helper function to generate all permutations with replacements
void generatePermutationsWithReplacements(std::vector<char>& input, std::vector<std::vector<char>>& results) {
    // Sort the input to start with the lexicographically smallest arrangement
    std::sort(input.begin(), input.end());
    
    do {
        // Generate all replacements for the current arrangement
        size_t size = input.size();
        size_t combinations = std::pow(3, size); // 3 choices for each character ('+', '*', '|')
        std::vector<char> current = input;

        for (size_t i = 0; i < combinations; ++i) {
            size_t temp = i;
            for (size_t j = 0; j < size; ++j) {
                // Map temp value to '+', '*', or '|'
                switch (temp % 3) {
                    case 0: current[j] = '+'; break;
                    case 1: current[j] = '*'; break;
                    case 2: current[j] = '|'; break;
                }
                temp /= 3;
            }
            results.push_back(current);
        }
    } while (std::next_permutation(input.begin(), input.end())); // Generate the next permutation
}
bool hasSolution2(std::pair<long long, std::vector<int>> eq){
   long long value = eq.first;
   std::vector<int> nums = eq.second;
   long long sum = 0;
   for (int i = 0; i < nums.size(); ++i) {sum += nums[i];}
   if (sum == value) return true;

   std::vector<char> ops;
   for (int i = 0; i < nums.size()-1; ++i){ ops.push_back('+'); }

   std::vector<std::vector<char>> opsPerms;
   generatePermutationsWithReplacements(ops, opsPerms);
   std::set<std::vector<char>> SetopsPerms(opsPerms.begin(), opsPerms.end());
   for (auto x : SetopsPerms){
      for (auto y : x){
         std::cout << y << ' ';
      }
      std::cout << std::endl;
   }
   for (auto operators : SetopsPerms){
      long long r = nums[0];
      for (int j = 0; j < operators.size(); ++j){
         if (operators[j] == '+') r += nums[j+1];
         else if (operators[j] == '*') r *= nums[j+1];
         else if (operators[j] == '|') {
            std::string rS = std::to_string(r);
            std::string nS = std::to_string(nums[j+1]);
            std::string res = rS + nS;
            r = std::stoll(res);
         }
      }
      if (r == value) return true;
   }

   return false;
}
long long part1(std::vector<std::string> inp){
   std::vector<std::pair<long long, std::vector<int>>> equations;
   for (std::string s : inp){
      std::string temp = "";
      std::pair<long long, std::vector<int>> eq;
      for (char c : s) {
         if (c == ':') {eq.first = std::stoll(temp); temp = "";}
         else if (c == ' ') {eq.second.push_back(std::stoi(temp)); temp = "";}
         else temp += c;
      }
      eq.second.push_back(std::stoi(temp));
      equations.push_back(eq);
   }
   long long sum = 0;
   for (auto eq : equations){
      if (hasSolution(eq)) sum += eq.first;
   }

   return sum;
}
long long part2(std::vector<std::string> inp){
   std::vector<std::pair<long long, std::vector<int>>> equations;
   for (std::string s : inp){
      std::string temp = "";
      std::pair<long long, std::vector<int>> eq;
      for (char c : s) {
         if (c == ':') {eq.first = std::stoll(temp); temp = "";}
         else if (c == ' ') {eq.second.push_back(std::stoi(temp)); temp = "";}
         else temp += c;
      }
      eq.second.push_back(std::stoi(temp));
      equations.push_back(eq);
   }
   long long sum = 0;
   for (auto eq : equations){
      if (hasSolution2(eq)) {std::cout << '-' << eq.first << std::endl; sum += eq.first;}
      std::cout << std::endl;
   }
   //int a = 4;
   //if (hasSolution2(equations[a])) {std::cout << '-' << equations[a].first << std::endl;}

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
   std::cout << "aaa" << std::endl;
   std::cout << "Part 2: " << part2(input) << std::endl;
   return 0;
}
