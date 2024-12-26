#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>
#include <sstream>
std::vector<std::set<std::string>> findTriangles(const std::unordered_map<std::string, std::unordered_set<std::string>>& graph) {
   std::vector<std::set<std::string>> triangles;

   for (const auto& [node, neighbors] : graph) {
      for (const std::string& neighbor1 : neighbors) {
         if (graph.find(neighbor1) != graph.end()) {
            for (const std::string& neighbor2 : graph.at(neighbor1)) {
               if (neighbor2 != node && neighbors.find(neighbor2) != neighbors.end()) {
                  // Found a triangle
                  std::set<std::string> triangle = {node, neighbor1, neighbor2};
                  // Ensure the triangle is unique
                  if (std::find(triangles.begin(), triangles.end(), triangle) == triangles.end()) {
                     triangles.push_back(triangle);
                  }
               }
            }
         }
      }
   }
   return triangles;
}
bool isClique(const std::set<std::string>& nodes, const std::unordered_map<std::string, std::unordered_set<std::string>>& graph) {
   for (const std::string& node : nodes) {
      for (const std::string& other : nodes) {
         if (node != other && graph.at(node).find(other) == graph.at(node).end()) {
            return false;
         }
      }
   }
   return true;
}
std::set<std::string> findLargestClique(const std::unordered_map<std::string, std::unordered_set<std::string>>& graph) {
   std::set<std::string> largestClique;
   std::vector<std::string> nodes;
   for (const auto& [node, _] : graph) {
      nodes.push_back(node);
   }

   size_t n = nodes.size();
   // Use bitmasking to find all subsets of nodes
   for (size_t mask = 1; mask < (1 << n); ++mask) {
      std::set<std::string> subset;
      for (size_t i = 0; i < n; ++i) {
         if (mask & (1 << i)) {
            subset.insert(nodes[i]);
         }
      }
      if (subset.size() > largestClique.size() && isClique(subset, graph)) {
         largestClique = subset;
      }
   }
   return largestClique;
}
int part1(std::vector<std::string> inp){
   std::unordered_map<std::string, std::unordered_set<std::string>> pcs;
   for (std::string s : inp){
      std::string a = s.substr(0, 2), b = s.substr(3);
      pcs[a].insert(b);
      pcs[b].insert(a);
   }
   std::vector<std::set<std::string>> triangles = findTriangles(pcs);
   int count = 0;
   for (auto s : triangles){
      bool containsT = false;
      for (auto ss : s){
         if (ss[0] == 't') containsT = true;
      }
      if (containsT) count++;
   }
   return count;
}
int part2(std::vector<std::string> inp){
   std::unordered_map<std::string, std::unordered_set<std::string>> pcs;
   for (std::string s : inp){
      std::string a = s.substr(0, 2), b = s.substr(3);
      pcs[a].insert(b);
      pcs[b].insert(a);
   }
   std::set<std::string> largestClique = findLargestClique(pcs);
   std::vector<std::string> sortedClique(largestClique.begin(), largestClique.end());
   std::sort(sortedClique.begin(), sortedClique.end());
   std::ostringstream passwordStream;
   for (size_t i = 0; i < sortedClique.size(); ++i) {
      if (i > 0) {
         passwordStream << ",";
      }
      passwordStream << sortedClique[i];
   }

   std::string password = passwordStream.str();

   // Output the result
   std::cout << "Password to get into the LAN party: " << password << std::endl;
   return 0;
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
