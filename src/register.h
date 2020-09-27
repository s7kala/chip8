#ifndef REGISTER_H
#define REGISTER_H

#include <string>

class Register {
    public:
        explicit Register(std::string type = "", char data = 0);
        void write(char data);
    private:
        std::string label;
        char data;
};

#endif