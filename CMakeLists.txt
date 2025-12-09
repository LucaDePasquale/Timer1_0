cmake_minimum_required(VERSION 3.30)
project(Timer1_0)

set(CMAKE_CXX_STANDARD 20)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_library(core
        src/Timer.cpp
        src/Datetime.cpp
        src/Observer.h
        src/Subject.h
        src/Timer.h
        src/Datetime.h
)


target_include_directories(core PUBLIC src)


add_executable(Timer1_0
        src/main.cpp
        src/Gui.cpp
        src/Gui.h
)

target_link_libraries(Timer1_0
        core
        ${wxWidgets_LIBRARIES}
)


add_subdirectory(test)



