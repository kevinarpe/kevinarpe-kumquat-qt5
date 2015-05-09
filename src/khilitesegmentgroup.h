//
// Created by kca on 5/9/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KHILITESEGMENTGROUP_H
#define KEVINARPE_KUMQUAT_QT5_KHILITESEGMENTGROUP_H

#include "KHiliteSegment"
#include "KQAbstractItemModel"
#include <unordered_map>

namespace kumquat {

typedef std::vector<KHiliteSegment> KHiliteSegmentVec;

// TODO: Convert to Abstract
// Then create KHiliteSegmentGroup and KThreadSafeHiliteSegmentGroup
class KHiliteSegmentGroup {

public:
    KHiliteSegmentGroup()
    { }

    KHiliteSegmentVec&
    operator[](const QModelIndex& modelIndex);

    const KHiliteSegmentVec&
    operator[](const QModelIndex& modelIndex)
    const;

    void
    clear();

    bool
    erase(const QModelIndex& modelIndex);

private:
    static const KHiliteSegmentVec EMPTY_VEC;

    typedef std::unordered_map<QModelIndex, KHiliteSegmentVec> QModelIndex_To_KHiliteSegmentVec_Map;
    QModelIndex_To_KHiliteSegmentVec_Map _map;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KHILITESEGMENTGROUP_H
