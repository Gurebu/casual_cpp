//
// Created by Gurebu on 05.09.2016.
//

#ifndef CASUAL_CPP_FALSE_SHARING_H
#define CASUAL_CPP_FALSE_SHARING_H

#include <iostream>
#include "base/ThreadingTest.h"

namespace {
    template <std::size_t padsize>
    struct shared_data {
        unsigned x = 0;
        unsigned char padding[padsize];
        unsigned y = 0;

        std::function<void(unsigned)> make_test(unsigned reps) {
            return [this, reps] (unsigned tid) {
                if (tid == 1) {
                    auto r = reps;
                    while (--r) {
                        x += r;
                    }
                } else {
                    auto r = reps;
                    while (--r) {
                        y += r;
                    }
                }
            };
        }
    };
}

void false_sharing() {
    { // Padded data in stuctures
        shared_data<0> pad_0;
        shared_data<16> pad_16;
        shared_data<64> pad_64;
        shared_data<256> pad_256;

        constexpr unsigned reps = 1000000000;

        auto test1 = ThreadingTest(pad_0.make_test(reps)); // ~ 6.6 secs
        auto test2 = ThreadingTest(pad_16.make_test(reps)); // ~ 6.6 secs
        auto test3 = ThreadingTest(pad_64.make_test(reps)); // ~ 2.2 secs
        auto test4 = ThreadingTest(pad_256.make_test(reps)); // ~ 2.7 secs

        std::cout << "padding = 0: " << test1.run(2) << std::endl;
        std::cout << "padding = 16: " << test2.run(2) << std::endl;
        std::cout << "padding = 64: " << test3.run(2) << std::endl;
        std::cout << "padding = 256: " << test4.run(2) << std::endl;
    }

    std::cout << std::endl;

    { // index % n_threads parallelization (hint! not the best idea)
        constexpr unsigned array_size = 1024;
        constexpr unsigned thread_count = 4;
        constexpr unsigned index_count = array_size / thread_count;
        constexpr unsigned reps = 4000000000;

        unsigned arr[array_size], init = 0;
        for (auto it = std::begin(arr); it != std::end(arr); ++it) {
            *it = init++;
        }

        auto ptest1 = ThreadingTest([&](unsigned tid) {
            // Split the data into even chunks
            unsigned indices[index_count];
            for (unsigned i = 0; i < index_count; ++i) {
                indices[i] = i + tid * index_count;
            }

            unsigned index = 0;
            for (unsigned i = 0; i < reps; ++i) {
                index = (index + 1) % index_count;
                ++arr[indices[index]];
            }
        });

        auto ptest2 = ThreadingTest([&](unsigned tid) {
            // Split the data into even chunks
            unsigned indices[index_count];
            for (unsigned i = 0; i < index_count; ++i) {
                indices[i] = tid + i * thread_count;
            }

            unsigned index = 0;
            for (unsigned i = 0; i < reps; ++i) {
                index = (index + 1) % index_count;
                ++arr[indices[index]];
            }
        });

        std::cout << "even split: " << ptest1.run(thread_count) << std::endl;
        std::cout << "every n'th: " << ptest2.run(thread_count) << std::endl;
    }
}

#endif //CASUAL_CPP_FALSE_SHARING_H
