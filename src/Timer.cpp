//
// Created by depa on 18.11.25.
//

#include <iostream>
#include <chrono>
#include "Timer.h"
void Timer::setUpTimer(){
    if(duration <= 0){
        throw std::invalid_argument("Duration must be greater than zero");
    }
    remainingTime=duration;
    start = std::chrono::steady_clock::now();
    isrunning = true;
    last_checked = start;

}
// Get next timer tick and calculate seconds
void Timer::getTick() {
    if (!isrunning) {
        return;   //no update if is paused
    }

    const auto now = std::chrono::steady_clock::now();
    const auto diff = std::chrono::duration_cast<std::chrono::seconds>(now - last_checked).count();

    if (remainingTime > 0) {
        if (diff >= 1) {
            remainingTime -= static_cast<int>(diff);
            last_checked = now;
            notify();
        }
    } else
        isrunning = false;
    notify();
}
void Timer::stopTimer(){
    isrunning = false;
}
void Timer::resumeTimer(){
    isrunning = true;
    last_checked = std::chrono::steady_clock::now();
    getTick();
    notify();

}
void Timer::restartTimer(){
    if(isrunning){
        throw std::invalid_argument("Timer is already running, stop the timer before restarting");
    }
    remainingTime = duration;
    isrunning = false;
    notify();
}
int Timer::getRemainingTime()const{
    return remainingTime;
}
int Timer::getDuration()const{
    return duration;
}
bool Timer::isRunning()const{
    return isrunning;
}
void Timer::setDuration(int s){
    if(s >=0){
        duration = s;
        remainingTime =duration;
        last_checked = std::chrono::steady_clock::now();

        notify();
    }
    else{
        throw std::invalid_argument("one of the value is invalid or all of them");}
}
//observer Methods
void Timer::subscribe(Observer* o){
    observers.push_back(o);
}
void Timer::unsubscribe(Observer* o){
    observers.remove(o);
}
void Timer::notify(){
    for(const auto& o : observers){
        o->update();
    }
}
