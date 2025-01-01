#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

long long mix(long long secretNumber, long long mixNumber){ return (secretNumber^mixNumber); }
long long prune(long long secretNumber){ return (secretNumber%16777216); }
void evolveNumber(long long& sN){
   sN = prune(mix(sN,sN*64)); // step 1
   sN = prune(mix(sN,sN/32));   // step 2
   sN = prune(mix(sN,sN*2048)); // step 3
}

std::map<std::vector<int>, int> seqToTotal;
long long part1(std::vector<std::string> inp){
   std::vector<long long> secretNumbers;
   for (std::string s : inp){ secretNumbers.push_back(std::stoll(s)); }
   for (long long& num : secretNumbers){
      std::vector<int> buyer = {(int)(num%10)};
      for (int i = 0; i < 2000; ++i){
         evolveNumber(num);
         buyer.push_back((int)(num%10));
      }
      std::set<std::vector<int>> seen;
      for (int i = 0; i < buyer.size()-4; ++i){
         auto [a, b, c, d, e] = std::tuple<int, int, int, int, int>{buyer[i+0],buyer[i+1],buyer[i+2],buyer[i+3],buyer[i+4]};
         std::vector<int> seq = {b-a, c-b, d-c, e-d};
         if (seen.find(seq) != seen.end()) continue;
         seen.insert(seq);
         seqToTotal[seq] += e;
      }
   }
   long long result = 0;
   for (long long& n : secretNumbers){
      result += n;
   }
   return result;
}
long long part2(std::vector<std::string> inp){
   int max = -1;
   for (auto [seq, total] : seqToTotal){
      if (total > max) max = total;
   }
   return max;
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
