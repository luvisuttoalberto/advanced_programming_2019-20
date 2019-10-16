#include <cmath>
#include <iostream>
//here we verify that we have a sequent version of c++ 11, in which have been introduced the auto instead of template
#if __cplusplus > 201103L

template <class T>
auto init(const std::size_t l) {
  return new T[l]{};
}

#else

template <class T>
T* init(const std::size_t l) {
  return new T[l]{};
}

#endif

//we now introduce a compile error so that we can, through the compiler, know the type of pb or ps
/*template <typename T>
void debug(T);*/



int main() {
	//nb: with auto you can't do auto i{0}, you have to use =
  auto b = true;          // a bool
  auto ch = 'x';          // a char
  auto i = 123;           // an int
  auto d = 1.2;           // a double
  auto z = std::sqrt(d);  // z has the type of whatever sqrt(d) returns
  auto ui = 0u;           // unsigned int
  auto llui = 0llu;       // long long unsigned int

  for (auto i = 0; i < 7; ++i)
    std::cout << i << std::endl;
//it is a pointer to a boolean (because b is a boolean)
  auto pb = &b;  // guess what.. How can I know?

  //debug(pb); //here I'm calling a function that is not defined
  auto ps = init<double>(11);
  delete[] ps;
  return 0;
}
