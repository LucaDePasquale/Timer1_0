cmake_minimum_required(VERSION 3.30)
project(Timer1_0)

set(CMAKE_CXX_STANDARD 20)
# Trova la libreria Curses (ncurses)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(Timer1_0 main.cpp
        Observer.h
        Subject.h
        Timer.cpp
        Timer.h
        Datetime.cpp
        Datetime.h
        Gui.cpp
        Gui.h)

# Linka ncurses
target_link_libraries(Timer1_0 ${CURSES_LIBRARIES})
