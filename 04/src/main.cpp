#include <fstream>
#include <iostream>
#include <string>
#include <vector>


int getVertical(const std::vector<std::string>& board, int i, int j) {
    const std::string target = "XMAS";
    int count = 0;
    int rows = board.size();

    // Check downward
    if (i + 3 < rows) {
        bool match = true;
        for (int k = 0; k < 4; ++k) {
            if (board[i + k][j] != target[k]) {
                match = false;
                break;
            }
        }
        if (match) ++count;
    }

    // Check upward
    if (i - 3 >= 0) {
        bool match = true;
        for (int k = 0; k < 4; ++k) {
            if (board[i - k][j] != target[k]) {
                match = false;
                break;
            }
        }
        if (match) ++count;
    }

    return count;
}

int getHorizontal(const std::vector<std::string>& board, int i, int j) {
    const std::string target = "XMAS";
    int count = 0;
    int cols = board[0].size();

    // Check right
    if (j + 3 < cols) {
        bool match = true;
        for (int k = 0; k < 4; ++k) {
            if (board[i][j + k] != target[k]) {
                match = false;
                break;
            }
        }
        if (match) ++count;
    }

    // Check left
    if (j - 3 >= 0) {
        bool match = true;
        for (int k = 0; k < 4; ++k) {
            if (board[i][j - k] != target[k]) {
                match = false;
                break;
            }
        }
        if (match) ++count;
    }

    return count;
}

int getDiagonal(const std::vector<std::string>& board, int i, int j) {
    const std::string target = "XMAS";
    int count = 0;
    int rows = board.size();
    int cols = board[0].size();

    // Check downward-right
    if (i + 3 < rows && j + 3 < cols) {
        bool match = true;
        for (int k = 0; k < 4; ++k) {
            if (board[i + k][j + k] != target[k]) {
                match = false;
                break;
            }
        }
        if (match) ++count;
    }

    // Check upward-left
    if (i - 3 >= 0 && j - 3 >= 0) {
        bool match = true;
        for (int k = 0; k < 4; ++k) {
            if (board[i - k][j - k] != target[k]) {
                match = false;
                break;
            }
        }
        if (match) ++count;
    }

    // Check downward-left
    if (i + 3 < rows && j - 3 >= 0) {
        bool match = true;
        for (int k = 0; k < 4; ++k) {
            if (board[i + k][j - k] != target[k]) {
                match = false;
                break;
            }
        }
        if (match) ++count;
    }

    // Check upward-right
    if (i - 3 >= 0 && j + 3 < cols) {
        bool match = true;
        for (int k = 0; k < 4; ++k) {
            if (board[i - k][j + k] != target[k]) {
                match = false;
                break;
            }
        }
        if (match) ++count;
    }

    return count;
}

int part1(std::vector<std::string> inp){
   std::vector<std::string> board;
   for (std::string s : inp){ board.push_back(s); }
   int count = 0;
   // checks all horizontals for xmas
   for (int i = 0; i < board.size(); ++i) {
      for (int j = 0; j < board[i].size(); ++j) {
         if (board[i][j] == 'X') {
            // Check all directions from this starting point
            count += getVertical(board, i, j);
            count += getHorizontal(board, i, j);
            count += getDiagonal(board, i, j);
         }
      }
   }
   return count;
}
int countXMAS(const std::vector<std::string>& board, int i, int j) {
   const std::string mas = "MAS";
   int count = 0;
   int rows = board.size();
   int cols = board[0].size();
   if (i == 0 || i == rows-1) return 0;
   if (j == 0 || j == cols-1) return 0;

   if (board[i-1][j-1] == 'M' && board[i+1][j+1] == 'S'){
      if (board[i+1][j-1] == 'M' && board[i-1][j+1] == 'S') count++;
      if (board[i+1][j-1] == 'S' && board[i-1][j+1] == 'M') count++;
   }
   if (board[i-1][j-1] == 'S' && board[i+1][j+1] == 'M'){
      if (board[i+1][j-1] == 'M' && board[i-1][j+1] == 'S') count++;
      if (board[i+1][j-1] == 'S' && board[i-1][j+1] == 'M') count++;
   }


   return count;
}
int part2(std::vector<std::string> inp){
   std::vector<std::string> board;
   for (std::string s : inp){ board.push_back(s); }
   
   int count = 0;
   for (int i = 0; i < board.size(); ++i) {
      for (int j = 0; j < board[i].size(); ++j) {
         if (board[i][j] == 'A') {
            count += countXMAS(board, i, j);
         }
      }
   }
   return count;
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
