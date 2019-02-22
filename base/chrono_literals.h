#pragma once

#include <chrono>
#include "base/macros.h"

#ifdef _MSC_VER
#pragma warning(push) 
#pragma warning(disable: 4455)
#endif

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wliteral-suffix"
#endif

NEW_BASE_BEGIN

// the c++14 std::chrono_literals

// duration LITERALS
inline namespace literals {
    inline namespace chrono_literals {
        inline std::chrono::hours operator "" h(unsigned long long val)
        {	// return integral hours
            return (std::chrono::hours(val));
        }

        inline std::chrono::duration<double, std::ratio<3600> > operator "" h(
            long double val)
        {	// return floating-point hours
            return (std::chrono::duration<double, std::ratio<3600> >(val));
        }

        inline std::chrono::minutes operator "" min(unsigned long long val)
        {	// return integral minutes
            return (std::chrono::minutes(val));
        }

        inline std::chrono::duration<double, std::ratio<60> > operator "" min(
            long double val)
        {	// return floating-point minutes
            return (std::chrono::duration<double, std::ratio<60> >(val));
        }

        inline std::chrono::seconds operator "" s(unsigned long long val)
        {	// return integral seconds
            return (std::chrono::seconds(val));
        }

        inline std::chrono::duration<double> operator "" s(long double val)
        {	// return floating-point seconds
            return (std::chrono::duration<double>(val));
        }

        inline std::chrono::milliseconds operator "" ms(unsigned long long val)
        {	// return integral milliseconds
            return (std::chrono::milliseconds(val));
        }

        inline std::chrono::duration<double, std::milli> operator "" ms(
            long double val)
        {	// return floating-point milliseconds
            return (std::chrono::duration<double, std::milli>(val));
        }

        inline std::chrono::microseconds operator "" us(unsigned long long val)
        {	// return integral microseconds
            return (std::chrono::microseconds(val));
        }

        inline std::chrono::duration<double, std::micro> operator "" us(
            long double val)
        {	// return floating-point microseconds
            return (std::chrono::duration<double, std::micro>(val));
        }

        inline std::chrono::nanoseconds operator "" ns(unsigned long long val)
        {	// return integral nanoseconds
            return (std::chrono::nanoseconds(val));
        }

        inline std::chrono::duration<double, std::nano> operator "" ns(
            long double val)
        {	// return floating-point nanoseconds
            return (std::chrono::duration<double, std::nano>(val));
        }
    }	// inline namespace std::chrono_literals
}	// inline namespace literals

NEW_BASE_END

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#ifdef _MSC_VER
#pragma warning(pop) 
#endif
