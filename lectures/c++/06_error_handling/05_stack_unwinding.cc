#include <iostream>
#include <vector>

#include "ap_error.h"

class Foo {
 public:
  Foo() { std::cout << "Foo" << std::endl; }
  ~Foo() { std::cout << "~Foo" << std::endl; }
};

class Bar {
 public:
  Bar() { std::cout << "Bar" << std::endl; }
  ~Bar() { std::cout << "~Bar" << std::endl; }
};

class Vector {
  double* elem;

 public:
  Vector(const unsigned int l) : elem{new double[l]} {
    std::cout << "Vector" << std::endl;
  }
  ~Vector() noexcept {
    delete[] elem;
    std::cout << "~Vector" << std::endl;
  }
};

class ManyResources {
  double* ptr;
  Vector v;

 public:
  ManyResources() : ptr{nullptr}, v{3} {
    std::cout << "Manyresources" << std::endl;
    try {
      ptr = new double[5];  // new(std::nothrow) double[5] could be better
      //the following line is a simulation of something that has gone wrong, just to see how the try/catch and delete of the initializated objects react
      AP_ERROR(false) << "Error in ManyResources ctor." << std::endl;
    } catch (...) {
      delete[] ptr;  // <----
      throw;
    }
  }

  ~ManyResources() noexcept {
    std::cout << "Manyresources" << std::endl;
    delete[] ptr;  // <----
  }
};

int main() {
  Foo f;
  int* raw_ptr = new int[7];
  try {
    // to put this here would be wrong because raw_ptr would not be visible inside the catch-clause:
    // int * raw_ptr=new int[7]; 
    ManyResources mr;
    Bar b;

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;

    delete[] raw_ptr;  // <--- try to comment this and run valgrind or use the
                       // sanitize library
    return 1;

  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n" << std::endl;

    delete[] raw_ptr;  // <---
    return 2;
  }

  delete[] raw_ptr;  // <---
  return 0;
}
