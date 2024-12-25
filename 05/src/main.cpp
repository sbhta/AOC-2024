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

int part1(std::string fileName){
   std::map<int, std::vector<int>> rules;
   std::vector<std::vector<int>> updatesVector;
   std::ifstream file(fileName);
   std::string temp;
   bool gettingRules = true;
   while (std::getline(file, temp)){
      if (temp == "") {gettingRules = false; continue;}
      else {
         if (gettingRules){
            int x = std::stoi(temp.substr(0,2));
            int y = std::stoi(temp.substr(3,2));
            if (rules.count(x) > 0) {
               rules[x].push_back(y);
            }
            else {
               rules[x] = {y};
            }
         }
         else {
            std::vector<int> up;
            for (int i = 0; i < temp.length(); i+=3){ up.push_back(std::stoi(temp.substr(i, 2))); }
            updatesVector.push_back(up);
         }
      }
   }
   file.close();

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
int part2(std::string fileName){
   std::map<int, std::vector<int>> rules;
   std::vector<std::vector<int>> updatesVector;
   std::ifstream file(fileName);
   std::string temp;
   bool gettingRules = true;
   while (std::getline(file, temp)){
      if (temp == "") {gettingRules = false; continue;}
      else {
         if (gettingRules){
            int x = std::stoi(temp.substr(0,2));
            int y = std::stoi(temp.substr(3,2));
            if (rules.count(x) > 0) {
               rules[x].push_back(y);
            }
            else {
               rules[x] = {y};
            }
         }
         else {
            std::vector<int> up;
            for (int i = 0; i < temp.length(); i+=3){ up.push_back(std::stoi(temp.substr(i, 2))); }
            updatesVector.push_back(up);
         }
      }
   }
   file.close();

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
   std::cout << "sample part 1: ";
   std::cout << part1(argv[1]) << std::endl;
   std::cout << "input part 1: ";
   std::cout << part1(argv[2]) << std::endl;
   std::cout << "sample part 2: ";
   std::cout << part2(argv[1]) << std::endl;
   std::cout << "input part 2: ";
   std::cout << part2(argv[2]) << std::endl;
   return 0;
}
