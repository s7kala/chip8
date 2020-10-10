#ifndef CH8EXCEPTS_H
#define CH8EXCEPTS_H

#include <exception>
#include <string>

class ProcessorException : public std::exception {
    public:
        explicit ProcessorException(std::string msg): message{std::move(msg)} {}
        std::string& what() { return message; }
        ~ProcessorException() override = default;
    protected:
        std::string message;
};

class InvalidCPUInstruction : public ProcessorException {
    public:
        explicit InvalidCPUInstruction(const std::string& msg): ProcessorException(msg) {}
};



#endif
