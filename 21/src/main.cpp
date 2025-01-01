#include <algorithm>
#include <cmath>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::vector<std::vector<char>> numKeypad = {
   {'7', '8', '9'},
   {'4', '5', '6'},
   {'1', '2', '3'},
   {' ', '0', 'A'},
};
std::vector<std::vector<char>> dirKeypad = {
   {' ', '^', 'A'},
   {'<', 'v', '>'}
};
struct Seq {
   
};
std::vector<std::string> cartesianProduct(const std::vector<std::vector<std::string>>& input) {
    std::vector<std::string> result = {""};
    for (const auto& group : input) {
        std::vector<std::string> temp;
        for (const auto& item : group) {
            for (const auto& current : result) {
                temp.push_back(current + item);
            }
        }
        result = std::move(temp);
    }
    return result;
}
std::vector<std::string> solve1(std::string string, std::vector<std::vector<char>> keypad){
   std::map<char, std::pair<int, int>> pos;
   for (int r = 0; r < keypad.size(); ++r){
      for (int c = 0; c < keypad[0].size(); ++c){
         if (keypad[r][c] != ' ') pos[keypad[r][c]] = {r, c};
      }
   }
   std::map<std::pair<std::pair<int,int>, std::pair<int, int>>, std::vector<std::string>> seqs;
   for (auto x : pos){
      for (auto y : pos){
         if (x.second == y.second){
            seqs[{x.second, y.second}] = {"A"};
            continue;
         }
         std::vector<std::string> possibilities;
         std::deque<std::pair<std::pair<int,int>, std::string>> q = {{x.second, ""}};
         double optimal = INFINITY;
         bool run = true;
         while (!q.empty() && run){
            auto [r, c] = q.front().first;
            auto moves = q.front().second;
            q.pop_front();
            for (auto [nr, nc, nm] : std::vector<std::tuple<int, int, char>>{{r-1,c,'^'},{r+1,c,'v'},{r,c+1,'>'},{r,c-1,'<'}}){
               if (nr < 0 || nc < 0 || nr >= keypad.size() || nc >= keypad[0].size()) continue;
               if (keypad[nr][nc] == ' ') continue;
               if (keypad[nr][nc] == y.first){
                  if (optimal < moves.length()+1){
                     run = false;
                     break;
                  }
                  optimal = moves.length()+1;
                  possibilities.push_back(moves+nm+'A');
               }
               else {
                  q.push_back({{nr, nc}, moves+nm});
               }
            }
         }
         seqs[{x.second, y.second}] = possibilities;
      }
   }

   std::vector<std::vector<std::string>> options;
   std::string str = 'A'+string;
   for (int i = 0; i < str.length()-1; ++i){
      options.push_back(seqs[{pos[str[i]], pos[str[i+1]]}]);
   }
   return cartesianProduct(options);
}
int part1(std::vector<std::string> codes){
   int total = 0;
   for (std::string code : codes){
      auto robot1 = solve1(codes[0], numKeypad);
      auto next = robot1;
      for (int i = 0; i < 2; ++i){
         std::vector<std::vector<std::string>> possibleNext;
         for (auto seq : next){ possibleNext.push_back(solve1(seq, dirKeypad)); }
         auto minlen = std::min_element(possibleNext.begin(), possibleNext.end(),
                                        [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                                        return a.size() < b.size();
                                        })->size();
         std::vector<std::vector<std::string>> nextTemp;
         for (auto seq : possibleNext){
            if (seq.size() == minlen) nextTemp.push_back(seq);
         }
         next = nextTemp[0];
      }
      total += next[0].length() * std::stoi(codes[0].substr(0, codes[0].length()-1));
   }
   return total;
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
