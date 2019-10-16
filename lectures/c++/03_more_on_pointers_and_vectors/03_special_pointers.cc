#include <cstring>  // strcmp
#include <iostream>

int func1(const char* a);
int func2(const char* a);
void func3(const char* a);

int main() {
  int a{8};
  int* pi{&a};

  char** ppc;

  int* ap[7];// is an array of 7 pointers to integers

  void* pv{pi}; // you can cast int* to void *, not the way around, unless you use static_cast (see after)
  // *pv; // we cannot dereference void*
  // ++pv; // we cannot increment. Why? Because we don't know the size of every element!
  int* pi2{static_cast<int*>(pv)};

  pv = ppc;
  pv = ap;
  pv = pi;

  pi = nullptr;
  ppc = nullptr;
  // ap = nullptr;  // error, why?
  ap[0] = nullptr;
  int** bbb;
  bbb = ap;
  pv = nullptr;
  pi2 = 0;  // older codes. gets the nullptr (don't do this)

  // pi = NULL; // please don't do this

  double* da{new double[5]{}};
  delete[] da;  // dangling pointer
  da = nullptr; // do this do you can't print something in an address which is no more active
  //the sequent two are equal
  if (pi != nullptr)
    std::cout << "pi is not nullptr and I can dereference it " << *pi
              << std::endl;

  if (pi)
    std::cout << "pi is not nullptr and I can dereference it " << *pi
              << std::endl;

  if (pi == nullptr)
    std::cout << "pi is nullptr and I CANNOT dereference it \n";

  if (!pi)
    std::cout << "pi is nullptr and I CANNOT dereference it \n";

  // strings are special type of char[]
  char word[]{"Hello"};
  char word2[]{'H', 'e', 'l', 'l', 'o', 0};
  if (strcmp(word, word2) == 0)  // word == word2 is
                                 // implementation-dependent (it might
                                 // compare the two pointers, i.e. the
                                 // two addresses of word and word2)
    std::cout << "same\n";
  else
    std::cout << "different\n";

  int (*fp)(const char*); // here i am defining a pointer to function that takes pointers to char and returns integers
  fp = func1;

  fp("hello");
  //the sequent syntax is equal but preferred, more clear

  fp = &func2;
  fp("world");

  // fp = func3; // error: wrong signature (returns void)
  auto xx = func3;

  xx("auto");

  decltype(&func3) x = func3;
  //similar to auto, you initialize a variable of the type of func3
  //we could also have written: void (*x)(const char*) = func3
  x("decltype");

  return 0;
}

int func1(const char* a) {
  std::cout << "1111: " << a << std::endl;
  return 1;
}

int func2(const char* a) {
  std::cout << "2222: " << a << std::endl;
  return 2;
}

void func3(const char* a) {
  std::cout << "3333: " << a << std::endl;
}
