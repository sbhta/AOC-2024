#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

int part1(std::vector<std::string> inp){
   std::regex pattern(R"(mul\(\d+,\d+\))");
   std::vector<std::string> mults;
   for (std::string s : inp){
      for (std::sregex_iterator it(s.begin(), s.end(), pattern), end_it; it != end_it; ++it) {
         mults.push_back(it->str()); 
      }
   }
   int result = 0;
   for (std::string s : mults){
      std::string a;
      std::string b;
      bool change = true;
      for (int i = 4; i < s.length()-1; ++i){
         if (s[i] == ',') change = false;
         else change?a+=s[i]:b+=s[i];
      }
      result += std::stoi(a)*std::stoi(b);
   }

   return result;
}
int part2(std::vector<std::string> inp){
   std::regex pattern(R"(mul\(\d+,\d+\)|do\(\)|don't\(\))");
   std::vector<std::string> cmds;
   for (std::string s : inp){
      for (std::sregex_iterator it(s.begin(), s.end(), pattern), end_it; it != end_it; ++it) {
         cmds.push_back(it->str()); 
      }
   }
   int result = 0;
   bool Do = true;
   for (std::string s : cmds){
      if (s[2] == 'n') Do = false;
      if (s[2] == '(') Do = true;
      if (Do && s[2] == 'l'){
         std::string a;
         std::string b;
         bool change = true;
         for (int i = 4; i < s.length()-1; ++i){
            if (s[i] == ',') change = false;
            else change?a+=s[i]:b+=s[i];
         }
         result += std::stoi(a)*std::stoi(b);
      }
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
