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
    int length = input.size();
    int combinations = std::pow(3, length); // 3 choices for each operator: '+', '*', '|'

    for (int i = 0; i < combinations; ++i) {
        std::vector<char> current(length);
        int temp = i;
        for (int j = 0; j < length; ++j) {
            switch (temp % 3) {
                case 0: current[j] = '+'; break;
                case 1: current[j] = '*'; break;
                case 2: current[j] = '|'; break;
            }
            temp /= 3;
        }
        results.push_back(current);
    }
}
bool hasSolution2(std::pair<long long, std::vector<int>> eq) {
    long long value = eq.first;
    std::vector<int> nums = eq.second;

    // Quick check using the sum of all numbers
    long long sum = 0;
    for (int num : nums) {
        sum += num;
    }
    if (sum == value) {
        return true;
    }

    // Generate all operator combinations
    std::vector<char> ops(nums.size() - 1, '+');
    std::vector<std::vector<char>> opsPerms;
    generatePermutationsWithReplacements(ops, opsPerms);

    // Evaluate each operator combination
    for (const auto& operators : opsPerms) {
        long long r = nums[0];
        for (size_t j = 0; j < operators.size(); ++j) {
            if (operators[j] == '+') {
                r += nums[j + 1];
            } else if (operators[j] == '*') {
                r *= nums[j + 1];
            } else if (operators[j] == '|') {
                std::string rS = std::to_string(r);
                std::string nS = std::to_string(nums[j + 1]);
                r = std::stoll(rS + nS);
            }
        }
        if (r == value) {
            return true;
        }
    }

    return false;
}
long long part1(std::vector<std::string> inp){
   std::vector<std::pair<long long, std::vector<int>>> equations;
   for (std::string s : inp){
      s.erase(s.find(' '), 1);
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

    // Parse input into equations
    for (std::string s : inp) {
        s.erase(s.find(' '), 1);
        std::string temp = "";
        std::pair<long long, std::vector<int>> eq;

        for (char c : s) {
            if (c == ':') {
                eq.first = std::stoll(temp);
                temp = "";
            } else if (c == ' ') {
                eq.second.push_back(std::stoi(temp));
                temp = "";
            } else {
                temp += c;
            }
        }
        eq.second.push_back(std::stoi(temp));
        equations.push_back(eq);
    }

    long long sum = 0;

    // Evaluate each equation
    for (const auto& eq : equations) {
        if (hasSolution2(eq)) {
            sum += eq.first;
        }
    }

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
   std::cout << "Part 2: " << part2(input) << std::endl;
   return 0;
}
