#include <ap_error.h>
#include <iostream>

struct Animal {
  unsigned int age;
  double weight;

  Animal(const unsigned int a, const double w) : age{a}, weight{w} {
    AP_ERROR(!(weight < 0)) << "invalid weight!\n";
  }
  //NB: with template it worked also before; 
  //in fact, with templates the type is known at compile time, so the compiler can call the right function (in that case the function of the child)
  Animal() : Animal{0, 0} {}  // delegating constructor
  // we need "virtual" to have the possibility to overwrite the function in the children class and call them through the reference to a parent class object
  //in this way we can avoid using templates; which requires all the possible types known at compile time.
  virtual void speak() const = 0;  // pure virtual function ==> abstract class
  //=0 means that this function is PURE virtual: in this way the struct animal is an abstract class: you will not be able to istantiate an object of this class
  virtual void info() const noexcept {
    std::cout << "age:\t" << age << '\n' << "weight:\t" << weight << '\n';
  }
  //NB: Virtual is really bad for HPC: it makes you do a lot of jumps over memory (very bad) 
  //also, the compiler can't inline virtual functions: he can't know which one is the one to inline!! 
  //the parent one or one of the children one????? we don't know it at compile time!!
  virtual ~Animal() {}  // why? see file 03_virtual_destructor.cc
};

struct Dog : public Animal {
  void speak() const noexcept override { std::cout << "Bau\n"; }
  Dog() = default;
  Dog(const unsigned int a, const double d) : Animal{a, d} {}
};

struct Snake : public Animal {
  bool dangerous;
  Snake(const unsigned int a, const double w, const bool b)
      : Animal{a, w}, dangerous{b} {}
  explicit Snake(const bool b) : Animal{}, dangerous{b} {}
  //from c++11 it is necessary to use override in order to modify a virtual function.
  //before we had to use virtual, with the possibility of mistakenly create a different function.
  void info() const noexcept override {
    Animal::info();
    std::cout << "dangerous:\t" << (dangerous ? "true" : "false") << std::endl;
  }
  void speak() const noexcept override { std::cout << "ssss\n"; } 
};

void print_animal(const Animal& a) noexcept {
  std::cout << "throught ref\n";
  a.info();
  a.speak();
}

int main() {
  try {
    Snake s{true};
    s.info();
    s.speak();

    std::cout << std::endl;

    Animal* p = new Snake{1, 2.3, false};

    std::cout << "through pointer\n";
    p->info();
    p->speak();

    delete p;

    std::cout << std::endl;

    print_animal(s);

    return 0;
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
