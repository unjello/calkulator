#include <core/Engine.h>
#include "catch.hpp"


SCENARIO("Can evaluate simple numbers", "[basics]") {
    WHEN("Expression is empty") {
        THEN("it evaluates to zero") {
            REQUIRE(static_cast<uint32_t>(Calculate("")) == 0);
        }
    }
}
