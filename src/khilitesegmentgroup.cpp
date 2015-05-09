//
// Created by kca on 5/9/15.
//

#include "KHiliteSegmentGroup"

namespace kumquat {

/*static*/ const KHiliteSegmentVec KHiliteSegmentGroup::EMPTY_VEC;

KHiliteSegmentVec&
KHiliteSegmentGroup::
operator[](const QModelIndex& modelIndex) {
    KHiliteSegmentVec& x = _map[modelIndex];
    return x;
}

const KHiliteSegmentVec&
KHiliteSegmentGroup::
operator[](const QModelIndex& modelIndex)
const {
    auto iter = _map.find(modelIndex);
    if (iter == _map.end()) {
        return EMPTY_VEC;
    }
    else {
        const KHiliteSegmentVec& x = iter->second;
        return x;
    }
}

void
KHiliteSegmentGroup::
clear() {
    _map.clear();
}

bool
KHiliteSegmentGroup::
erase(const QModelIndex& modelIndex) {
    const std::size_t result = _map.erase(modelIndex);
    const bool x = (0 != result);
    return x;
}

}  // namespace kumquat
