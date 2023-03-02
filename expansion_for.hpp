#ifndef __EXPANSION_FOR_H
#define __EXPANSION_FOR_H

#include <cstdlib>
#include <utility>
template <typename F, size_t... Is>
constexpr void for_impl(F&& f, std::index_sequence<Is...>) {
  (f(Is), ...);
}

template <size_t N, typename F>
constexpr void for_(F&& f) {
  for_impl(std::forward<F>(f), std::make_index_sequence<N>{});
}

#endif
