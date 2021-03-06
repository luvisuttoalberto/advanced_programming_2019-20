#include <iostream>

struct foo {
  void f(int x) { std::cout << "int " << x << std::endl; }
};

struct bar : public foo {
  using foo::f;  // brings all foo::f to this scope
  void f(char x) { std::cout << "char " << x << std::endl; } //without "using" this would be overloading
  //Non è proprio proprio così, sistema un po' sta cosa
  //overloading is not done with inheritance; without using, the object "33" inserted in the main would be seen as a char, even if it is an int
};

int main() {
  bar b;
  b.f(33);
}
