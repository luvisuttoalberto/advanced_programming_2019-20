#include <array>
#include <iostream>
#include <vector>

//note: in c in classes you can put both data and function; in structures you can't;
//in c++ you can do this in both; the difference between class and struct is seen after


struct Point_s {
  double x;
  double y;
  void print();
};  // note ; at the end
//here, once we are inside the struct Point_s, we can access x and y without writing the Point_s in front; same with class
//The main difference between struct and class is:
//In the struct everything is public.
//in the class the default visibility is private; in fact, when we define the function inside the class later, we have to write "public:"
void Point_s::print() {
  std::cout << "Structure. x = " << x << "; y = " << y << std::endl;
}

class Point_c {
//here we could have written the following line and it would have been the same
//private:
  double x;
  double y;

 public:
  void print() {
    std::cout << "Class. x = " << x << "; y = " << y << std::endl;
  }  // note no ; at the end
};   // note ; at the end

int main() {
  Point_s ps;
  ps.x = 9.9;
  ps.y = 3. / 7;

  ps.print();

  Point_c pc;
  //the following gives an error cause x is private!!
  // pc.x =7.6; // error
  pc.print();  // Instead, I can access private data through public functions. That's why I had to make the function public

  Point_s* p = &ps;
  //N.B.: you can't use the . syntax to access the value of the pointer, this is the sintax for the function inside a class! 
  //You must use the arrow operator
  p->x = 0.0;
  p->print();
  //Using an alias you can do it with the usual pointer syntax
  auto& pr = ps;
  ++pr.x;
  pr.print();

  Point_s array_of_structs[8];  // built-in array
  array_of_structs[0].x = 1;
  array_of_structs[0].y = 2;

  std::array<Point_s, 5> as;
  as[3].x = 3;

  std::vector<Point_s> vs;
  //here you are not putting ps inside of vs; you are copying ps in a new Point_s and putting that into vs (copy semantic, see next lessons)
  vs.push_back(ps);
  vs[0].x = 999;
  ps.x = 11;
  ps.print();
  vs[0].print();

  return 0;
}
