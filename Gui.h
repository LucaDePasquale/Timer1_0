//
// Created by depa on 19.11.25.
//

#ifndef GUI_H
#define GUI_H



#include <chrono>

#include "Datetime.h"
#include "Observer.h"
#include "Timer.h"

// Graphic User Interface Class
class GUI : public Observer{
public:
    explicit GUI(const std::shared_ptr<Timer> &t, const std::shared_ptr<DateTime> &d) : timer(t), datetime(d) {
        timer->subscribe(this);
    }
    ~GUI() override {
        timer->unsubscribe(this);
    }

    // Window Controls
    void init();
    void close();

    // Interfaces
    void printLogo() const;
    void printDateTime() const;
    void printTimerStatus(const std::string &status) const;

    void printError(const std::string &error) const;

    // Format
    void printCenter(int row, const std::string &text) const;
    std::string formatTime(int seconds);

    // Observer Methods
    void attach() override;
    void detach() override;
    void update() override;
private:
    int window_width = 0, window_height = 0;

    std::string ascii_art =" Timer ";
    std::shared_ptr<Timer> timer;
    std::shared_ptr<DateTime> datetime;
};



#endif //GUI_H
