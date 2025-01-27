#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::map<std::string, bool> known;
std::map<std::string, std::vector<std::string>> formulas;
bool calc(std::string wire){
   if (known.find(wire) != known.end()) return known[wire];
   std::string op = formulas[wire][0];
   std::string x = formulas[wire][1];
   std::string y = formulas[wire][2];
   if (op == "OR "){ known[wire] = calc(x) | calc(y); }
   else if (op == "AND"){ known[wire] = calc(x) & calc(y); }
   else if (op == "XOR"){ known[wire] = calc(x) ^ calc(y); }

   return known[wire];
}

long long part1(std::vector<std::string> inp){
   int index = 0;
   for (std::string s : inp) {
      index++;
      if (s == "") break;
      known[s.substr(0, 3)] = s[5]=='1'?true:false;
   }
   for (int i = index;i< inp.size(); ++i){
      std::string s = inp[i];
      if (s[4] == 'O') s.insert(7, 1, ' ');
      std::string x = s.substr(0, 3);
      std::string op = s.substr(4, 3);
      std::string y = s.substr(8, 3);
      std::string z = s.substr(15, 3);
      formulas[z] = {op, x, y};
   }
   for (auto [wire, form] : formulas){
      calc(wire);
   }
   std::string strResult = "";
   for (auto [wire, value] : known){
      if (wire[0] != 'z') continue;
      if (value == true) strResult += '1';
      else strResult += '0';
   }
   std::reverse(strResult.begin(), strResult.end());
   return std::stoll(strResult, nullptr, 2);
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
