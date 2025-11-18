//
// Created by depa on 18.11.25.
//

#include "Datatime.h"

std::string DateTime::updateCurrent() const {
    const auto now = std::chrono::system_clock::now();

    // Get the current time zone
    const std::chrono::zoned_time local_time{std::chrono::current_zone(), now};
    const auto today = floor<std::chrono::days>(local_time.get_local_time());

    const auto ymd = std::chrono::year_month_day{today};
    auto time = std::chrono::hh_mm_ss{duration_cast<std::chrono::seconds>(local_time.get_local_time() - today)};

    switch (mode) {
        case LONG_FORMAT:
            return (std::format("{:%B %d %Y}", ymd) + "  " + std::format("{:%H:%M:%S}", time));
        case MEDIUM_FORMAT:
            return (std::format("{:%b %d %Y}", ymd) + "  " + std::format("{:%H:%M}", time));
        case SHORT_FORMAT:
            return (std::format("{:%F}", ymd) + "  " + std::format("{:%I:%M %p}", time));
    }
}

void DateTime::setViewmode() {
    if (mode == LONG_FORMAT)
        mode = MEDIUM_FORMAT;
    else if (mode == MEDIUM_FORMAT)
        mode = SHORT_FORMAT;
    else
        mode = LONG_FORMAT;
}
