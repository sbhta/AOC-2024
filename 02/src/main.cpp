#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// check if a level is safe
bool isReportSafe(std::vector<int> report){
   // check if ascending or decending
   bool ascending = report[0]-report[1] < 0;
   for (int i = 0; i < report.size()-1; ++i){
      if (report[i] - report[i+1] == 0) {return false;}
      if (ascending && report[i] - report[i+1] > 0){return false;}
      if (!ascending && report[i] - report[i+1] < 0){return false;}
      if (std::abs(report[i]-report[i+1]) > 3) {return false;}
   }
   return true;
}
int part1(std::vector<std::string> inp){
   // compile the input into reports
   std::vector<std::vector<int>> reports;
   for (std::string s : inp){
      std::string nS = "";
      std::vector<int> rp;
      for (char ch : s){
         if (ch == ' '){ rp.push_back(std::stoi(nS)); nS = ""; }
         else nS += ch; 
      }
      rp.push_back(std::stoi(nS));
      reports.push_back(rp);
   }
   int count = 0;
   for (std::vector<int> repo : reports){
      if (isReportSafe(repo)) count++;
   }
   return count;
}
int part2(std::vector<std::string> inp){
   // compile the input into reports
   std::vector<std::vector<int>> reports;
   for (std::string s : inp){
      std::string nS = "";
      std::vector<int> rp;
      for (char ch : s){
         if (ch == ' '){ rp.push_back(std::stoi(nS)); nS = ""; }
         else nS += ch; 
      }
      rp.push_back(std::stoi(nS));
      reports.push_back(rp);
   }
   int count = 0;
   for (std::vector<int> repo : reports){
      if (isReportSafe(repo)) count++;
      else {
         for (int i = 0; i < repo.size(); ++i){
            std::vector<int> cRepo = repo;
            cRepo.erase(cRepo.begin()+i);
            if (isReportSafe(cRepo)) {count++; break;}
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
