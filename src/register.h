#ifndef REGISTER_H
#define REGISTER_H

#include <string>

class Register {
    public:
        Register(std::string type = "");
        void write(char data);
    private:
        std::string type;
        char data;
};

#endif