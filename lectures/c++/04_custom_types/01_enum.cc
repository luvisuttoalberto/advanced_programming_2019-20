#include <iostream>

//N.B.: use const expressions instead of #define; in this way you can announce the type of variable. 
//Remember the example of the exercise on the conversion of numbers: no magic numbers!
//Also, they are both "known" at compile time so there is no computational difference

enum color { red, yellow, green };
// enum color{red=0, yellow=1, green=2}; // would have been equivalent

void dwim(const color c) { // just to remember, dwim = do what i mean
  switch (c) {
    case red:
      std::cout << "option 1: red\n";
      break;
    case yellow:
      std::cout << "option 2: yellow\n";
      break;
    case green:
      std::cout << "option 3: green\n";
      break;
    default:
      std::cout << "unknown option\n";  // should I exit the program?
      break;
  }
}

int main() {
  color opt{red};
  // opt = 3; // cannot assign int to enum
  int a{opt};  // but they implicitly converts to integers

  dwim(opt);

  dwim(yellow);

  // dwim(2); // error
  dwim(color(2));  // works but why you may want to write this?
  //watchout: even if the following goes to the default option, doing this is dangerous
  dwim(color(6));  // ???

  return 0;
}
