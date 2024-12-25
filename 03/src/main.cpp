#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

int part1(std::string fileName){
   std::ifstream file(fileName);
   std::string temp = "";
   std::regex pattern(R"(mul\(\d+,\d+\))");
   std::vector<std::string> mults;
   while (std::getline(file, temp)){
      for (std::sregex_iterator it(temp.begin(), temp.end(), pattern), end_it; it != end_it; ++it) {
         mults.push_back(it->str()); 
      }
   }
   file.close();
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
int part2(std::string fileName){
   std::ifstream file(fileName);
   std::string temp = "";
   std::regex pattern(R"(mul\(\d+,\d+\)|do\(\)|don't\(\))");
   std::vector<std::string> cmds;
   while (std::getline(file, temp)){
      for (std::sregex_iterator it(temp.begin(), temp.end(), pattern), end_it; it != end_it; ++it) {
         cmds.push_back(it->str()); 
      }
   }
   file.close();
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
   std::cout << "sample part 1:";
   std::cout << part1(argv[1]) << std::endl;
   std::cout << "sample part 2:";
   std::cout << part2(argv[1]) << std::endl;
   std::cout << "input part 1:";
   std::cout << part1(argv[2]) << std::endl;
   std::cout << "input part 2:";
   std::cout << part2(argv[2]) << std::endl;
   return 0;
}
