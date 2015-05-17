//
// Created by kca on 5/16/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KALGORITHM_H
#define KEVINARPE_KUMQUAT_QT5_KALGORITHM_H

#include <algorithm>

namespace kumquat {

template<typename ForwardIter, typename TValue>
inline ForwardIter
kbinary_search(ForwardIter first, ForwardIter last, const TValue& value) {
    const auto& compareFunc = std::less<TValue>();
    const ForwardIter x = kbinary_search(first, last, value, compareFunc);
    return x;
}

// Ref: http://stackoverflow.com/a/446327/257299
template<typename ForwardIter, typename TValue, typename CompareFunc>
ForwardIter
kbinary_search(ForwardIter first, ForwardIter last, const TValue& value, CompareFunc compareFunc) {
    const ForwardIter iter = std::lower_bound(first, last, value, compareFunc);
    if (iter == last || compareFunc(value, *iter)) {
        return last;
    }
    else {
        return iter;
    }
}

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KALGORITHM_H
