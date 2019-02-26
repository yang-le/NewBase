// Copyright [year] <Copyright Owner>

#pragma once

#include <type_traits>

namespace nb {
namespace utility {
// the c++14 integer_sequence
template <class T, T... Ints>
struct integer_sequence {  // sequence of integer parameters
  static_assert(std::is_integral<T>::value,
                "integer_sequence<T, I...> requires T to be an integral type.");

  typedef integer_sequence<T, Ints...> type;
  typedef T value_type;

  static constexpr size_t size() noexcept {
    // get length of parameter list
    return (sizeof...(Ints));
  }
};

template <size_t... Ints>
struct index_sequence : integer_sequence<size_t, Ints...> {};

// ALIAS TEMPLATE make_integer_sequence
template <bool Negative, bool Zero, class Int_con, class Int_seq>
struct make_seq {
  // explodes gracefully below 0
  static_assert(!Negative,
                "make_integer_sequence<T, N> requires N to be non-negative.");
};

// ends recursion at 0
template <class T, T... Ints>
struct make_seq<false, true, std::integral_constant<T, 0>,
                integer_sequence<T, Ints...>> : integer_sequence<T, Ints...> {};

// counts down to 0
template <class T, T Ix, T... Ints>
struct make_seq<false, false, std::integral_constant<T, Ix>,
                integer_sequence<T, Ints...>>
    : make_seq<false, Ix == 1, std::integral_constant<T, Ix - 1>,
               integer_sequence<T, Ix - 1, Ints...>> {};

template <class T, T Size>
struct make_integer_sequence :
    make_seq < Size<0, Size == 0, std::integral_constant<T, Size>,
                             integer_sequence<T>>::type {};

template <size_t Size>
struct make_index_sequence : make_integer_sequence<size_t, Size> {};

template <class... T>
struct index_sequence_for : make_index_sequence<sizeof...(T)> {};
}  // namespace utility
}  // namespace nb
