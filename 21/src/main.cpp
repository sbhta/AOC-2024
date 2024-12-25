#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
struct Position {
    int row, col;
};
std::unordered_map<char, Position> numPad = {
        {'7', {0, 0}}, {'8', {0, 1}}, {'9', {0, 2}},
        {'4', {1, 0}}, {'5', {1, 1}}, {'6', {1, 2}},
        {'1', {2, 0}}, {'2', {2, 1}}, {'3', {2, 2}},
                       {'0', {3, 1}}, {'A', {3, 2}} // 'A' is at the bottom-right
    };
std::unordered_map<char, Position> dirPad= {
                 {'^', {0, 1}},{'A', {0, 2}},
   {'<', {1, 0}},{'v', {1, 1}},{'>', {1, 2}},
    };
std::string getNumericActions(std::string code){
   Position current = numPad['A'];
   int totalSteps = 0;
   std::vector<char> path; // To store the movement directions

   for (char digit : code) {
      Position target = numPad[digit];
      while (current.row < target.row) {
         path.push_back('v');
         current.row++;
         totalSteps++;
      }
      while (current.row > target.row) {
         path.push_back('^');
         current.row--;
         totalSteps++;
      }

      while (current.col < target.col) {
         path.push_back('>');
         current.col++;
         totalSteps++;
      }
      while (current.col > target.col) {
         path.push_back('<');
         current.col--;
         totalSteps++;
      }
      path.push_back('A');
   }
   std::string result = "";
   for (char c : path){
      result += c;
   }
   return result;
}
std::string getDirectionActions(std::string directions){
   Position current = dirPad['A'];
   int totalSteps = 0;
   std::vector<char> path; // To store the movement directions

   for (char digit : directions) {
      Position target = dirPad[digit];
      while (current.row < target.row) {
         path.push_back('v');
         current.row++;
         totalSteps++;
      }
      while (current.row > target.row) {
         path.push_back('^');
         current.row--;
         totalSteps++;
      }

      while (current.col < target.col) {
         path.push_back('>');
         current.col++;
         totalSteps++;
      }
      while (current.col > target.col) {
         path.push_back('<');
         current.col--;
         totalSteps++;
      }
      path.push_back('A');
   }
   std::string result = "";
   for (char c : path){
      result += c;
   }
   return result;
}

int part1(std::vector<std::string> codes){
   int result = 0;
   for (std::string c : codes){
      int numPart = std::stoi((c.substr(0, c.length()-1)));
      std::string actions = (getDirectionActions(getDirectionActions(getNumericActions(c))));
      int lenPart = actions.length();
      std::cout << lenPart << '*' << numPart << std::endl;
      result += lenPart*numPart;
   }
   return result;
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

   std::cout << part1(input) << std::endl;
   return 0;
}
