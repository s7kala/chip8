#include "register.h"

#include <utility>

Register::Register(std::string type): type{std::move(type)}, data{0} {}

void Register::write(char d) {
    data = d;
}
