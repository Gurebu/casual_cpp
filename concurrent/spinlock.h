//
// Created by Gurebu on 05.09.2016.
//

#ifndef CONCURRENCY_SPINLOCK_H
#define CONCURRENCY_SPINLOCK_H

#include <atomic>

class spinlock {
    std::atomic_flag _f;
public:
    inline void lock();
    inline void unlock();
    inline bool try_lock();
};


#endif //CONCURRENCY_SPINLOCK_H
