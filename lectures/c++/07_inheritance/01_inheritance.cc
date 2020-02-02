#include "ap_error.h"
#include <iostream>

struct Animal {
  unsigned int age;
  double weight;

  Animal(const unsigned int a, const double w) : age{a}, weight{w} {
    AP_ERROR(weight >= 0) << "invalid weight: " << weight << std::endl;
  }

  Animal() noexcept : Animal{0, 0} {}  // delegating constructor

  void speak() const noexcept { std::cout << "Unknown\n"; }
  void info() const noexcept {
    std::cout << "age:\t" << age << '\n' << "weight:\t" << weight << '\n';
  }
};

struct Dog : public Animal { 
  //difference: in this way we say that a Dog IS an animal; before we said that a Dog HAS an animal
  //We are saying that the children [derived] struct can access all the public members of the parent [super/base] struct (Animal in this case)
  //Note that in the struct, public is the default
  //in a struct we can also define data as protected:
  //these objects of the struct are private, but can be accessed by the children
  void speak() const noexcept { std::cout << "Bau\n"; }
  Dog() noexcept = default;
  Dog(const unsigned int a, const double d) : Animal{a, d} {} //here I'm calling the parent constructor (of Animal)
  //NB: I'm not implementing the function info() because the info() of Animal is enough, we don't have other object (infos)
};

struct Snake : public Animal {
  bool dangerous;
  Snake(const unsigned int a, const double w, const bool b)
      : Animal{a, w}, dangerous{b} {} //note that we should construct the father first
  explicit Snake(const bool b) noexcept : Animal{}, dangerous{b} {}
  void info() const noexcept {//instead, here we need to implement the function info. NB: THIS IS WRONG
    Animal::info();
    std::cout << "dangerous:\t" << (dangerous ? "true" : "false") << std::endl;
  }
  void speak() const noexcept { std::cout << "ssss\n"; }
};

// run-time (dynamic) polymorphism
void print_animal(const Animal& a) noexcept { //you can pass a children to a function that expects a parent
  std::cout << "through ref\n";
  a.info();
  a.speak();
}

// compile-time (static) polymorphism
template <class T> //NOTE THAT THIS IMPLIES THAT ALL THE types must be known at compile time
void print_animal_template(const T& a) noexcept {
  std::cout << "through template\n";
  a.info();
  a.speak();
}

int main() {
  try {
    Dog d;
    d.info();
    d.speak();

    std::cout << std::endl;

    Dog d1{0, 0.6};
    d1.info();
    d1.speak();

    std::cout << std::endl;

    Snake s{true};
    s.info();
    s.speak();

    std::cout << std::endl;

    Animal* p = new Snake{1, 2.3, false};// a pointer to the base class can point to all of his children (and the children of the children)
    std::cout << "through pointer\n";
    p->info(); // Animal doesn't know that Snake has a dangerous variable!! It will print Unknown (the output of the parent function speak())
    p->speak();

    delete p;

    std::cout << std::endl;

    print_animal(s);

    std::cout << std::endl;

    print_animal_template(s);

    return 0;
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
