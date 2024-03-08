#include <catch2/catch_test_macros.hpp>

#include <memory>

#include "CConfigura.h"

TEST_CASE("Check The configuration") {
    std::unique_ptr<CConfigura> config = std::make_unique<CConfigura>();
    auto setparam = config->setParam("prueba", "123");
    REQUIRE(setparam == true);
}
