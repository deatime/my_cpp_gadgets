#include <iostream>
#include <string>
#include "permute.hpp"
#include "curry.hpp"
using namespace std;

class Cont {
  std::string str;
public:
  Cont(auto&& str): str(std::forward<decltype(str)>(str)) {}
  Cont(const Cont& other): Cont(other.str) {
    cout << str << " copy" << endl;
  }
  Cont(Cont&& other): Cont(std::move(other.str)) {
    cout << str << " move" << endl;
  }
  auto getStr() const {
    return str;
  }
  friend ostream& operator<<(ostream& ost, const Cont& cont) {
    return ost << cont.str;
  }
};

Cont cat(const Cont& a, const Cont& b) {
  return Cont(a.getStr() + b.getStr());
}

Cont cat3(const Cont& a, const Cont& b, const Cont& c) {
  return Cont(a.getStr() + b.getStr() + c.getStr());
}

int main() {
  Cont a("a"), b("b"), c("c");
  cout << "cat: "  << cat(a, b) << endl;
  cout << "cat3: " << cat3(a, b, c) << endl;

  auto flip_cat = flip(cat);
  auto flip_cat3 = flip(cat3);
  cout << "flip: "  << flip_cat(a, b) << endl;
  cout << "flip3: " << flip_cat3(a, b, c) << endl;

  auto permute_cat3 = permute<1, 0, 2>(cat3);
  cout << "permute(1, 0, 2): " << permute_cat3(a, b, c) << endl;

  auto curried_flip_cat3 = curry<decltype(flip_cat3)::F>(flip_cat3);
  cout << "curried_flip_cat3: " << curried_flip_cat3(a)(b)(c) << endl;

  auto curried_permute_cat3 = curry<decltype(flip_cat3)::F>(flip_cat3);
  cout << "curried_permute_cat3: " << curried_flip_cat3(a)(b)(c) << endl;
}
