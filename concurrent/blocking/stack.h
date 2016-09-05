//
// Created by Gurebu on 05.09.2016.
//

#ifndef CASUAL_CPP_STACK_H
#define CASUAL_CPP_STACK_H

#include <stack>
#include <mutex>

namespace tsafe_blocking {
    template <typename Value>
    class stack {
        std::stack<Value> _impl;
        std::mutex _mut;
    public:
        void push(Value &&val) {
            std::lock_guard<std::mutex> guard(_mut);
            _impl.push(std::forward(val));
        }

        Value pop() {
            std::lock_guard<std::mutex> guard(_mut);
            auto val = std::move(_impl.top());
            _impl.pop();
            return val;
        }
    };
}

#endif //CASUAL_CPP_STACK_H
