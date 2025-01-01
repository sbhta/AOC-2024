#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>
std::map<std::string, std::set<std::string>> conns;
int part1(std::vector<std::string> inp){
   std::vector<std::pair<std::string, std::string>> edges;
   for (std::string s : inp){ edges.push_back({s.substr(0, 2), s.substr(3)}); }
   for (auto [x, y] : edges){
      if (conns.find(x) == conns.end()) conns[x] = {};
      if (conns.find(y) == conns.end()) conns[y] = {};
      conns[x].insert(y);
      conns[y].insert(x);
   }
   std::set<std::tuple<std::string, std::string, std::string>> sets;
   for (auto x : conns){
      for (auto y : conns[x.first]){
         for (auto z : conns[y]){
            if (x.first != z && conns[z].find(x.first) != conns[z].end()){
               std::vector<std::string> arr(3);
               arr = {x.first, y, z};
               std::sort(arr.begin(), arr.end());
               sets.insert(std::make_tuple(arr[0], arr[1], arr[2]));
            }
         }
      }
   }
   int count = 0;
   for (auto s : sets){
      if (std::get<0>(s)[0] == 't' || std::get<1>(s)[0] == 't' || std::get<2>(s)[0] == 't'){
         count++;
         continue;
      }
   }
   return count;
}
std::set<std::set<std::string>> sets2;
void search(std::string& node, std::set<std::string> req){
   std::vector<std::string> temp; for (std::string s : req) temp.push_back(s);
   std::sort(temp.begin(), temp.end());
   std::set<std::string> sorted(temp.begin(), temp.end());
   if (sets2.find(sorted) != sets2.end()) return;
   sets2.insert(sorted);
   for (auto neighbor : conns[node]){
      if (req.find(neighbor) != req.end()) continue;
      if (!std::all_of(req.begin(), req.end(), [&](const auto& query) { return conns[query].find(neighbor) != conns[query].end(); })) continue;
      auto req2 = req;
      req2.insert(neighbor);
      search(neighbor, req2);
   }
}
std::string part2(std::vector<std::string> inp){
   for (auto x : conns){
      std::string x1 = x.first;
      search(x1, {x.first});
   }
   std::set<std::string> max;
   for (auto x : sets2){
      if (x.size() > max.size()) max = x;
   }
   std::string result = "";
   for (std::string s : max){
      result += s +',';
   }
   return result.substr(0, result.length()-1);
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
