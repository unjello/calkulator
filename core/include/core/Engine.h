// andrzej lichnerowicz, unlicensed (~public domain)
#pragma once

#include <string>


#if defined(_WIN32)
#   if defined(CORE_EXPORTS)
#   	define CORE_API __declspec(dllexport)
#   else
#	    define CORE_API __declspec(dllimport)
#   endif
#else
#   define CORE_API
#endif

namespace _0xaL::calkulator::core {
    struct Boxed_Value {
        long double real;
        long long dec;
        long long hex;
        long long oct;
        std::string bin;

        Boxed_Value() : real(0.0), dec(0), hex(0), oct(0), bin("0") {}
    };

    class Calkulator {
    public:
        Boxed_Value const eval(const char* first) const;
    };
}