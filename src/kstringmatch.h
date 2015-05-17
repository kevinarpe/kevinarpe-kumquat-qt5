//
// Created by kca on 5/17/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KSTRINGMATCH_H
#define KEVINARPE_KUMQUAT_QT5_KSTRINGMATCH_H

#include <vector>

namespace kumquat {

class KStringMatch /*final*/ {

public:
    KStringMatch(const std::size_t index, const std::size_t count)
        : _index(index), _count(count)
    { }

    std::size_t
    index()
    const {
        return _index;
    }

    std::size_t
    count()
    const {
        return _count;
    }

private:
    std::size_t _index;
    std::size_t _count;
};

typedef std::vector<KStringMatch> KStringMatchVec;

inline
bool
operator<(const KStringMatch& a, const KStringMatch& b) {
    if (a.index() < b.index()) {
        return true;
    }
    const bool x = (a.count() < b.count());
    return x;
}

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KSTRINGMATCH_H
