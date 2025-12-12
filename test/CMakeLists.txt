
# Cerca GoogleTest
find_package(GTest REQUIRED)

file(GLOB TEST_SOURCES *.cpp)

add_executable(runalltest ${TEST_SOURCES})

target_include_directories(runalltest PRIVATE ../src)

target_link_libraries(runalltest
        PRIVATE
        core
        GTest::gtest
        GTest::gtest_main
        pthread
)

add_test(NAME AllTests COMMAND runalltest)
