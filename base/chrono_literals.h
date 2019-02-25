// Copyright [year] <Copyright Owner>

#pragma once

#include <chrono>
#include "base/macros.h"

NEW_BASE_BEGIN

// the c++14 std::chrono_literals

// duration LITERALS
inline namespace literals {
inline namespace chrono_literals {
inline std::chrono::hours operator"" _h(
    unsigned long long val) {  // NOLINT(runtime/int)
  // return integral hours
  return (std::chrono::hours(val));
}

inline std::chrono::duration<double, std::ratio<3600>> operator"" _h(
    long double val) {  // return floating-point hours
  return (std::chrono::duration<double, std::ratio<3600>>(val));
}

inline std::chrono::minutes operator"" _min(
    unsigned long long val) {  // NOLINT(runtime/int)
  // return integral minutes
  return (std::chrono::minutes(val));
}

inline std::chrono::duration<double, std::ratio<60>> operator"" _min(
    long double val) {
  // return floating-point minutes
  return (std::chrono::duration<double, std::ratio<60>>(val));
}

inline std::chrono::seconds operator"" _s(
    unsigned long long val) {  // NOLINT(runtime/int)
  // return integral seconds
  return (std::chrono::seconds(val));
}

inline std::chrono::duration<double> operator"" _s(long double val) {
  // return floating-point seconds
  return (std::chrono::duration<double>(val));
}

inline std::chrono::milliseconds operator"" _ms(
    unsigned long long val) {  // NOLINT(runtime/int)
  // return integral milliseconds
  return (std::chrono::milliseconds(val));
}

inline std::chrono::duration<double, std::milli> operator"" _ms(
    long double val) {
  // return floating-point milliseconds
  return (std::chrono::duration<double, std::milli>(val));
}

inline std::chrono::microseconds operator"" _us(
    unsigned long long val) {  // NOLINT(runtime/int)
  // return integral microseconds
  return (std::chrono::microseconds(val));
}

inline std::chrono::duration<double, std::micro> operator"" _us(
    long double val) {
  // return floating-point microseconds
  return (std::chrono::duration<double, std::micro>(val));
}

inline std::chrono::nanoseconds operator"" _ns(
    unsigned long long val) {  // NOLINT(runtime/int)
  // return integral nanoseconds
  return (std::chrono::nanoseconds(val));
}

inline std::chrono::duration<double, std::nano> operator"" _ns(
    long double val) {
  // return floating-point nanoseconds
  return (std::chrono::duration<double, std::nano>(val));
}
}  // namespace chrono_literals
}  // namespace literals

NEW_BASE_END
