//
// Created by depa on 19.11.25.
//

#include "Gui.h"
#include <ncurses.h>
#include <iomanip>
#include <sstream>
#include <iostream>

void GUI::init() {
    // Ncurses Settings
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(0);

    window_width = getmaxx(stdscr);
    window_height = getmaxy(stdscr);

    // Logo Topbar
    printLogo();
    mvhline(8, 0, ACS_HLINE, window_width);

    // Date and Hour Widget
    printCenter(8, " Date & Hour ");
    printDateTime();

    // Timer Widget
    mvhline(13, 0, ACS_HLINE, window_width);
    printCenter(13, " Timer ");
    update();

    // Footer
    mvhline(window_height-5, 0, ACS_HLINE, window_width);
    mvprintw(window_height-4, 1, "FORMAT: V -change format");
    mvprintw(window_height-3, 1, "TIMER:  S -start/pause | R -restart | UP: +1s | DOWN: -1s");
    mvprintw(window_height-2, 1, "APP:    Q -quit");

    // Window Border
    box(stdscr, 0, 0);
    refresh();
}

void GUI::printLogo() const {
    std::istringstream logo(ascii_art);
    std::string line;
    int row = 1;

    while (std::getline(logo, line)) {
        printCenter(row++, line);
    }

    printCenter(6, "by Neri Saldutti");
}

void GUI::printDateTime() const {
    mvhline(10, 1, ' ', window_width-2);
    printCenter(10, datetime->updateCurrent());

    refresh();
}

void GUI::update() {
        if (timer->getRemainingTime() == 0) {
            printTimerStatus("0");
            beep();
        }
        printCenter(15, formatTime(timer->getRemainingTime()));

    refresh();
}

void GUI::printTimerStatus(const std::string &status) const {
    mvhline(16, 1, ' ', window_width-2);
    if (status == "running") {
        printCenter(16, "TIMER IS RUNNING");
    } else if (status == "paused") {
        printCenter(16, "TIMER IS PAUSED");
    } else if (status == "0") {
        printCenter(16, "TIMER IS UP!");
    } else if (status == " ") {
        mvhline(16, 1, ' ', window_width-2);
    }

    refresh();
}

void GUI::printError(const std::string &error) const {
    mvhline(16, 1, ' ', window_width-2);
    printCenter(16, "ERROR: " + error);
}

void GUI::printCenter(const int row, const std::string &text) const {
    const int col = (window_width - static_cast<int>(text.length())) / 2;
    mvprintw(row, col, text.c_str());
}

std::string GUI::formatTime(const int seconds) {
    std::ostringstream formatted_time;
    const int hours = seconds / 3600;
    const int minutes = (seconds - hours * 3600) / 60;
    const int remainingSeconds = seconds % 60;
    formatted_time << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << remainingSeconds;
    return formatted_time.str();
}

void GUI::close() {
    endwin();
}

void GUI::attach() {
    timer->subscribe(this);
}

void GUI::detach() {
    timer->unsubscribe(this);
}
