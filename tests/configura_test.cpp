#include <catch2/catch_test_macros.hpp>

#include <memory>

#include "CConfigura.h"

TEST_CASE("Check The configuration") {
    // Arrange
    std::unique_ptr<CConfigura> config = std::make_unique<CConfigura>();

    // Act
    auto setparam = config->setParam("prueba", "123");

    // Assert
    REQUIRE(setparam == true);
}

TEST_CASE("Check getParam Ok") {
    // Arrange
    std::unique_ptr<CConfigura> config = std::make_unique<CConfigura>();
    auto setparam = config->setParam("prueba", "123");

    // Act 
    auto value = config->getParam("prueba");

    // Assert
    REQUIRE(setparam == true);
    REQUIRE(value == "123");
}

TEST_CASE("Check getParam Fail") {
    // Arrange
    std::unique_ptr<CConfigura> config = std::make_unique<CConfigura>();
    
    // Act 
    auto value = config->getParam("prueba1");

    // Assert
    REQUIRE(value == "");
}
