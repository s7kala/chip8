#include "register.h"

#include <utility>

Register::Register(std::string type, char data):
    label{std::move(type)}, data{data} {}

void Register::write(char d) {
    data = d;
}
