extern "C" {
#include "hello.h"
}

int main() { //ALWAYS USE THE LINKER IN WHICH THE MAIN IS WRITTEN, in this case a c++ linker
  hello_from_c();
  return 0;
}
