#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

class Observer;
struct Info {
    int row, col;

};

class Subject {
    std::vector<Observer*> observers;
public:
    void attach(Observer*);
    void notifyObservers();
    virtual Info getInfo() const = 0;
    virtual ~Subject() = default;
};


#endif
