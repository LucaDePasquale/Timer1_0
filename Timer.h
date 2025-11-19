//
// Created by depa on 18.11.25.
//

#ifndef TIMER_H
#define TIMER_H

#include "Subject.h"
#include "Observer.h"
#include <list>
#include <vector>
#include <chrono>

class Timer :public Subject {
public:
    Timer (): remainingTime(0),isrunning(false),duration(0) {}
    ~Timer() override{}
    int getRemainingTime() const;
    int getDuration() const;
    bool isRunning() const;
    void setDuration(int s);

    void setUpTimer();
    void stopTimer();

    void restartTimer();
    void resumeTimer();
    void getTick();

    void subscribe(Observer* o) override;
    void unsubscribe(Observer* o) override;
    void notify() override;




private:
    int remainingTime;
    bool isrunning;
    int duration;
    std::list<Observer*> observers;

    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> last_checked;

};





#endif //TIMER_H
