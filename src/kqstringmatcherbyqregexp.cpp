//
// Created by kca on 5/17/15.
//

#include "KQStringMatcherByQRegExp"

namespace kumquat {

// public
KQStringMatcherByQRegExp::
KQStringMatcherByQRegExp(std::initializer_list<QRegExp> list)
    : _regExpVec(list)
{
    assert(!_regExpVec.empty() && "List is empty");
}

// public
bool
KQStringMatcherByQRegExp::
match(const QString& s, KStringMatchVec* const v)
const {
    v->clear();
    for (const QRegExp& r : _regExpVec) {
        int index = 0;
        while (-1 != (index = r.indexIn(s, index))) {
            const int count = r.matchedLength();
            v->emplace_back(index, count);
        }
    }
    std::sort(v->begin(), v->end());
    const bool x = !(v->empty());
    return x;
}

}  // namespace kumquat
