#include <iostream>
#include <string>

//You can have many constructors, but only one destructor, which activates when the variable goes out of scope
//IMPORTANT: never mix new and malloc: new calls the constructor, malloc doesn't; same with delete and free()

struct Foo {
  //standard way to give a name to the variables: put the _ in front of the variable name (not mandatory)
  int _i;
  double _d;
  std::string _s;
  //constructor: same name of the class, doesn't have a return (neither a return type obv)
  Foo(const int i, const double d, const std::string& s);  // custom constructor, called with parameters; you can have many of these

  Foo();  // default constructor, can be called without parameters

  ~Foo();  // destructor
};

Foo::Foo(const int i, const double d, const std::string& s)//here we are writing in the "limbo";
//the difference is: in the limbo the variables are not constructed yet; inside the {} (line 29) the variables have already been constructed;
//here you can and should construct the variables; inside you can't, and also you can't use the uniform initializers {}; 
//here you can't use =
    : _i{i},
      _d{d},
      _s{s}
// _i, _d, _s must be initialized in the same order they have been declared in the struct

{

  //inside here you can't do _i{i}; the object has already been constructed! Instead, you can do _i = i;
  //which one is better? The first, it's faster!! I construct the variable with the right value;
  //In the = one you first construct the variable with no value, and then you copy the value inside of the variable; you do 2 operations!!
  std::cout << "custom ctor\n";
  // if you want/need you can use _i, _d, _s and change their value with the usual notation +,-,=,*, or call a function..
  // don't use {} because this notation is reserved for the construction of the variables and at this point they have already been constructed
}

Foo::Foo() {
  std::cout << "default ctor\n";  // what happens to our member variables?
}

Foo::~Foo() {
  std::cout << "dtor\n";
}

//here we are defining the operator << so that we can print all the variables inside of a Foo object separated with " "
//cout is also an object of type ostream, defined inside of the namespace std
//this is an example of an operator overloading
std::ostream& operator<<(std::ostream& os, const Foo& f) {
  os << f._i << " " << f._d << " " << f._s << std::endl;
  return os;
  //I return this so that I can continue; the same is done by the usual std::cout << "f0: "
  //the operator defined here receive in the first case (see after) std::cout << "f0: " and returns the modified output stream 
}

int main() {
  Foo f0;    // call default ctor
  Foo f1{};  // call default ctor
  // Foo f2(); // compiler error, because the compiler thinks that you are defining a function with return type Foo

  Foo f2{8, 2.2, "hello"}; //call custom constructor
  //Foo f2(8, 2.2, "hello");works too but DON'T USE THIS
  std::cout << "f0: " << f0 << "f1: " << f1 << "f2: " << f2 << std::endl;

  //the destructor is called when the variable goes out of scope
  //NEVER INVOKE A DESTRUCTOR BY HAND
  //the destructor is called 3 times, from bottom to top: the first destructed variable is f2, the last is f0
  //this is valid also inside of the Foo object
  return 0;
}
