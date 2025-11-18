cmake_minimum_required(VERSION 3.30)
project(Timer1_0)

set(CMAKE_CXX_STANDARD 20)

add_executable(Timer1_0 main.cpp
        Observer.h
        Subject.h
        Timer.cpp
        Timer.h
        Datatime.cpp
        Datatime.h)
