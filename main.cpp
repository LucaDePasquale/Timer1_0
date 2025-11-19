#include <iostream>
#include <ncurses.h>

#include "Gui.h"
#include "Timer.h"
#include "Datetime.h"

int main() {
    auto timer = std::make_shared<Timer>();
    auto date_time = std::make_shared<DateTime>();
    const auto gui = std::make_unique<GUI>(timer, date_time);

    bool terminate = false;
    gui->init();

    while (!terminate) {
        const int ch = getch();
        gui->printDateTime();
        switch (ch) {
            case 'v':
                date_time->setViewmode();
            break;
            case 's':
                if (!timer->isRunning()) {
                    try {
                        timer->setUpTimer();
                        gui->printTimerStatus("running");
                    } catch (const std::exception& e) {
                        gui->printError(e.what());
                    }
                } else {
                    timer->stopTimer();
                    gui->printTimerStatus("paused");
                }
            break;
            case 'r':
                try {
                    timer->restartTimer();
                    gui->printTimerStatus(" ");
                } catch (std::exception& e) {
                    gui->printError(e.what());
                }

            break;
            case KEY_UP:
                if (!timer->isRunning()) {
                    timer->setDuration('u');
                    gui->printTimerStatus(" ");
                }
            break;
            case KEY_DOWN:
                if (!timer->isRunning()) {
                    timer->setDuration('d');
                    gui->printTimerStatus(" ");
                }
            break;
            case 'q':
                terminate = true;
            break;
            default:
                ;
        }
        if (timer->isRunning())
            timer->getTick();
    }

    gui->close();

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.