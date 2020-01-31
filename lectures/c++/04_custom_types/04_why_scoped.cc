#include <iostream>

enum month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

using namespace std;

//instead, if we use:
//using std::cout;
//using std::endl;
//there is no problem for the compiler to understand what we are refering to

int main() {
  cout << nov << endl;

  // if I uncomment the following, it gives an error because there is an ambiguous name: dec is also an std function. Pay attention!
  // cout << dec << endl;
  return 0;
}
