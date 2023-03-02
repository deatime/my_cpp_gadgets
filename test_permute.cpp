#include <iostream>
#include <string>
#include "permute.hpp"
using namespace std;

struct Cont {
  std::string str;
  Cont(auto&& str): str(std::forward<decltype(str)>(str)) {}
  Cont(const Cont& other): Cont(other.str) {
    cout << str << " copy" << endl;
  }
  Cont(Cont&& other): Cont(std::move(other.str)) {
    cout << str << " move" << endl;
  }
};

Cont cat(const Cont& a, const Cont& b) {
  return Cont(a.str + b.str);
}

Cont cat3(const Cont& a, const Cont& b, const Cont& c) {
  return Cont(a.str + b.str + c.str);
}

int main() {
  Cont a("a"), b("b"), c("c");
  cout << "cat: "  << cat(a, b).str << endl;
  cout << "cat3: " << cat3(a, b, c).str << endl;

  auto flip_cat = flip(cat);
  auto flip_cat3 = flip(cat3);
  cout << "flip: "  << flip_cat(a, b).str << endl;
  cout << "flip3: " << flip_cat3(a, b, c).str << endl;

  auto permute_cat3 = permute<1, 0, 2>(cat3);
  cout << "permute(1, 0, 2): " << permute_cat3(a, b, c).str << endl;
}
