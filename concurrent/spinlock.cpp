//
// Created by Gurebu on 05.09.2016.
//

#include "spinlock.h"

inline void spinlock::lock() {
    while (_f.test_and_set(std::memory_order_acquire));
}

inline void spinlock::unlock() {
    _f.clear(std::memory_order_release);
}

inline bool spinlock::try_lock() {
    return !_f.test_and_set(std::memory_order_acquire);
}
