#include <iostream>

struct X {
  int a = 5;  // in-class initialization
  double b;
  char c = 'a';
  //in this way we are explicitely generating a default constructor
  //this may be useful when we want also to create a non default constructor, but we also want to have a default constructor
  //otherwise it's not generated
  X() = default;  // in-class initializers are used by the constructors
};

struct Y {
  int a = 77;
  double b;
  char c = 'a';
  Y() : a{5} {}  // what it is written here in the constructor wins the in-class initialization
  //in this way we have a = 5, the rest is not changed
  Y(const Y&) = delete;
};

int main() {
  X x1;    // compiler-generated default ctor
  X x2{};  // compiler-generated default ctor calls {} on uninitialized vars (so only b in this case)
  std::cout << x1.a << "--" << x1.b << "--" << x1.c << "\n";
  std::cout << x2.a << "--" << x2.b << "--" << x2.c << "\n\n";

  Y y1;    // default ctor
  Y y2{};  // default ctor
  std::cout << y1.a << "--" << y1.b << "--" << y1.c << "\n";
  std::cout << y2.a << "--" << y2.b << "--" << y2.c << "\n";

  // Y y3{y2}; // error: call to a deleted function

  return 0;
}
