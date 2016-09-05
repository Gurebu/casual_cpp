//
// Created by Gurebu on 05.09.2016.
//

#ifndef CASUAL_CPP_CACHE_THRASHING_H
#define CASUAL_CPP_CACHE_THRASHING_H

// TODO test unique_ptrs

#include <algorithm>
#include <iostream>
#include "base/Test.h"

void cache_thrashing() {
    constexpr unsigned size = 1024;
    constexpr unsigned reps = 1000;

    // random shuffle of order of allocation
    unsigned indices[size];
    for (unsigned i = 0; i < size; ++i) {
        indices[i] = i;
    }
    std::random_shuffle(std::begin(indices), std::end(indices));

    // allocate an array of pointers to sequential memory
    unsigned **data = new unsigned *[size];
    for (auto i : indices) {
        data[i] = new unsigned[size];
    }

    // populate the array
    for (unsigned i = 0; i < size; ++i) {
        for (unsigned j = 0; j < size; ++j) {
            data[i][j] = i + j;
        }
    }

    // "natural" order
    auto test1 = Test([&data, size, reps](){
        unsigned sum = 0;

        for (unsigned r = 1; r <= reps; ++r) {
            for (unsigned i = 0; i < size; ++i) {
                for (unsigned j = 0; j < size; ++j) {
                    sum += r * data[i][j];
                }
            }
        }

        // "Use" the result to avoid optimization
        std::cout << sum << " ";
    });

    for (int k = 0; k < 10; ++k) {
        std::cout << "Test1 is run in: " << test1.run() << " seconds" << std::endl; // ~ 2.3 seconds
    }

    // "cache-oblivious" order
    auto test2 = Test([&data, size, reps](){
        unsigned sum = 0;

        for (unsigned r = 1; r <= reps; ++r) {
            for (unsigned i = 0; i < size; ++i) {
                for (unsigned j = 0; j < size; ++j) {
                    sum += r * data[j][i];
                }
            }
        }

        // "Use" the result to avoid optimization
        std::cout << sum << " ";
    });

    std::cout << std::endl;

    for (int k = 0; k < 10; ++k) {
        std::cout << "Test2 is run in: " << test2.run() << " seconds" << std::endl; // ~ 2.7 seconds
    }

    for (unsigned i = 0; i < size; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

#endif //CASUAL_CPP_CACHE_THRASHING_H
