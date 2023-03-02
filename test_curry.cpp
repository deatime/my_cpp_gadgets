#include <iostream>
#include <string>
#include <string_view>
#include "curry.hpp"

using std::cout, std::endl;
using std::string, std::string_view;

int add3(int a, int b, int c) {
  return a + b + c;
}

int f0() {
  cout << "f0 called: ";
  return 0xf0;
} 

void overload(int, int) { // 3 overloaded functions with same name
  cout << "void(int, int) called" << endl;
}
void overload(int, int, int) {
  cout << "void(int, int, int) called" << endl;
}
void overload(string_view, string_view) {
  cout << "void(string_view, string_view) called" << endl;
}


class A {
public:
  string str;
  A(string str): str(str) {}
  A(A const& other): str(other.str) { 
    cout << str << ":        copy constructor called" << endl; 
  }
  A(A     && other): str(std::move(other.str)) { 
    cout << str << ":        move constructor called" << endl; 
  }
};

class Callable {
public:
  Callable() = default;
  Callable(Callable const& other) { cout << "callable: copy constructor called" << endl; }
  Callable(Callable     && other) { cout << "callable: move constructor called" << endl; }
  void operator()(A const& a, A const& b, A const& c) {
    cout << a.str << ", "<< b.str << ", "<< c.str << ": Callable::operator() called" << endl;
  }
};

int main() {
  auto cur_add3 = curry(add3);
  cout << "cur_add3(1, 3, 2) -> " << cur_add3(1, 3, 2) << endl; // use as original function
  cout << "cur_add3(1)(3)(2) -> " << cur_add3(1)(3)(2) << endl; // use as curried function
  cout << "cur_add3(1, 3)()()(2) ->" << cur_add3(1, 3)()()(2) << endl; // or any comination
  // can't be called since all arguments have be applied 
  // cout << cur_add3(1)(3, 2)() << endl;
  
  auto cur_f0 = curry(f0);
  cout << cur_f0() << endl; // 0 argument functions are allowed   

  auto add2 = [](int a, int b) { return a + b; }; // lambda
  auto addWith4 = curry(add2)(4);
  cout << "addWith4(8) -> " << addWith4(8) << endl;
  cout << "addWith4(6) -> " << addWith4(6) << endl;

  Callable call; // class with operator() overloaded
  auto cur_call = curry(std::move(call));
  A aa("a"), ab("b"), ac("c");
  cur_call(aa)(ab)(ac);

  // overloaded functions need explicit type conversion
  // auto cur_fOverload1 = curry(fOverload); // mutiple candidates
  auto cur_overload1 = curry((void(&)(int, int))overload); 
  auto cur_overload2 = curry((void(&)(int, int, int))overload); 
  auto cur_overload3 = curry((void(&)(string_view, string_view))overload); 
  cur_overload1(1)(2);
  cur_overload2(1)(2)(3);
  cur_overload3("hello ", "world");
}

