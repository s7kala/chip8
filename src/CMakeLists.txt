cmake_minimum_required(VERSION 3.17)
project(src)

set(CMAKE_CXX_STANDARD 14)

# add_compile_options(-DETI660)

add_executable(src main.cc mcomp.cc processor.cc register.cc memory.cc)
