cmake_minimum_required(VERSION 3.17)
project(ch8vm)

set(CMAKE_CXX_STANDARD 14)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_compile_options(-DDEBUG)
add_executable(src main.cc mcomp.cc processor.cc memory.cc subject.cc textdisplay.cc graphicsdisplay.cc ../asm/dasm.cc)
target_link_libraries(src -lcurses -lsfml-graphics -lsfml-window -lsfml-system)
