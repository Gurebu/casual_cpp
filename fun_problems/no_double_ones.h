//
// Created by Gurebu on 04.09.2016.
//

#ifndef CASUAL_CPP_NO_DOUBLE_ONES_H
#define CASUAL_CPP_NO_DOUBLE_ONES_H

#include <deque>

/*
 * function number_of_strings(int N)
 * must return the number of binary strings of length N
 * that contain no adjacent 1's
 * i.e assert(number_of_strings(3) == 5) etc.
 *
 * assume:
 *      p(n) - number of strings containing no "11" sequence
 *      q(n) - number of strings that have a "11" sequence
 *      p*(n) - number of strings that don't have "11" in them and begin with a 1
 *
 * then for n > 3:
 *      p(n) = 2^n - q(n)
 *      q(n) = 2 * q(n - 1) + p*(n - 1)
 *      p*(n) = p(n - 2)
 *
 * simplified:
 *      p(n) = 2 * p(n - 1) - p(n - 3)
 */

int number_of_strings(int N) {
    if (N == 0) return 0;

    std::deque<int> mem = { 2, 3, 5 };
    if (N < 4) return mem[N - 1];

    for (int i = 4; i <= N; ++i) {
        mem.push_back(2 * mem.back() - mem.front());
        mem.pop_front();
    }

    return mem.back();
}

#endif //CASUAL_CPP_NO_DOUBLE_ONES_H
