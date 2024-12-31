#include <cassert>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::string part1(std::vector<std::string> inp){
   int a = std::stoi(inp[0].substr(12));
   int b = std::stoi(inp[1].substr(12));
   int c = std::stoi(inp[2].substr(12));
   std::vector<int> program;
   for (int i = 9; i < inp[4].size(); i+=2){ program.push_back(inp[4][i]-'0'); }
   int pointer = 0;
   std::vector<int> output;
   std::function combo = [&a,&b,&c](int op){
      switch (op) {
         case 4: return a;break; 
         case 5: return b;break; 
         case 6: return c;break; 
         default: return op;break; 
      }
   };
   while (pointer < program.size()){
      int ins = program[pointer];
      int operand = program[pointer+1];
      switch (ins) {
         case 0: a = a >> combo(operand);break; // adv
         case 1: b = b ^ operand;break; // bxl
         case 2: b = combo(operand)%8;break; // bst
         case 3: if (a != 0) {pointer = operand; continue;};break; // jnz
         case 4: b = b ^ c;break; // bxc
         case 5: output.push_back(combo(operand)%8);break; // out
         case 6: b = a >> combo(operand);break; // bdv
         case 7: c = a >> combo(operand);break; // cdv
      }
      pointer+=2;
   }
   std::string result = "";
   for (int i : output){
      result += std::to_string(i) + ',';
   }
   result.back() = ' ';
   return result; 
}
std::vector<int> program2;
int find(std::vector<int> target, int ans){
   std::cout << ans << std::endl;
   if (target.empty()) return ans;
   for (int t = 0; t < 8; ++t){
      int a = ans << 3 | t;
      int b = 0;
      int c = 0;
      int* output = nullptr;
      bool adv3 = false;
      std::function combo = [&a,&b,&c](int op){
         switch (op) {
            case 4: return a;break; 
            case 5: return b;break; 
            case 6: return c;break; 
            default: return op;break; 
         }
      };
      for (int pointer = 0; pointer < target.size()-2; pointer += 2){
         int ins = program2[pointer];
         int operand = program2[pointer+1];
         if (ins == 0){
            assert(operand == 3);
            assert(!adv3);
            adv3 = true;
         }
         else if (ins == 1){
            b = b ^ operand;
         }
         else if (ins == 2){
            b = combo(operand)%8;
         }
         else if (ins == 3){
            throw std::logic_error("JNZ in body of loop");
         }
         else if (ins == 4){
            b = b ^ c;
         }
         else if (ins == 5){
            assert(output == nullptr);
            int temp = combo(operand)%8;
            output = &temp;
         }
         else if (ins == 6){
            b = a >> combo(operand);
         }
         else if (ins == 7){
            c = a >> combo(operand);
         }
         if (*output == target.back()){
            std::vector<int> target2;
            for (int i = 0; i < target.size()-1; ++i) target2.push_back(target[i]);
            int sub = find(target2, a);
            if (sub == -1)continue;
            return sub;
         }
      }
   }
   return -1;
}
long long part2(std::vector<std::string> inp, long long ans){
   std::vector<int> program;
   for (int i = 9; i < inp[4].size(); i+=2){ program.push_back(inp[4][i]-'0'); }
   if (program.empty()) return ans;
   program2 = program;
   std::cout << find(program, 2024) << std::endl;
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
   std::cout << "Part 2: " << part2(input, 0) << std::endl;
   return 0;
}
