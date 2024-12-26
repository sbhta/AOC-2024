#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

bool canMakeDesign(std::string design, std::vector<std::string> patterns){
   std::queue<std::string> q;
   q.push(design);
   std::unordered_set<std::string> visited;
   visited.insert(design);
   while (!q.empty()){
      std::string current = q.front();
      q.pop();
      for (std::string p : patterns){
         if (current.size() >= p.size() && current.substr(0, p.size()) == p){
            std::string next = current.substr(p.size());
            if (next.empty()) return true;
            if (visited.find(next) == visited.end()){
               visited.insert(next);
               q.push(next);
            }
         }
      }
   }
   return false;
}
int part1(std::vector<std::string> inp){
   // getting all patterns
   std::vector<std::string> patterns;
   std::string temp = "";
   for (char c : inp[0]){
      if (c == ',') {
         patterns.push_back(temp);
         temp = "";
      }
      else {
         c==' '?temp=temp:temp+=c;
      }
   }
   patterns.push_back(temp);
   // get all the desired designs
   std::vector<std::string> designs;
   for (int i = 2; i < inp.size(); ++i){
      designs.push_back(inp[i]);
   }
   
   int count = 0;
   for (std::string s : designs){
      if (canMakeDesign(s, patterns)) count++;
   }

   return count;
}
long long countPossibleDesigns(std::string& design, std::vector<std::string>& patterns){
   // Use a map to store the number of ways to create each substring of the design
   std::unordered_map<std::string, long long> ways;
   ways[""] = 1; // Base case: one way to create an empty string

   // Iterate through the design from the end towards the start
   for (long long i = design.size(); i >= 0; --i) {
      std::string current = design.substr(i);

      for (const std::string& pattern : patterns) {
         if (current.size() >= pattern.size() && current.substr(0, pattern.size()) == pattern) {
            std::string next = current.substr(pattern.size());

            // Update the number of ways to create this substring
            ways[current] += ways[next];
         }
      }
   }

   // Return the number of ways to create the full design
   return ways[design];
}
long long part2(std::vector<std::string> inp){
   // getting all patterns
   std::vector<std::string> patterns;
   std::string temp = "";
   for (char c : inp[0]){
      if (c == ',') {
         patterns.push_back(temp);
         temp = "";
      }
      else {
         c==' '?temp=temp:temp+=c;
      }
   }
   patterns.push_back(temp);
   // get all the desired designs
   std::vector<std::string> designs;
   for (long long i = 2; i < inp.size(); ++i){
      designs.push_back(inp[i]);
   }
   
   long long count = 0;
   long long i = 0;
   for (std::string s : designs){
      i++;
      count += countPossibleDesigns(s, patterns);
      //std::cout << i << '/' << designs.size() << std::endl;
   }

   return count;
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
