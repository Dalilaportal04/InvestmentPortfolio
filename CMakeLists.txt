cmake_minimum_required(VERSION 3.27)
project(InvestmentPortfolio)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(InvestmentPortfolio
        Push_Test.cpp
        Push_Test.h)
