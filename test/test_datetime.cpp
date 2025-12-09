//
// Created by depa on 09.12.25.
//
#include "Datetime.h"
#include <gtest/gtest.h>

#include <regex>

TEST(DateTimeTest, UpdateCurrentReturnsNonEmptyString) {
    DateTime dt;
    std::string result = dt.updateCurrent();
    EXPECT_FALSE(result.empty());
}

TEST(DateTimeTest, UpdateCurrentFormatsChangeWithViewmode) {
    DateTime dt;

    // LONG_FORMAT
    dt.setViewmode(); // LONG -> MEDIUM
    std::string medium = dt.updateCurrent();
    EXPECT_FALSE(medium.empty());

    dt.setViewmode(); // MEDIUM -> SHORT
    std::string shortFmt = dt.updateCurrent();
    EXPECT_FALSE(shortFmt.empty());

    dt.setViewmode(); // SHORT -> LONG
    std::string longFmt = dt.updateCurrent();
    EXPECT_FALSE(longFmt.empty());


    EXPECT_NE(medium.length(), shortFmt.length());
    EXPECT_NE(longFmt.length(), shortFmt.length());
}