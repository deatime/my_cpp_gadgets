#ifndef __CURRY_H
#define __CURRY_H

#include <tuple>
#include <functional>
#include <type_traits>
#include <memory>

// the curried function can only execute once
// if the class takes the ownership of the function
// so I replaced it with shared_ptr

template<typename F, typename Tup, int N>
struct Curry;

template<typename F, typename Tup>
struct Curry<F, Tup, 0> {
  // F f; 
  std::shared_ptr<F> pf;
  // Curry(F&& f, Tup&&) : f(std::forward<F>(f)) {}
  Curry(std::shared_ptr<F> pf, Tup&&) : pf(pf) {}

  auto operator()() { return (*pf)(); }
};

template<typename F, typename Tup, int N>
struct Curry {
  // F f;
  std::shared_ptr<F> pf;
  Tup t;
  // Curry(F&& f, Tup&& t): f(std::forward<F>(f)), t(std::forward<Tup>(t)) {}
  Curry(std::shared_ptr<F> pf, Tup&& t): pf(pf), t(std::forward<Tup>(t)) {}

  template<typename... Args>
  auto operator()(Args&&... args) {
    auto nt = std::tuple_cat(
      std::forward<Tup>(t), 
      std::forward_as_tuple(std::forward<Args>(args))...); // no overhead to forward args
    using NT = std::decay_t<decltype(nt)>;
    if constexpr (sizeof...(args) == N) {
      // return std::apply(f, nt);
      return std::apply(*pf, nt);
    } else {
      return Curry<F, decltype(nt), N - sizeof...(args)>(
        // std::forward<F>(f), 
        pf,
        std::forward<NT>(nt));
    }
  }
};

template<typename T> // count arguments of a callable
struct count_arg;

template<typename R, typename ...Args> 
struct count_arg<std::function<R(Args...)>> {
  static const size_t value = sizeof...(Args);
};

template<typename F> 
inline constexpr int count_arg_v = count_arg<F>::value;

template<typename F>
auto curry(F&& f) { // helper function
  using FF = decltype(std::function(f));
  constexpr int nargs = count_arg_v<FF>;
  // return Curry<FF, std::tuple<>, nargs>(std::forward<F>(f), std::tuple());
  return Curry<FF, std::tuple<>, nargs>(std::make_shared<FF>(f), std::tuple());
}

#endif
