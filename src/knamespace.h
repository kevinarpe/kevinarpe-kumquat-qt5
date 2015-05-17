//
// Created by kca on 5/9/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KNAMESPACE_H
#define KEVINARPE_KUMQUAT_QT5_KNAMESPACE_H

#include <Qt>

namespace kumquat {

enum /*class*/ Dimension {
    Row    = 0x1,
    Column = 0x2,
};

Q_DECLARE_FLAGS(Dimensions, Dimension)

extern const std::vector<Dimension> DIMENSION_VALUE_VEC;  // { Dimension::Row, Dimension::Column };

}  // namespace kumquat

namespace std {

// Specialisation of std::hash for all unscoped enums.
// Ref: http://stackoverflow.com/a/21029900/257299
template<>
class hash<kumquat::Dimension> {

public:
    size_t
    operator()(const kumquat::Dimension& value)
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

}

#endif //KEVINARPE_KUMQUAT_QT5_KNAMESPACE_H
