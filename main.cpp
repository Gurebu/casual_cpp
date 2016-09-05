

// TODO simultaneous wakeup

//int main() {
//    test_ordering(std::memory_order_relaxed, std::memory_order_relaxed);
//    for (int i = 0; i < 10; ++i) {
//        std::cout << i << " : "
//                  << number_of_strings(i) << ", "
//                  << number_of_strings2(i) << ", "
//                  << number_of_strings3(i) << std::endl;
//    }

//    constexpr unsigned int array_size = 1024;
//    constexpr unsigned int thread_count = 4;
//    constexpr unsigned int index_count = array_size / thread_count;
//    constexpr bool cache_friendly = true;
//
//    unsigned int arr[array_size], init = 0, tries = 4000000000;
//    for (auto it = std::begin(arr); it != std::end(arr); ++it) {
//        *it = init++;
//    }
//
//    unsigned int fin_counter = 0;
//    std::mutex cout_mutex;
//    std::chrono::system_clock::time_point tstamp;
//
//    std::vector<std::thread> pool;
//    for (int tid = 0; tid < thread_count; ++tid) {
//        std::thread t([&](unsigned int n) {
//            unsigned int indices[index_count];
//
//            if (cache_friendly) {
//                // Split the data into even chunks
//                for (unsigned int i = 0; i < index_count; ++i) {
//                    indices[i] = i + n * index_count;
//                }
//            } else {
//                // Take every n'th value for this thread
//                for (unsigned int i = 0; i < index_count; ++i) {
//                    indices[i] = n + i * thread_count;
//                }
//            }
//
//            // Work code
//
//            unsigned int index = 0;
//            for (unsigned int i = 0; i < tries; ++i) {
//                index = (index + 1) % index_count;
//                ++arr[indices[index]];
//            }
//
//            // Thread finish
//
//            std::lock_guard<std::mutex> lk(cout_mutex);
//            std::cout << "Thread " << n << " finished" << std::endl;
//            if (++fin_counter == thread_count) {
//                auto duration = std::chrono::system_clock::now() - tstamp;
//                std::cout << "Finished all! Took time: " << duration.count() / 1e9 << std::endl;
//            }
//        }, tid);
//
//        pool.push_back(std::move(t));
//    }
//
//    tstamp = std::chrono::system_clock::now();
//
//    for (auto &t : pool) {
//        t.join();
//    }



//    return 0;
//}

// TODO namespaces

#include "tests/cache_thrashing.h"

int main() {
    cache_thrashing();

    return 0;
}

