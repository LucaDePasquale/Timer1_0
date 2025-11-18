//
// Created by depa on 18.11.25.
//

#ifndef DATATIME_H
#define DATATIME_H
#include <chrono>

enum Viewmode {
    LONG_FORMAT,
    MEDIUM_FORMAT,
    SHORT_FORMAT,
};

class DateTime {
public:
    DateTime() : mode(LONG_FORMAT) {}
    std::string updateCurrent() const;

    void setViewmode();
private:
    Viewmode mode;
};






#endif //DATATIME_H
