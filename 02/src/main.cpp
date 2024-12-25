#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int part1(std::vector<std::string> inp){
   int count = 0;
   
   std::vector<std::vector<int>> reports;

   for (std::string s : inp){
      std::string nS = "";
      std::vector<int> rp;
      for (char ch : s){
         if (ch == ' '){
            rp.push_back(std::stoi(nS));
            nS = "";
         }
         else {
            nS += ch;
         }
      }
      rp.push_back(std::stoi(nS));
      reports.push_back(rp);
   }
   for (std::vector<int> repo : reports){
      // check if ascending or decending
      bool ascending = repo[0]-repo[1] < 0;
      bool safe = true;
      if (repo[0] - repo[1] == 0) continue;
      for (int i = 0; i < repo.size()-1; ++i){
         if (repo[i] - repo[i+1] == 0) {safe = false;break;}
         if (ascending && repo[i] - repo[i+1] > 0){safe = false; break;}
         if (!ascending && repo[i] - repo[i+1] < 0){safe = false; break;}
         if (std::abs(repo[i]-repo[i+1]) > 3) {safe = false; break;}
      }
      if (safe) count++;
   }
   return count;
}

// a function that gives all of the reports possible when removing one of the levels
std::vector<std::vector<int>> removeOneLevel(std::vector<int> repo){
   std::vector<std::vector<int>> perms;
   std::vector<int> tempRepo;
   for (int skip = 0; skip < repo.size(); ++skip){
      for (int i = 0; i < repo.size(); ++i){
         if (skip != i)tempRepo.push_back(repo[i]);
      }
      perms.push_back(tempRepo);
      tempRepo.clear();
   }

   return perms;
}

int part2(std::vector<std::string> inp){
   int count = 0;
   
   std::vector<std::vector<int>> reports;

   for (std::string s : inp){
      std::string nS = "";
      std::vector<int> rp;
      for (char ch : s){
         if (ch == ' '){
            rp.push_back(std::stoi(nS));
            nS = "";
         }
         else {
            nS += ch;
         }
      }
      rp.push_back(std::stoi(nS));
      reports.push_back(rp);
   }
   for (std::vector<int> repo : reports){
      // check if ascending or decending
      bool ascending = repo[0]-repo[1] < 0;
      bool safe = true;
      if (repo[0] - repo[1] == 0) continue;
      for (int i = 0; i < repo.size()-1; ++i){
         if (repo[i] - repo[i+1] == 0) {safe = false;break;}
         if (ascending && repo[i] - repo[i+1] > 0){safe = false; break;}
         if (!ascending && repo[i] - repo[i+1] < 0){safe = false; break;}
         if (std::abs(repo[i]-repo[i+1]) > 3) {safe = false; break;}
      }

      if (safe) count++;
      else {
         std::vector<std::vector<int>> perms = removeOneLevel(repo);
         for (std::vector<int> rp : perms){
            bool ascending2 = rp[0]-rp[1] < 0;
            bool safe2 = true;
            if (rp[0] - rp[1] == 0) continue;
            for (int i = 0; i < rp.size()-1; ++i){
               if (rp[i] - rp[i+1] == 0) {safe2 = false;break;}
               if (ascending2 && rp[i] - rp[i+1] > 0){safe2 = false; break;}
               if (!ascending2 && rp[i] - rp[i+1] < 0){safe2 = false; break;}
               if (std::abs(rp[i]-rp[i+1]) > 3) {safe2 = false; break;}
            }
            if (safe2) {
               count++;
               break;
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
   std::cout << "NOT CORRECT YET Part 2: " << part2(input) << std::endl;
   return 0;
}
