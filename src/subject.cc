#include "subject.h"
#include "observer.h"
#include "link.h"

void Subject::attach(Observer *obs) {
    observers.emplace_back(obs);
}

void Subject::notifyObservers() {
    for(auto &obs: observers) {
        obs->notify(*this);
    }
}