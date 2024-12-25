#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

bool isUpdateCorrect(std::map<int, std::vector<int>> rules, std::vector<int> update){
   for (int i = 0; i < update.size(); ++i){
      std::vector<int> containedRules;
      for (int num : rules[update[i]]){
         if (std::count(update.begin(), update.end(), num) > 0) containedRules.push_back(num);
      }
      for (int j = 0; j < i; ++j){
         if (std::count(containedRules.begin(), containedRules.end(), update[j]) > 0) return false;
      }
   }
   return true;
}
std::vector<int> correctUpdate(std::map<int, std::vector<int>> rules, std::vector<int> update){
   // Create the subgraph for the current update
   std::map<int, std::vector<int>> subgraph;
   std::map<int, int> inDegree; // Keep track of in-degrees for topological sort

   for (int page : update) {
      subgraph[page] = {}; // Ensure all nodes are included in the graph
      inDegree[page] = 0;  // Initialize in-degree
   }

   // Populate subgraph and in-degrees
   for (int page : update) {
      if (rules.count(page) > 0) {
         for (int neighbor : rules[page]) {
            if (std::count(update.begin(), update.end(), neighbor) > 0) {
               subgraph[page].push_back(neighbor);
               inDegree[neighbor]++;
            }
         }
      }
   }

   // Topological sort using Kahn's algorithm
   std::vector<int> sortedUpdate;
   std::queue<int> zeroInDegree;
   for (const auto& [node, degree] : inDegree) {
      if (degree == 0) zeroInDegree.push(node);
   }

   while (!zeroInDegree.empty()) {
      int current = zeroInDegree.front();
      zeroInDegree.pop();
      sortedUpdate.push_back(current);

      for (int neighbor : subgraph[current]) {
         inDegree[neighbor]--;
         if (inDegree[neighbor] == 0) zeroInDegree.push(neighbor);
      }
   }

   // Return the sorted update
   return sortedUpdate;
}

int part1(std::vector<std::string> inp){
   std::map<int, std::vector<int>> rules;
   std::vector<std::vector<int>> updatesVector;
   bool gettingRules = true;
   for (std::string s : inp){
      if (s == "") {gettingRules = false; continue;}
      else {
         if (gettingRules){
            int x = std::stoi(s.substr(0,2));
            int y = std::stoi(s.substr(3,2));
            if (rules.count(x) > 0) {
               rules[x].push_back(y);
            }
            else {
               rules[x] = {y};
            }
         }
         else {
            std::vector<int> up;
            for (int i = 0; i < s.length(); i+=3){ up.push_back(std::stoi(s.substr(i, 2))); }
            updatesVector.push_back(up);
         }
      }
   }

   std::vector<std::vector<int>> correctUpdates;
   for (int i = 0; i < updatesVector.size(); ++i){
      if (isUpdateCorrect(rules, updatesVector[i])) correctUpdates.push_back(updatesVector[i]);
   }

   int result = 0;
   for (std::vector<int> update : correctUpdates){
      result += update[update.size()/2];
   }

   return result;
}
int part2(std::vector<std::string> inp){
   std::map<int, std::vector<int>> rules;
   std::vector<std::vector<int>> updatesVector;
   bool gettingRules = true;
   for (std::string s : inp){
      if (s == "") {gettingRules = false; continue;}
      else {
         if (gettingRules){
            int x = std::stoi(s.substr(0,2));
            int y = std::stoi(s.substr(3,2));
            if (rules.count(x) > 0) {
               rules[x].push_back(y);
            }
            else {
               rules[x] = {y};
            }
         }
         else {
            std::vector<int> up;
            for (int i = 0; i < s.length(); i+=3){ up.push_back(std::stoi(s.substr(i, 2))); }
            updatesVector.push_back(up);
         }
      }
   }

   std::vector<std::vector<int>> incorrectUpdates;
   std::vector<std::vector<int>> correctUpdates;
   for (int i = 0; i < updatesVector.size(); ++i){
      if (!isUpdateCorrect(rules, updatesVector[i])) incorrectUpdates.push_back(updatesVector[i]);
   }
   for (int i = 0; i < incorrectUpdates.size(); ++i){
      correctUpdates.push_back(correctUpdate(rules, incorrectUpdates[i]));
   }

   int result = 0;
   for (std::vector<int> update : correctUpdates){
      result += update[update.size()/2];
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
