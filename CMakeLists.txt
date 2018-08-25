cmake_minimum_required(VERSION 2.6)
project(riscv_sim)

add_executable(riscv_sim main.cpp)

install(TARGETS riscv_sim RUNTIME DESTINATION bin)
