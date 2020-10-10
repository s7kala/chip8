#######################################################
### This Makefile builds the assembler/disassembler ###
#######################################################

EXEC = ch8asm
CXX = g++
CXXFLAGS = -std=c++14 -O2 -Wall -Werror -MMD
OBJECTS = asm.o dasm.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	-rm -f *.o *.d ${EXEC}
