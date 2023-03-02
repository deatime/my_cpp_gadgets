#ifndef __EXISTENTIAL_H
#define __EXISTENTIAL_H

#include <any>
#include <string>
#include <string_view>

class Animal {
  std::any obj;
  void (*makeSoundFn)(std::any&, std::string_view);

public:
  auto makeSound(auto&& str) {
    return makeSoundFn(obj, str);
  }

  Animal(auto&& x): obj(std::forward<decltype(x)>(x)) {
    using objtype = std::decay_t<decltype(x)>;

    makeSoundFn = [](auto& obj, auto str) {
      return any_cast<objtype>(obj).makeSound(str);
    };
  }
};

class Convertable {
  std::any obj;
  Convertable (*convertFn)(std::any&);
  std::string (*typeFn)(std::any&);

public:
  auto convert() {
    return convertFn(obj);
  }
  auto type() {
    return typeFn(obj);
  }

  Convertable(auto&& x): obj(std::forward<decltype(x)>(x)) {
    using objtype = std::decay_t<decltype(x)>;

    convertFn = [](auto& obj) {
      return any_cast<objtype>(obj).convert();
    };
    typeFn = [](auto& obj) {
      return any_cast<objtype>(obj).type();
    };
  }
};

#endif
