#include "instrumented.hpp"
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

template <typename I>
void set_instrumented(const std::size_t n, I first, I last) {
  using value_type = typename std::iterator_traits<I>::value_type;
  value_type::initialize(n);
  std::set<value_type> set{first, last};
  value_type::print_summary();
}

template <typename I>
void vector_instrumented(const std::size_t n, I first, I last) {
  using value_type = typename std::iterator_traits<I>::value_type;
  std::vector<value_type> v{first, last};
  value_type::initialize(n);
  std::sort(v.begin(), v.end());
  auto it = std::unique(v.begin(), v.end());
  value_type::print_summary();
}

int main() {
  using value_type = instrumented<int>; // this is the difference from test_time.cpp
  //basically we are instrumenting an integer; we are monitoring how many operations we are doing with him
  //we won't use virtual functions, so we won't have waste of memory, because it won't occupy more memory than an int;
  //the program will be slower, because we are doing more things
  //also, the algorithms don't change apart from the use of the structure time substituted with initialize(n)
  //why isn't it called with the . but with the ::? Because it's a static function!!
  
  value_type::print_header();
  for (std::size_t n = 16; n < (1 << 25); n <<= 1) {
    std::vector<value_type> v(n);
    std::iota(v.begin(), v.end(), value_type(-1024));
    std::random_shuffle(v.begin(), v.end());
    for (std::size_t i = 0; i < n; ++i)
      v[i] = int{v[i]} & 255;

    set_instrumented(n, v.begin(), v.end());
    //vector_instrumented(n, v.begin(), v.end()); // with instrumented you can see that this one does a LOT of more operations wrt the set one, but is faster;
    //The reason behind this is the memory location; 
    //with vector, the elements are contiguous in memory;
    //also, the less operations performed in set cost a lot with doubles, not really with integers
    //NB: it's always a good thing to verify if the algorithm works:
    //in this case we should have at least 1024 different numbers, so the size of the array should be 1024 (of course, only when n is more than 1024)
  }
}
