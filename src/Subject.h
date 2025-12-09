//
// Created by depa on 18.11.25.
//

#ifndef SUBJECT_H
#define SUBJECT_H
#include "Observer.h"
class Subject {
public:
    virtual ~Subject() {}
    virtual void subscribe(Observer* o) = 0;
    virtual void unsubscribe(Observer* o) = 0;
    virtual void notify() = 0;
};

#endif //SUBJECT_H
