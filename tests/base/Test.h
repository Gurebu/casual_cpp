//
// Created by Gurebu on 05.09.2016.
//

#ifndef CASUAL_CPP_TEST_H
#define CASUAL_CPP_TEST_H

#include <functional>

class Test {
    std::function<void(void)> body;
public:
    Test(std::function<void(void)> _body): body(_body) {}
    double run();
};

#endif //CASUAL_CPP_TEST_H
