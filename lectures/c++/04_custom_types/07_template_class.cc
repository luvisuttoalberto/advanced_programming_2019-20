#include <iostream>
#include <string>

template <typename num>
class Vector {
  num* elem;
  std::size_t _size;

 public:
  //the constructor puts the address of a new allocated array of size "size" and type "num" inside of elem and the size in _size
  Vector(const std::size_t size) : elem{new num[size]}, _size{size} {}

  // automatically release the acquired memory
  ~Vector() { delete[] elem; }

  // try to remove the const and recompile
  //this const means that the state of my object [what is the object?] will not be changed if i run this function

  std::size_t size() const { return _size; }

  num& operator[](const std::size_t i) { return elem[i]; }

  // try to comment this line and recompile
  const num& operator[](const std::size_t i) const { return elem[i]; }
  //the const written at the beginning of the line means "this return value cannot be changed"
};
//the const written in:
//std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
//allows you to call only functions that have a const before {}; 
//This is because you are using your own custom type
//In this way, you can guarantee the compiler that the variable v won't be changed by the function that you are calling, in this case the operator[]. 
//That's why we put the const before the {} in the operator[] overloading

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
  for (auto i = 0u; i < v.size(); ++i)
    os << "v[" << i << "] = " << v[i] << std::endl;
  return os;
}

int main() {
  Vector<double> v{10};

  for (auto i = 0u; i < v.size(); ++i)
    v[i] = i;

  std::cout << v << std::endl;

  Vector<double>* pv{&v};

  //I first have to dereference the pointer, then I can use the defined operators
  (*pv)[0] = -99.999;

  pv->operator[](1) = 77777.3333;  // or I call the function by name (orribile)

  std::cout << *pv << std::endl;

  Vector<double>& rv{v};

  rv[5] = 555;

  std::cout << v << std::endl;

  return 0;
}
