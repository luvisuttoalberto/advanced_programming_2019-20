#ifndef _FUNC_H_
#define _FUNC_H_

#include <iostream>
//functions are externally linked by default; 
//this is a problem if we only write void dummy(), beause when we link the various libraries we have multiple definition of dummy()
//solutions: use static or inline
//difference: with inline you suggest the compiler not to put a jump to that function, but to copy and paste the content of the function
//use it only with small functions! 
//Note that the compiler can do what he wants: he can decide not to inline inlined functions or to inline not inlined functions;
//in c++ "inline" implies internal linkage
//in c it doesn't, you have to put static
inline void dummy() {
  std::cout << "dummy\n";
}

#endif /* _FUNC_H_ */
