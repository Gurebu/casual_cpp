//
// Created by Gurebu on 05.09.2016.
//

#include <chrono>
#include "Test.h"

double Test::run() {
    auto tstamp = std::chrono::system_clock::now();
    body();
    auto duration = std::chrono::system_clock::now() - tstamp;
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() / 1e3;
}

