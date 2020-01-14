#include <iostream>
extern "C"{ //this will have an object written as in c, so hello, not _Z837hellov
  void hello(){
    std::cout << "Hello, World" << std::endl;
  }
}

int main(){
  hello();
}
