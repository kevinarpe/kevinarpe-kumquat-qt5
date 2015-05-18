//
// Created by kca on 5/6/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KFUNCTIONAL_H
#define KEVINARPE_KUMQUAT_QT5_KFUNCTIONAL_H

#include <functional>
#include <utility>

namespace std {

// Specialisation of std::hash for all unscoped enums.
// Ref: http://stackoverflow.com/a/21029900/257299
template<typename TEnum>
class hash {

private:
    using sfinae = typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type;

public:
    size_t
    operator()(const TEnum& value)
    const {
//        typedef typename std::underlying_type<TEnum>::type type;
//        const std::hash<type> h = std::hash<type>();
//        const size_t x = h(value);
        const size_t value2 = static_cast<size_t>(value);
        const std::hash<size_t> h = std::hash<size_t>();
        const size_t x = h(value2);
        return x;
    }
};

}  // namespace std

namespace kumquat {

// Ref: http://stackoverflow.com/a/20602159/257299
// Ref: http://hg.openjdk.java.net/jdk8/jdk8/jdk/file/tip/src/share/classes/java/util/Arrays.java
template<typename T1, typename T2>
struct pairhash {

public:
    std::size_t
    operator()(const std::pair<T1, T2>& value) {
        const std::hash<std::error_code>& h1 = std::hash<T1>();
        const std::size_t x1 = h1(value.first);

        const std::hash<std::error_code>& h2 = std::hash<T2>();
        const std::size_t x2 = h2(value.first);

        const std::size_t x = (x1 * 31) + x2;
        return x;
    }

};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KFUNCTIONAL_H
