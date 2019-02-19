// Copyright [year] <Copyright Owner>

#pragma once

#include <tuple>

template <typename T>
struct function_traits;

template <typename Ret, typename... Args>
struct function_traits<Ret(Args...)> {
    using return_type = Ret;
    using type = Ret(Args...);
    using arg_tuple_t = std::tuple<Args...>;
    static constexpr size_t num_args = sizeof...(Args);

    template<size_t I>
    struct args {
        static_assert(I < num_args, "index out of bound");
        using type = typename std::tuple_element<I, arg_tuple_t>::type;
    };
};

template <typename Ret, typename... Args>
struct function_traits<Ret(Args..., ...)>
    : function_traits<Ret(Args...)> {};

template <typename Ret, typename... Args>
struct function_traits<Ret(*)(Args...)>
    : function_traits<Ret(Args...)> {};

template <typename Ret, typename... Args>
struct function_traits<Ret(*)(Args..., ...)>
    : function_traits<Ret(Args...)> {};

template <typename Ret, typename C, typename... Args>
struct function_traits<Ret(C::*)(Args...)>
    : function_traits<Ret(Args...)> {};

template <typename Ret, typename C, typename... Args>
struct function_traits<Ret(C::*)(Args...) const>
    : function_traits<Ret(Args...)> {};

template <typename Ret, typename C, typename... Args>
struct function_traits<Ret(C::*)(Args...) volatile>
    : function_traits<Ret(Args...)> {};

template <typename Ret, typename C, typename... Args>
struct function_traits<Ret(C::*)(Args...) const volatile>
    : function_traits<Ret(Args...)> {};

template<typename Callable>
struct function_traits
    : function_traits<decltype(&Callable::operator())> {};
