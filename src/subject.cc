#include "subject.h"
#include "observer.h"

void Subject::attach(Observer *obs) {
    observers.emplace_back(obs);
}

bool Subject::notifyObservers() {
    bool VF = false;
    for(auto &obs: observers) {
        if(obs->notify(*this))
            VF = true;
    }
    return VF;
}
