//
// Created by Gurebu on 05.09.2016.
//

#include <atomic>
#include <chrono>
#include <vector>
#include <thread>
#include <condition_variable>
#include "ThreadingTest.h"

double ThreadingTest::run(unsigned n_threads) {
    std::chrono::system_clock::time_point tstart, tend;
    std::atomic<unsigned> prepare_ctr(n_threads), finish_ctr(n_threads);

    std::mutex m;
    std::condition_variable cvar;

    std::vector<std::thread> pool;
    for (unsigned tid = 0; tid < n_threads; ++tid) {
        pool.push_back(std::thread([&, tid]() {
            if (--prepare_ctr == 0) {
                tstart = std::chrono::system_clock::now();
                cvar.notify_all();
            } else {
                std::unique_lock<std::mutex> lk(m);
                cvar.wait(lk);
            }

            body(tid);

            if (--finish_ctr == 0) {
                tend = std::chrono::system_clock::now();
            }
        }));
    }

    for (auto &t : pool) t.join();
    return (tend - tstart).count() / 1e9;
}