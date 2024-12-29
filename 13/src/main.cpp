#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
struct ClawMachine {
   std::pair<long long, long long> A;
   std::pair<long long, long long> B;
   std::pair<long long, long long> prize;
};
std::regex number_regex(R"(\d+)");
ClawMachine getMachine(std::string block){
   std::vector<long long> numbers;
   for (std::sregex_iterator it(block.begin(), block.end(), number_regex), end; it != end; ++it) {
      numbers.push_back(std::stoll(it->str()));
   }
   return {{numbers[0], numbers[1]},{numbers[2], numbers[3]},{numbers[4], numbers[5]}};
}
long long part1(std::vector<std::string> inp){
   std::string temp = "";
   std::vector<ClawMachine> machines;
   for (std::string s : inp){
      if (s == "") {
         machines.push_back(getMachine(temp));
         temp = "";
      }
      else temp += s;
   }
   machines.push_back(getMachine(temp));
   long long sum = 0;
   for (ClawMachine m : machines){
      bool running = true;
      for (long long aT = 0; aT <= 100 && running; ++aT){
         for (long long bT = 0; bT <= 100; ++bT){
            if (m.prize.first == m.A.first*aT+m.B.first*bT &&
                m.prize.second == m.A.second*aT+m.B.second*bT){
               running = false;
               sum += (aT*3)+(bT);
            }
         }
      }
   }

   return sum;
}
long long part2(std::vector<std::string> inp){
   std::string temp = "";
   std::vector<ClawMachine> machines;
   for (std::string s : inp){
      if (s == "") {
         machines.push_back(getMachine(temp));
         temp = "";
      }
      else temp += s;
   }
   machines.push_back(getMachine(temp));
   long long sum = 0;
   for (ClawMachine m : machines){
      long long ax=m.A.first, ay=m.A.second, bx=m.B.first, by=m.B.second, px=m.prize.first+10000000000000, py=m.prize.second+10000000000000;
      double ca = (px*by - py*bx) / (double)(ax*by - ay*bx);
      double cb = (px - ax*ca) / bx;
      if (std::trunc(ca) == ca && std::trunc(cb) == cb){
         sum += (ca*3)+cb;
      }
   }

   return sum;
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
