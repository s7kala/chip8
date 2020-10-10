/*
 * CHIP-8 Assembler/Disassembler Exceptions
 * $PROJECT_ROOT/asm/excepts.h
 */

#ifndef EXCEPTS_H
#define EXCEPTS_H

#include <exception>
#include <string>

class AsmException : public std::exception {
    public:
        explicit AsmException(std::string msg, bool isAssemble): 
            message{std::move(msg)},
            isAssemble{isAssemble} {}
        bool isAsm() { return isAssemble; }
        std::string& what() { return message; }
        ~AsmException() override = default;
    protected:
        std::string message;
        bool isAssemble;
};


#endif
