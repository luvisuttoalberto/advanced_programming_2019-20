#ifndef _CLASS_C_INTERFACE_H_
#define _CLASS_C_INTERFACE_H_

typedef void* Foo_c;
//the following lines are needed because we are going to compile c-main with a c compiler, that doesn't know what extern "C" is!! 
#ifdef __cplusplus //this macro is recognized by the preprocessor; 
//if the preprocessor is c++ he will keep these lines, otherwise it doesn't have this macro defined and it will not keep these lines
extern "C" {
#endif

Foo_c create_foo(int b);
void free_foo(Foo_c);
void print_foo(Foo_c);
void set_a(Foo_c, int v);
int get_a(Foo_c); //note that this can't return a reference; they don't exists in c; If you want to change the value you have to implement another function

#ifdef __cplusplus
}
#endif

#endif /* _CLASS_C_INTERFACE_H_ */
//all this must be compiled with a c++ compiler, because they use c++ features (like constructors)