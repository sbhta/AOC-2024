#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Gate {
   std::string output;
   std::string input1;
   std::string input2;
   char op;
};
bool check_key(std::map<std::string, bool> m, std::string key)
{
    // Key is not present
    if (m.find(key) == m.end())
        return false;
    return true;
}
long long part1(std::vector<std::string> inp){
   std::map<std::string, bool> wires;
   size_t start = 0;
   for (std::string s : inp){
      start++;
      if (s == "") break;
      wires[s.substr(0,3)] = (s[5]=='1');
   }
   std::vector<Gate> gates;
   for (long long i = start; i < inp.size(); ++i){
      Gate g;
      switch (inp[i][4]) {
         case 'X': g.input1=inp[i].substr(0, 3);g.input2=inp[i].substr(8,3);g.op='^';g.output=inp[i].substr(15,3);break;
         case 'A': g.input1=inp[i].substr(0, 3);g.input2=inp[i].substr(8,3);g.op='&';g.output=inp[i].substr(15,3);break;
         case 'O': g.input1=inp[i].substr(0, 3);g.input2=inp[i].substr(7,3);g.op='|';g.output=inp[i].substr(14,3);break;
      }
      gates.push_back(g);
   }
   size_t index = 0;
   std::vector<size_t> foundValues;
   while (foundValues.size() < gates.size()){
      if (std::count(foundValues.begin(), foundValues.end(), index) > 0) {index++;continue;}
      if (check_key(wires, gates[index].input1)){
         if (wires.find(gates[index].input2) != wires.end()){
            foundValues.push_back(index);
            switch (gates[index].op) {
               case '^': wires[gates[index].output] = (wires[gates[index].input1]^wires[gates[index].input2]);break;
               case '&': wires[gates[index].output] = (wires[gates[index].input1]&wires[gates[index].input2]);break;
               case '|': wires[gates[index].output] = (wires[gates[index].input1]|wires[gates[index].input2]);break;
            }
         }
      }
      index++;
      if (index >= gates.size()) index = 0;
   }
   std::string resultString = "";
   for (auto [name, value] : wires){ if (name[0] == 'z') resultString+=std::to_string(value); }
   std::string resultString2 = "";
   for (long long i = resultString.length()-1; i >= 0; --i){ resultString2 += resultString[i]; }
   long long result = std::stoll(resultString2, nullptr, 2);
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
   //std::cout << "Part 2: " << part2(input) << std::endl;
   return 0;
}
