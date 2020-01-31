#include <cmath>
#include <iostream>

int main() {
  double d = std::sqrt(4);
  std::cout << d << " " << errno << std::endl;

  d = std::sqrt(-4);
  std::cout << d << " " << errno << std::endl;
  //NB: the value of errno is not set to 0 after an error; 
  //for example: if we do again sqrt(4) errno is still 33
  return 0;
}
