// andrzej lichnerowicz, unlicensed (~public domain)
#include "catch.hpp"
#include <core/Engine.h>

//using _0xaL::calkulator::core::Calculate;

SCENARIO("Can evaluate simple numbers", "[basics]") {
    GIVEN("Expression is empty") {
        THEN("boxed value evaluates to zero") {
            //REQUIRE(Calculate("") == 0.0);
        }   
    }
    GIVEN("Expression is a single number") {
        WHEN("the number is decimal integer") {
            THEN("it evaluates to an integer") {
                //REQUIRE(Calculate("10") == 10);
            }
        }
    }
}