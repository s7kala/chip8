#ifndef CH8EXCEPTS_H
#define CH8EXCEPTS_H

#include <exception>
#include <stdexcept>
#include <string>

class ProcessorException : public std::exception {
    public:
        explicit ProcessorException(const char* msg) : m{msg} {}
        const char* what() const noexcept override { return m.what(); }
        ~ProcessorException() override = default;
    protected:
        std::runtime_error m;
};

class InvalidCPUInstruction : public ProcessorException {
    public:
        explicit InvalidCPUInstruction(const char* msg): ProcessorException(msg) {}
};

class DisplayException : public std::exception {
    public:
        explicit DisplayException(const char* msg) : m{msg} {}
        const char* what() const noexcept override { return m.what(); }
        ~DisplayException() override = default;
    protected:
        std::runtime_error m;
};


#endif
