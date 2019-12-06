#include <fstream>
#include <iostream>
int main() {
  int a = 7;
  double d = 9.9;
  {
    std::ofstream f{"a_file.txt"}; //don't need to put open and close when you construct it using a string

    f << "Hello World!\n"
      << "a = " << a << "\n"
      << "d = " << d << std::endl;

    f << "Another line!\n";
  }
  return 0;
}
