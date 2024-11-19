//
// Created by 9tail on 9/12/2024.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/main.cpp"

TEST_CASE("First Test", "[positive]"){
    int a, b;
    a = 15;
    b = 15;
    REQUIRE(sum(a,b) == 35);
}