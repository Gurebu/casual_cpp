//
// Created by Gurebu on 05.09.2016.
//

#ifndef CONCURRENCY_FUNCTIONAL_H
#define CONCURRENCY_FUNCTIONAL_H

#include <algorithm>
#include <type_traits>
#include <iterator>

template <template <typename, typename...> class Container, typename InputVal, typename Func>
auto fmap(const Container<InputVal> &cont, Func f) -> Container<typename std::result_of<Func(InputVal)>::type> {
    Container<typename std::result_of<Func(InputVal)>::type> result;
    std::transform(cont.cbegin(), cont.cend(), std::inserter(result, result.end()), f);
    return result;
}

template <template <typename, typename...> class Container, typename Val, typename Func>
auto freduce(const Container<Val> &cont, Func f, Val accum=Val()) -> Val {
    for (const auto &item : cont) {
        accum = f(accum, item);
    }
    return accum;
}

#endif //CONCURRENCY_FUNCTIONAL_H
