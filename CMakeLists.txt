cmake_minimum_required(VERSION 3.16)
project(mo_rk2)

set(CMAKE_CXX_STANDARD 17)

add_executable(mo_rk2 main.cpp GeneticAlgorithm.cpp GeneticAlgorithm.hpp)