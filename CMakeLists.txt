cmake_minimum_required(VERSION 3.27)
project(InvestmentPortfolio)

set(CMAKE_CXX_STANDARD 14)

include_directories("../jsoncpp")

add_executable(InvestmentPortfolio
        BTree.cpp
        BTree.h
        heap2.cpp
        heap2.h
        main.cpp)
