#ifndef __PERMUTE_H
#define __PERMUTE_H

#include <functional>
#include <memory>

// can only flip 2 args
// template <typename F>
// struct Flip;
// 
// template <typename R, typename A1, typename A2>
// struct Flip<std::function<R(A1, A2)>> {
//   using F = std::function<R(A1, A2)>;
//   std::shared_ptr<F> pf;
//   
//   Flip(std::shared_ptr<F> pf): pf(pf) {}
// 
//   auto operator()(auto&& a1, auto&& a2) {
//     return (*pf)(std::forward<decltype(a2)>(a2), 
//                  std::forward<decltype(a1)>(a1));
//   }
// };
// 
// auto flip(auto&& func) {
//   using FF = decltype(std::function(func));
//   return Flip<FF>(std::make_shared<FF>(func));
// }

template <typename F>
struct Flip;

template <typename R, typename... Args>
struct Flip<std::function<R(Args...)>> {
  using F = std::function<R(Args...)>;
  std::shared_ptr<F> pf;
  
  Flip(std::shared_ptr<F> pf): pf(pf) {}

  auto operator()(auto&&... args) {
    constexpr size_t N = sizeof...(args);
    return impl<N>(std::make_index_sequence<N>{}, std::forward_as_tuple(args...));
  }

  template <size_t N, size_t... Is>
  auto impl(std::index_sequence<Is...>, auto&& tup) {
    return (*pf)(std::forward<decltype(std::get<N-1-Is>(tup))>(std::get<N-1-Is>(tup))...); 
  }
};

auto flip(auto&& func) {
  using FF = decltype(std::function(func));
  return Flip<FF>(std::make_shared<FF>(func));
}

template <typename F, size_t... Is>
struct Permute;

template <typename R, typename... Args, size_t... Is>
struct Permute<std::function<R(Args...)>, Is...> {
  using F = std::function<R(Args...)>;
  std::shared_ptr<F> pf;
  
  Permute(std::shared_ptr<F> pf): pf(pf) {}

  auto operator()(auto&&... args) {
    auto tup = std::forward_as_tuple(args...);
    return (*pf)(std::forward<decltype(get<Is>(tup))>(get<Is>(tup))...);
  }
};

template <size_t... Is>
auto permute(auto&& func) {
  using FF = decltype(std::function(func));
  return Permute<FF, Is...>(std::make_shared<FF>(func));
}

#endif
