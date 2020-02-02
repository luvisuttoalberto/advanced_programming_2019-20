#include <iostream>

template <typename T>
struct Base {
  void foo() const { std::cout << "base foo" << std::endl; }
};

template <typename T>
struct Derived : public Base<T> {
  void bar() const { this->foo(); } //without this-> the code wouldn't compile; this is because the Base<T> is templated
  //the compiler will apply different rules when we insert this->; 
  //if you have problems accessing things that you know you can access, use it.
  //We don't really know why
};

int main() {
  Derived<int> d;
  d.bar();
}
