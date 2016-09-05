//
// Created by Gurebu on 05.09.2016.
//

#ifndef CASUAL_CPP_THREADINGTEST_H
#define CASUAL_CPP_THREADINGTEST_H

#include <functional>

class ThreadingTest {
    std::function<void(unsigned)> body;
public:
    ThreadingTest(std::function<void(unsigned)> _body): body(_body) {}
    double run(unsigned n_threads);
};

#endif //CASUAL_CPP_THREADINGTEST_H
