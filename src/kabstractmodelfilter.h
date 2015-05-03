//
// Created by kca on 5/3/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KABSTRACTMODELFILTER_H
#define KEVINARPE_KUMQUAT_QT5_KABSTRACTMODELFILTER_H

#include "ksortfilterproxymodel.h"
#include <QModelIndex>
#include <vector>

namespace kumquat {

class KAbstractModelFilter {

public:
    KAbstractModelFilter()
    { }

    virtual ~KAbstractModelFilter()
    { }

    virtual bool
    filterAcceptsRow(const KSortFilterProxyModel& proxyModel,
                     const int sourceRowIndex,
                     const QModelIndex& sourceParent)
    const = 0;

    virtual bool
    filterAcceptsColumn(const KSortFilterProxyModel& proxyModel,
                        const int sourceColumnIndex,
                        const QModelIndex& sourceParent)
    const = 0;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KMODELFILTER_H
