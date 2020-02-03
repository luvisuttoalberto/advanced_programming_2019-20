// we do this check to avoid double definition of the same macro (possible if we import in the same file different libraries that import this library)
#ifndef __find_if_hardcoded
#define __find_if_hardcoded

template <typename I, typename T>
// requires I is Iterator
// *I is of type T
//In the following function I return and iterator (kind of a pointer)
//it makes sense to return a pointer when you search for something; do it!
I find_if_hardcoded(I first, const I last, const T& value){
  // precondition [first, last)
  //NB: we can't verify this precondition!
  //For example: in the case in which the iterators are two pointers from a linked list
  //We leave this to the user
  while( first != last && *first != value){
    ++first;
  }
  return first;
}

//Is this a generalization of the function find_if_virtual??
//Now we want to generalize the algorithm
//A predicate is a function that returns a boolean
//P, the predicate, can be a function or even a class (our case) that has an operator(T) that returns a bool
template <typename I, typename P>
// requires I is Iterator
// *I is of type T
//if we wanted to avoid the second template, we should have written:
//I find_if_template(I first, const I last, bool (*func)(const T&) )
I find_if_template(I first, const I last, P predicate){
  // precondition [first, last) //as before, can't be verified
  while( first != last && !predicate(*first) ){
    ++first;
  }
  return first;
}

template <typename T>
struct predicate_base{
  //operator() overloading
  virtual bool operator()(const T&) const = 0;
  //note that this is a pure abstract function!
  //At the moment, you can't predict what it will be
};

template <typename I,typename T>
// requires I is Iterator
// *I is compatible with predicate
//writing the function in the followin way I can accept predicate_base or one of his children (polymorphism)
I find_if_virtual(I first, const I last, const predicate_base<T>& predicate){
  // precondition [first, last) // as before
  while( first != last && !predicate(*first) ){
    ++first;
  }
  return first;
}

#endif
