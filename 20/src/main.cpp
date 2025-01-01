#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


int part1(std::vector<std::string> inp){
   int rows = inp.size();
   int cols = inp[0].size();
   bool run = true;
   int r, c;
   for (int rs = 0; rs < rows && run; ++rs){
      for (int cs = 0; cs < cols; ++cs){
         if (inp[rs][cs] == 'S'){
            r = rs;
            c = cs;
            run = false;
            break;
         }
      }
   }
   std::vector<std::vector<int>> dists(rows, std::vector<int>(cols, -1));
   dists[r][c] = 0;
   while (inp[r][c] != 'E'){
      for (auto [nr, nc] : std::vector<std::pair<int, int>>{{r+1,c},{r-1,c},{r,c+1},{r,c-1}}){
         if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) continue;
         if (inp[nr][nc] == '#') continue;
         if (dists[nr][nc] != -1) continue;
         dists[nr][nc] = dists[r][c]+1;
         r = nr;
         c = nc;
      }
   }
   int count = 0;
   for (int i = 0; i < rows; ++i){
      for (int j = 0; j < cols; ++j){
         if (inp[i][j] == '#') continue;
         for (auto [nr, nc] : std::vector<std::pair<int, int>>{{i+2, j},{i+1, j+1},{i, j+2},{i-1, j+1}}){
            if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) continue;
            if (inp[nr][nc] == '#') continue;
            if (std::abs(dists[i][j]-dists[nr][nc]) >= 102) count++;
         }
      }
   }
   return count;
}
int part2(std::vector<std::string> inp){
   int rows = inp.size();
   int cols = inp[0].size();
   bool run = true;
   int r, c;
   for (int rs = 0; rs < rows && run; ++rs){
      for (int cs = 0; cs < cols; ++cs){
         if (inp[rs][cs] == 'S'){
            r = rs;
            c = cs;
            run = false;
            break;
         }
      }
   }
   std::vector<std::vector<int>> dists(rows, std::vector<int>(cols, -1));
   dists[r][c] = 0;
   while (inp[r][c] != 'E'){
      for (auto [nr, nc] : std::vector<std::pair<int, int>>{{r+1,c},{r-1,c},{r,c+1},{r,c-1}}){
         if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) continue;
         if (inp[nr][nc] == '#') continue;
         if (dists[nr][nc] != -1) continue;
         dists[nr][nc] = dists[r][c]+1;
         r = nr;
         c = nc;
      }
   }
   int count = 0;
   for (int i = 0; i < rows; ++i){
      for (int j = 0; j < cols; ++j){
         if (inp[i][j] == '#') continue;
         for (int radius = 2; radius <= 20; ++radius){
            for (int dr = 0; dr <= radius; ++dr){
               int dc = radius - dr;
               for (auto [nr, nc] : std::vector<std::pair<int, int>>{{i+dr, j+dc},{i+dr, j-dc},{i-dr, j+dc},{i-dr, j-dc}}){
                  if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) continue;
                  if (inp[nr][nc] == '#') continue;
                  if ((dists[i][j]-dists[nr][nc]) >= 100+radius) count++;
               }
            }
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
