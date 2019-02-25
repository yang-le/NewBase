// Copyright [year] <Copyright Owner>

#pragma once

#include <tuple>
#include "base/macros.h"

NEW_BASE_BEGIN

namespace utility {
template <typename F>
struct function_traits;

template <typename Ret, typename... Args>
struct function_traits<Ret(Args...)> {
  using return_type = Ret;
  using type = Ret(Args...);
  using arg_tuple_t = std::tuple<Args...>;
  static constexpr size_t arity = sizeof...(Args);

  template <size_t I>
  struct arg {
    static_assert(I < arity,
                  "function_traits<F>::arg<I> requires I to be less than "
                  "function_traits<F>::arity.");
    using type = typename std::tuple_element<I, arg_tuple_t>::type;
  };
};

template <typename Ret, typename... Args>
struct function_traits<Ret(Args..., ...)> : function_traits<Ret(Args...)> {};

template <typename Ret, typename... Args>
struct function_traits<Ret (*)(Args...)> : function_traits<Ret(Args...)> {};

template <typename Ret, typename... Args>
struct function_traits<Ret (*)(Args..., ...)> : function_traits<Ret(Args...)> {
};

template <typename Ret, typename C, typename... Args>
struct function_traits<Ret (C::*)(Args...)> : function_traits<Ret(Args...)> {};

template <typename Ret, typename C, typename... Args>
struct function_traits<Ret (C::*)(Args...) const>
    : function_traits<Ret(Args...)> {};

template <typename Ret, typename C, typename... Args>
struct function_traits<Ret (C::*)(Args...) volatile>
    : function_traits<Ret(Args...)> {};

template <typename Ret, typename C, typename... Args>
struct function_traits<Ret (C::*)(Args...) const volatile>
    : function_traits<Ret(Args...)> {};

template <typename Callable>
struct function_traits : function_traits<decltype(&Callable::operator())> {};
}  // namespace utility

NEW_BASE_END
