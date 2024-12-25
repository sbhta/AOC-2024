#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

unsigned long long part1(std::string inp){
   std::vector<long long> diskmap;
   long long Id = 0;
   for (int i = 0; i < inp.length(); ++i){
      if (i%2 == 0) {
         for (int j = 0; j < inp[i]-'0'; ++j) {diskmap.push_back(Id);}
         ++Id;
      }
      else {
         for (int j = 0; j < inp[i]-'0'; ++j) {diskmap.push_back(-1);}
      }
   }
   for (int i = diskmap.size()-1; i > 0; --i){
      if (diskmap[i] != -1) {
         for (int j = 0; j < i; ++j){
            if (diskmap[j] == -1){
               diskmap[j] = diskmap[i];
               diskmap[i] = -1;
            }
         }
      }
   }
   unsigned long long sum = 0;
   for (int i = 0; i < diskmap.size(); ++i){
      if (diskmap[i] != -1){sum += i*diskmap[i];}
      else break;
   }
   return sum;
}

unsigned long long part2(std::string inp){
   std::vector<std::pair<unsigned long long, unsigned long long>> diskmap;
   unsigned long long id = 0;
   for (unsigned long long i = 0; i < inp.length(); ++i){
      if (i%2 == 0) {diskmap.push_back({id, inp[i]-'0'}); id++;}
      else diskmap.push_back({-1, inp[i]-'0'});
   }
   for (unsigned long long last = diskmap.size()-1; last > 0; --last){
      if (diskmap[last].first != -1){
         for (unsigned long long i = 0; i < last; ++i){
            if (diskmap[i].first == -1){
               if (diskmap[i].second == diskmap[last].second){
                  diskmap[i].first = diskmap[last].first;
                  diskmap[last].first = -1;
               }
               else if (diskmap[i].second > diskmap[last].second){
                  diskmap[i].first = diskmap[last].first;
                  unsigned long long diff = diskmap[i].second - diskmap[last].second;
                  diskmap[i].second = diskmap[last].second;
                  diskmap[last].first = -1;
                  diskmap.insert(diskmap.begin()+i+1, {-1, diff});
               }
            }
         }
      }
   }
   unsigned long long sum = 0;
   unsigned long long j = 0;
   for (auto x : diskmap){
      for (unsigned long long i = 0; i < x.second; ++i){
         if (x.first == -1) ;
         else sum += j*x.first;
         ++j;
      }
   }
   return sum;
}

int main (int argc, char *argv[]) {
   std::string sample;
   std::string input;
   std::ifstream fileSample(argv[1]);
   std::ifstream fileInput(argv[2]);
   std::getline(fileSample, sample);
   std::getline(fileInput, input);
   fileSample.close();
   fileInput.close();

   std::cout << part2(sample) << std::endl;
   std::cout << part2(input) << std::endl;
   return 0;
}
