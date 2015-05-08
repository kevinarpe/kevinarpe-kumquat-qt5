//
// Created by kca on 5/6/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KFUNCTIONAL_H
#define KEVINARPE_KUMQUAT_QT5_KFUNCTIONAL_H

#include <functional>

namespace std {

// Ref: http://stackoverflow.com/a/21029900/257299
template<class TEnum>
class hash {

private:
    using sfinae = typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type;

public:
    size_t
    operator()(const TEnum& value)
    const {
        const size_t x = std::hash<typename std::underlying_type<TEnum>::type>()(value);
        return x;
    }
};

}

#endif //KEVINARPE_KUMQUAT_QT5_KFUNCTIONAL_H
