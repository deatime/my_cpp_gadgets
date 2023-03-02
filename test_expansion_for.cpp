#include <iostream>
#include <array>
#include "expansion_for.hpp"
using std::cout, std::endl;
using std::array;

int main() {
  for_<10>([](auto i) { // force expansion
    cout << i << endl;
  }); 
  // would be expand to
  // cout << 0 << endl;
  // cout << 1 << endl;
  // cout << 2 << endl;
  // cout << 3 << endl;
  // ...
  // cout << 9 << endl;

  // example: find min and max number of an array
  array arr{2, 3, 1, 5, 3, 5, 6, 9, 4, 7};

  int mn{arr.back()}, mx{arr.back()};
  for_<arr.size()-1>([&](auto i) {
    if (arr[i] < mn) mn = arr[i];
    if (arr[i] > mx) mx = arr[i];
  });
  
  // result
  cout << "arr: ";
  for (auto n: arr) {
    cout << n << " ";
  }
  cout << endl;
  cout << "min: " << mn << ", max: " << mx << endl;
}
