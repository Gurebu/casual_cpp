//
// Created by Gurebu on 01.09.2016.
//

#ifndef CONCURRENCY_MSICACHE_H
#define CONCURRENCY_MSICACHE_H

#include <array>
#include <vector>
#include <atomic>

template <typename word_type, std::size_t cache_size>
class MsiCache {
public:
    enum class word_status {
        Modified,
        Shared,
        Invalid,
    };
private:
    class cache_word {
        std::atomic<word_type> _word;
        word_status _status;
    };

    std::vector<std::atomic<word_type>>& _mem;
    std::array<std::atomic<word_type>, cache_size> _cache;


};




#endif //CONCURRENCY_MSICACHE_H
