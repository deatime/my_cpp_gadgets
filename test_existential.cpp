#include <iostream>
#include <vector>
#include <string_view>
#include "existential.hpp"
using std::cout, std::endl;
using std::string, std::string_view;
using std::vector;

class Cat {
  string name;
public:
  Cat(string_view name): name(std::forward<decltype(name)>(name)) {}
  auto makeSound(string_view mood) {
    cout << "Cat "<< name << "(" << mood << "): Meow!" << endl;
  }
};

class Dog {
public:
  auto makeSound(string_view mood) {
    cout << "Dog(" << mood << "): Woof!" << endl;
  }
};

struct Stage1 { Convertable convert(); string type() { return "class stage 1"; } };
struct Stage2 { Convertable convert(); string type() { return "class stage 2"; } };
struct Stage3 { Convertable convert(); string type() { return "class stage 3"; } };

Convertable Stage1::convert() {
  cout << "1 convert to 2" << endl;
  return Stage2{};
}
Convertable Stage2::convert() {
  cout << "2 convert to 3" << endl;
  return Stage3{};
}
Convertable Stage3::convert() {
  cout << "3 convert to 1" << endl;
  return Stage1{};
}

auto printType(auto&& vec) {
  int len = size(vec);
  cout << endl;
  for (int i = 0; i < len; ++i) {
    cout << i << ": " << vec[i].type() << endl;
  }
  cout << endl;
}

int main() {
  Animal cat{Cat{"Tom"}};
  Animal dog{Dog{}};
  cat.makeSound("happily");
  dog.makeSound("sadly");

  vector<Convertable> cvts{Stage1{}, Stage2{}, Stage3{}};

  printType(cvts);
  for (auto& cvt: cvts) cvt = cvt.convert();
  printType(cvts);
  for (auto& cvt: cvts) cvt = cvt.convert();
  printType(cvts);
  for (auto& cvt: cvts) cvt = cvt.convert();
  printType(cvts);
}
