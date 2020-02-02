#include <iostream>

struct Base {
  Base() { std::cout << "Base\n"; }
  //~Base() { std::cout << "~Base\n"; } //NB: THIS IS WRONG!! Memory leak
  virtual ~Base() { std::cout << "~Base\n"; } //In this way we can call the destructor of the children destructor
};

struct Derived : public Base {
  Derived() { std::cout << "Derived\n"; }
  ~Derived() { std::cout << "~Derived\n"; }
};

int main() {
  { Derived d; } //here i construct and destroy d

  std::cout << "\n\npointers\n";
  Base* p = new Derived;
  delete p; //if we didn't put virtual, with this I'm only calling the destructor of Base!!!

  return 0;
}
