//
// Created by depa on 09.12.25.
//
#include "Timer.h"
#include <gtest/gtest.h>
#include <thread>
#include <chrono>




TEST(TimerTest, InitialValuesAreCorrect) {
    Timer t;
    EXPECT_EQ(t.getDuration(), 0);
    EXPECT_EQ(t.getRemainingTime(), 0);
    EXPECT_FALSE(t.isRunning());
}



TEST(TimerTest, SetDurationWorksCorrectly) {
    Timer t;
    t.setDuration(30);

    EXPECT_EQ(t.getDuration(), 30);
    EXPECT_EQ(t.getRemainingTime(), 30);
}

TEST(TimerTest, SetDurationThrowsOnNegative) {
    Timer t;
    EXPECT_THROW(t.setDuration(-10), std::invalid_argument);
}


TEST(TimerTest, SetUpTimerStartsTimerCorrectly) {
    Timer t;
    t.setDuration(5);
    t.setUpTimer();

    EXPECT_TRUE(t.isRunning());
    EXPECT_EQ(t.getRemainingTime(), 5);
}

TEST(TimerTest, SetUpThrowsIfDurationZero) {
    Timer t;
    t.setDuration(0);

    EXPECT_THROW(t.setUpTimer(), std::invalid_argument);
}


TEST(TimerTest, GetTickDecreasesRemainingTime) {
    Timer t;
    t.setDuration(3);
    t.setUpTimer();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    t.getTick();

    EXPECT_LE(t.getRemainingTime(), 2);
}





TEST(TimerTest, ResumeTimerRestartsCountdown) {
    Timer t;
    t.setDuration(4);
    t.setUpTimer();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    t.stopTimer();
    int pausedAt = t.getRemainingTime();

    t.resumeTimer();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    t.getTick();

    EXPECT_LT(t.getRemainingTime(), pausedAt);
}


TEST(TimerTest, StopTimerPausesCorrectly) {
    Timer t; t.setDuration(5);
    t.setUpTimer();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    t.stopTimer();
    int afterStop = t.getRemainingTime();
    std::this_thread::sleep_for(std::chrono::seconds(1))
    ; t.getTick(); EXPECT_EQ(t.getRemainingTime(), afterStop);}

TEST(TimerTest, RestartTimerResetsCorrectly) {
    Timer t;
    t.setDuration(10);
    t.setUpTimer();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    t.stopTimer();

    t.restartTimer();

    EXPECT_EQ(t.getRemainingTime(), 10);
    EXPECT_FALSE(t.isRunning());
}

TEST(TimerTest, RestartThrowsIfRunning) {
    Timer t;
    t.setDuration(10);
    t.setUpTimer();

    EXPECT_THROW(t.restartTimer(), std::invalid_argument);
}



