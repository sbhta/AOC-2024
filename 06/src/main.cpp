#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

int part1(std::string fileName){
   std::vector<std::string> board;
   std::ifstream file(fileName);
   std::string temp;
   while (std::getline(file, temp)) {board.push_back(temp);}
   file.close();

   int xG, yG;
   char currentDir = 'u';
   std::map<char, std::pair<int, int>> dir = {
      {'r', {1, 0}},
      {'l', {-1, 0}},
      {'u', {0, -1}},
      {'d', {0, 1}},
   }; 
   int dxG = dir[currentDir].first, dyG = dir[currentDir].second;
   for (int i = 0; i < board.size(); ++i){ for (int j = 0; j < board[0].length(); ++j){ if (board[i][j] == '^') {xG = j; yG = i;break;} } }
   
   int visited = 1;
   while (xG+dxG < board[0].length() && xG+dxG > -1 &&
          yG+dyG < board.size() && yG+dyG > -1){
      int fyG = yG+dyG, fxG = xG+dxG;
      if (board[fyG][fxG] == '#'){
         if (currentDir == 'u') currentDir = 'r';
         else if (currentDir == 'r') currentDir = 'd';
         else if (currentDir == 'd') currentDir = 'l';
         else if (currentDir == 'l') currentDir = 'u';
         dxG = dir[currentDir].first;
         dyG = dir[currentDir].second;
         continue;
      }
      else {
         xG = fxG;
         yG = fyG;
         if (board[yG][xG] != 'X'){
            visited++;
            board[yG][xG] = 'X';
         }
      }
   }

   for (int i = 0; i < board.size(); ++i){
      std::cout << board[i] << std::endl;
   }

   return visited;
}
bool simulate_with_obstruction(std::vector<std::string> board, int obsX, int obsY) {
    int xG, yG;
    char currentDir = 'u';
    std::map<char, std::pair<int, int>> dir = {
        {'r', {1, 0}},
        {'l', {-1, 0}},
        {'u', {0, -1}},
        {'d', {0, 1}},
    };

    // Find starting position
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[0].length(); ++j) {
            if (board[i][j] == '^') {
                xG = j;
                yG = i;
                break;
            }
        }
    }

    // Place the obstruction
    board[obsY][obsX] = '#';

    std::set<std::tuple<int, int, char>> seenStates;
    seenStates.insert({xG, yG, currentDir});

    while (true) {
        int dxG = dir[currentDir].first;
        int dyG = dir[currentDir].second;
        int nextX = xG + dxG;
        int nextY = yG + dyG;

        if (nextX < 0 || nextX >= board[0].length() || nextY < 0 || nextY >= board.size()) {
            return false; // Guard exits the board
        }

        if (board[nextY][nextX] == '#') {
            // Turn right
            if (currentDir == 'u') currentDir = 'r';
            else if (currentDir == 'r') currentDir = 'd';
            else if (currentDir == 'd') currentDir = 'l';
            else if (currentDir == 'l') currentDir = 'u';
        } else {
            // Move forward
            xG = nextX;
            yG = nextY;
        }

        if (seenStates.count({xG, yG, currentDir})) {
            return true; // Loop detected
        }
        seenStates.insert({xG, yG, currentDir});
    }
}

int part2(std::string fileName) {
    std::vector<std::string> board;
    std::ifstream file(fileName);
    std::string temp;
    while (std::getline(file, temp)) {
        board.push_back(temp);
    }
    file.close();

    int loopCount = 0;

    // Test each position
    for (int y = 0; y < board.size(); ++y) {
        for (int x = 0; x < board[0].length(); ++x) {
            if (board[y][x] == '.' && !(y == 6 && x == 2)) { // Avoid guard's starting position
                if (simulate_with_obstruction(board, x, y)) {
                    ++loopCount;
                }
            }
        }
    }

    return loopCount;
}
int main (int argc, char *argv[]) {
   std::cout << part2(argv[1]) << std::endl;
   return 0;
}
