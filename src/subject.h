#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <cstdint>

class Observer;
struct Info {
    std::vector<uint8_t> sprite;
    uint8_t Vx, Vy;
    // keyboard
    uint16_t opcode;
};

class Subject {
    std::vector<Observer*> observers;
public:
    void attach(Observer*);
    bool notifyObservers();
    virtual Info getInfo() const = 0;
    virtual ~Subject() = default;
};


#endif
