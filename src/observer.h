#ifndef OBSERVER_H
#define OBSERVER_H

#include "subject.h"

class Observer {
public:
    virtual bool notify(const Subject &) = 0;
    virtual ~Observer() = default;
};


#endif

