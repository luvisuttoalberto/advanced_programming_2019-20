#include <algorithm>  // std::copy
#include <iostream>
#include <memory>

template <typename T>
class Vector {
  std::size_t _size;
  std::unique_ptr<T[]> elem;

 public:
  explicit Vector(const std::size_t length) // custom ctor
      : _size{length}, elem{new T[length]{}} {
    std::cout << "custom ctor\n";
  }

  // Vector(const std::initializer_list<T> args)
  //     : _size{args.size()}, elem{new T[_size]} {
  //   std::cout << "list ctor\n";
  //   std::copy(args.begin(), args.end(), begin());
  // }

  // default ctor
  Vector() { std::cout << "default ctor\n"; }  // _size uninitialized
  // Vector() : _size{}, elem{} { std::cout << "default ctor\n"; } // this could
  // be better Vector() = default;

  ~Vector() = default;

  /////////////////////////
  // copy semantics

  // copy ctor -- deep copy
  Vector(const Vector& v);

  // copy assignment -- deep copy
  Vector& operator=(const Vector& v);
  // end of copy semantics
  /////////////////////////

  /////////////////////////
  // move semantics
  //We can't put a const value inside this constructor: we MOVE it! The copied one is left in a vague state: you can call the destructor on it
  //The && here means that it is an r value: can only stay in the right size of an = sign
  //ex: a = 3; 3 can only stay on the right
  //the std::move(v._size) is just a copy //WHY IS THIS A COPY????
  //the std::move(v.elem) is not a copy!! You need to tell that (usually the && guys) are going to die, so assign
  //the NULL pointer to that one or release it, something like that
  //MESSAGE: USE UNIQUE POINTERS: THEY ARE AS FAST AS RAW POINTERS BUT BETTER 
  // move ctor
  Vector(Vector&& v) : _size{std::move(v._size)}, elem{std::move(v.elem)} {
    std::cout << "move ctor\n";
  }

  //SWAP EXERCISE SOLUTION!! use move: in this way you don't have to copy, you just move it!!
  //Of course you'll need a third object anyway

  // Vector(Vector&& v) = default; // ok

  // move assignment
  Vector& operator=(Vector&& v) {
    std::cout << "move assignment\n";
    _size = std::move(v._size);
    elem = std::move(v.elem);
    return *this; //this is a pointer to yourself; in this case to the istantiated object
  }

  // Vector& operator=(Vector&& v) = default; // ok

  // end move semantics
  /////////////////////////

  const T& operator[](const std::size_t& i) const { return elem[i]; }
  T& operator[](const std::size_t& i) { return elem[i]; }

  std::size_t size() const { return _size; }

  // range-for
  const T* begin() const { return &elem[0]; }
  T* begin() { return &elem[0]; }

  const T* end() const { return &elem[_size]; }
  T* end() { return &elem[_size]; }
};

// copy ctor
template <typename T> //note that you can access private member of this object (_size etc.)
Vector<T>::Vector(const Vector& v) : _size{v._size}, elem{new T[_size]} {
  std::cout << "copy ctor\n";
  std::copy(v.begin(), v.end(), begin()); // I could have done a for loop
  //copy from v.begin() to v.end() starting from my begin()
}

// copy assignment
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& v) {
  std::cout << "copy assignment (\n";

  // we could decide that this operation is allowed if and only if
  // _size == v._size
  //
  //reset() is a public function of the unique pointers
  elem.reset();              // first of all clean my memory
  auto tmp = v;              // then use copy ctor
  (*this) = std::move(tmp);  // finally move assignment (of the intermediate object)



  //WHY DON'T WE USE std::copy(v.begin(), v.end(), begin()); LIKE BEFORE??????? Cause otherwise we wouldn't copy also other data (like size in this case)
  


  // or we do everything by hand..
  // and we can do not reset and call new again if the sizes are suitable

  std::cout << ")\n";
  return *this;

  // is this approach consistent with self-assignment vx=vx?
}

template <typename T>
// why we return by value?
Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) {
  const auto size = lhs.size();

  // how should we check that the two vectors have the same size?

  Vector<T> res(size);
  for (std::size_t i = 0; i < size; ++i)
    res[i] = lhs[i] + rhs[i];

  return res;
}//We need to return the result by value in this case!! So we [DON'T???] put it in the heap and we return it

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
  for (const auto& x : v)
    os << x << " ";
  os << std::endl;
  return os;
}

int main() {
  std::cout << "Vector<int> v0; calls\n";
  Vector<int> v0;
  std::cout << v0.size() << "\n";
  std::cout << "Vector<int> v00{}; calls\n";
  Vector<int> v00{};
  std::cout << v00.size() << "\n";

  std::cout << "\nVector<double> v1{5}; calls\n";
  Vector<double> v1{5};

  std::cout << "\nVector<double> v2 = v1; calls\n";
  Vector<double> v2 = v1;
  //this will call the copy constructor, because it is like writing Vector<double> v2{v1};
  
  std::cout << "\nv2 = Vector<double>{7}; calls\n";
  v2 = Vector<double>{7};
  //this will call the move assignment, which will call the custom constructor first to initialize the arg value

  std::cout << "\nVector<double> v3{std::move(v1)}; calls\n";
  Vector<double> v3{std::move(v1)};  // now v1 should not be used
  //this of course will call the move constructor: std::move(v1) is an arg value

  std::cout << "\nv3 = v2; calls\n";
  v3 = v2;
  //this will call a copy assignment, because v2 is not an arg value;
  //the copy assignment will call the copy constructor to initialize the tmp
  //and then will call the move assignment to put the tmp in v3

  std::cout << "\nv2 = " << v2;
  std::cout << "v3 = " << v3;

  std::cout << "\nassign some values to v3\n";
  {
    // auto i = v3.size();
    // while (i--)
    //   v3[i] = i;

    int c = 0;
    for (auto& x : v3)
      x = c++;
  }//[these braces are probably put here just for the scope of c]

  // v3=v3;
  std::cout << "\nv2 = " << v2;
  std::cout << "v3 = " << v3;

  std::cout << "\nVector<double> v4{v3 + v3}; calls\n";
  Vector<double> v4{v3 + v3};
  //this will only call the custom constructor (used to construct the intermidiate vector in the function) because the result of the + is returned by value
  //why doesn't it call the custom constructor for the construction of v4? because we construct it inside, when we construct the res!! This is due to the return by value
  //The point is:
  //the compiler understands that he needs to construct the value directly inside of v4; so the intermediate res vector is not constructed

  std::cout << "v4 = " << v4;

  std::cout << "\nNRVO: Named Return Value Optimization\n";

  std::cout << "\nv4 = v3 + v3 + v2 + v3; calls\n";
  v4 = v3 + v3 + v2 + v3;
  //same reason as before, three objects are constructed (one for every operation; then the move assignment is called because v4 has already been constructed)
  //so this will only print the 3 custom constructors and the move assignment
  
  std::cout << "v4 = " << v4;

  return 0;
}
