
find_package(GTest REQUIRED)

# search all file .cpp in the directory test
file(GLOB TEST_SOURCES *.cpp)


add_executable(runTests ${TEST_SOURCES})

# Include the header
target_include_directories(runTests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Link to library core and GoogleTest
target_link_libraries(runTests
        core
        GTest::gtest
        GTest::gtest_main
        pthread
)

# Regist test
add_test(NAME AllTests COMMAND runTests)