#include <iostream>
//this is like namespace std{...}
namespace choose_a_name {

  int variable;
  //this is a nested namespace
  namespace nested {

    void hello1();
    void hello2();
    void hello3();

  }  // namespace nested
}  // namespace choose_a_name

int main() {
  // variable = 42; // error
  choose_a_name::variable = 42; //you can only access the variables of the namespace through the scope resolution operator
  // hello1(); // error
  //It's the same for the functions
  choose_a_name::nested::hello1();
  choose_a_name::nested::hello2();
  choose_a_name::nested::hello3();
  return 0;
}
//you can also define the function outside of the namespace; you only need to use one of the following 3:
void choose_a_name::nested::hello1() {
  std::cout << "hello1 from nested\n"
            << "variable is " << choose_a_name::variable << std::endl;
}

namespace choose_a_name {
  namespace nested {
    void hello2() {
      std::cout << "hello2 from nested\n"
                << "variable is " << variable << std::endl;
    }
  }  // namespace nested
}  // namespace choose_a_name
//the following is valid from now on
using namespace choose_a_name;

void nested::hello3() {
  std::cout << "hello3 from nested\n"
            << "variable is " << variable << std::endl;
}
