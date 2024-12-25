#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

void adv(int& regA, int operand){ regA = regA/std::pow(2,operand);} //operand is combo
void bxl(int& regB, int operand){ regB = regB^operand;} // operand is literal
void bst(int& regB, int operand){ regB = operand%8;} // operand is combo
bool jnz(int regA, int& pointer, int operand) {if(regA!=0) {pointer=operand;return true;}return false;} //operand is literal
void bxc(int& regB, int regC){ regB = regB^regC;} // operand is a register
void bdv(int& regB, int regA, int operand){ regB = regA/std::pow(2,operand);} //operand is combo
void cdv(int& regC, int regA, int operand){ regC = regA/std::pow(2,operand);} //operand is combo

std::string part1(std::vector<std::string> inp){
   std::string result = "";
   int regA = std::stoi(inp[0].substr(12));
   int regB = std::stoi(inp[1].substr(12));
   int regC = std::stoi(inp[2].substr(12));
   std::vector<int> program;
   for (int i = 9; i < inp[4].length(); i+=2){ program.push_back(inp[4][i]-'0'); }
   int p = 0;
   while (p <= program.size()){
      std::map<int, int> combo = {
         {0, 0},
         {1, 1},
         {2, 2},
         {3, 3},
         {4, regA},
         {5, regB},
         {6, regC},
         {7, 7},
      };
      if (program[p] == 0){adv(regA, combo[program[p+1]]);p+=2;}
      else if (program[p] == 1){bxl(regB, program[p+1]);p+=2;}
      else if (program[p] == 2){bst(regB, combo[program[p+1]]);p+=2;}
      else if (program[p] == 3){ if(!jnz(regA, p, program[p+1]))p+=2;}
      else if (program[p] == 4){bxc(regB, regC);p+=2;}
      else if (program[p] == 5){ result += std::to_string(combo[program[p+1]]%8) + ','; p+=2;}
      else if (program[p] == 6){bdv(regB, regA, combo[program[p+1]]);p+=2;}
      else if (program[p] == 7){cdv(regC, regA, combo[program[p+1]]);p+=2;}
   }
   std::string actualResult = result.substr(0, result.length()-1);
   return actualResult;
}
std::string part1(std::vector<std::string> inp, int A){
   std::string result = "";
   std::cout << A << std::endl;
   int regA = A;
   int regB = std::stoi(inp[1].substr(12));
   int regC = std::stoi(inp[2].substr(12));
   std::vector<int> program;
   for (int i = 9; i < inp[4].length(); i+=2){ program.push_back(inp[4][i]-'0'); }
   int p = 0;
   int run = 0;
   while (p <= program.size() && run < 10000){
      run++;
      std::map<int, int> combo = {
         {0, 0},
         {1, 1},
         {2, 2},
         {3, 3},
         {4, regA},
         {5, regB},
         {6, regC},
         {7, 7},
      };
      if (program[p] == 0){adv(regA, combo[program[p+1]]);p+=2;}
      else if (program[p] == 1){bxl(regB, program[p+1]);p+=2;}
      else if (program[p] == 2){bst(regB, combo[program[p+1]]);p+=2;}
      else if (program[p] == 3){ if(!jnz(regA, p, program[p+1]))p+=2;}
      else if (program[p] == 4){bxc(regB, regC);p+=2;}
      else if (program[p] == 5){ result += std::to_string(combo[program[p+1]]%8) + ','; p+=2;}
      else if (program[p] == 6){bdv(regB, regA, combo[program[p+1]]);p+=2;}
      else if (program[p] == 7){cdv(regC, regA, combo[program[p+1]]);p+=2;}
   }
   std::string actualResult = "";
   for (char c : result){if(c != ',') actualResult+=c;}
   return actualResult;
}
int part2(std::vector<std::string> inp){
   int i = 0;
   std::string should = "";
   for (char c : inp[4].substr(9)) {if(c != ',')should+=c;}
      std::cout << i << std::endl;
   while (should != part1(inp, i)){
      std::cout << i << std::endl;
      i++;
   }
   return i;
}

int main (int argc, char *argv[]) {
   std::vector<std::string> sample;
   std::vector<std::string> input;
   std::string temp;
   std::ifstream fileSample(argv[1]);
   std::ifstream fileInput(argv[2]);
   while (std::getline(fileSample, temp)){sample.push_back(temp);}
   while (std::getline(fileInput, temp)){input.push_back(temp);}
   fileSample.close();
   fileInput.close();

   std::cout << part2(sample) << std::endl;
   return 0;
}
