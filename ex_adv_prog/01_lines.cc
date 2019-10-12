#include <iostream>
#include <string>

int main(){
  
  std::string line, print;
  unsigned int max{10}, end;
  
  while(std::getline(std::cin, line)){

    // break lines longer than a given number of characters
    while(line.length() > max){

      unsigned int i{0};
      while(line[max - i] != ' '){
        i++;
      }
      end = max - i + 1;

      // don't break words
      print = line.substr(0, end);
      std::cout << print << "\n";
      
      line = line.substr(end);
    }
    
    std::cout << line << "\n";

  }
  
  return 0;
}