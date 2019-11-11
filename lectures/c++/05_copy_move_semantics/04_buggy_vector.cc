#include <iostream>

//we have a problem with the pointers here! 
//When we initialize two Vector objects, we have two different pointers, pointing to the same memory address
//what the compiler generates is a cheap copy: he copy by value, so the pointer of v2 has the same value 
//of the pointer of v1; in this way when we change v1 we also change v2 and viceversa
//This is also the reason why, when we free the memory, the compiler comes up with an error;
//we are freeing the same memory twice!! 

template <typename T>
class Vector {
  T* elem;
  std::size_t _size;

 public:
  //explicit is needed so that the compiler doesn't call implicitely the constructor of Vector when we call print
  explicit Vector(const std::size_t length) // custom constructor
  //new T[length]{} is like using calloc
      : elem{new T[length]{}}, _size{length} {}

  ~Vector() { delete[] elem; } // custom deconstructor
  //overloading of [] operator, with const and without const
  const T& operator[](const std::size_t& i) const { return elem[i]; }
  T& operator[](const std::size_t& i) { return elem[i]; }

  std::size_t size() const { return _size; }

  // range-for
  const T* begin() const { return elem; }
  T* begin() { return elem; }

  const T* end() const { return elem + size(); }
  T* end() { return elem + size(); }

};

/*void print(const Vector<int>& v){
  for(auto x : v){
    std::cout << x << std::endl;
  }
}*/

/*{
  auto it = v1.begin();
  auto stop = v1.end();
  for(; it!=stop; ++it){
    const auto x = *it
  }
}*/





int main() {
  Vector<int> v1{3};
  v1[0] = 1;
  v1[1] = 2;
  v1[2] = 3;

  std::cout << "v1: ";
  for (const auto x : v1) // to allow this I have to create the functions begin() and end() inside the class (with and without const)
    std::cout << x << " ";
  std::cout << std::endl;

  Vector<int> v2{v1};  // default copy constructor

  std::cout << "v2 after default copy ctor: ";
  for (const auto x : v2)
    std::cout << x << " ";
  std::cout << std::endl;

  v1[0] = 99;

  std::cout << "v2 after v1 has been changed: ";
  for (const auto x : v2)
    std::cout << x << " ";
  std::cout << std::endl;

  v2[1] = -999;

  std::cout << "v1 after v2 has been changed: ";
  for (const auto x : v1)
    std::cout << x << " ";
  std::cout << std::endl;

  return 0;
}
