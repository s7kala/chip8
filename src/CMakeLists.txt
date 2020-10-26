cmake_minimum_required(VERSION 3.17)
project(ch8vm)

set(CMAKE_CXX_STANDARD 14)

#add_compile_options(-DDEBUG)
add_executable(ch8vm main.cc mcomp.cc processor.cc memory.cc subject.cc
            textdisplay.cc graphicsdisplay.cc ../asm/dasm.cc keypad.cc display.cc)
target_link_libraries(ch8vm -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio)
