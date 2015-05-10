//
// Created by kca on 5/3/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KABSTRACTMODELFILTER_H
#define KEVINARPE_KUMQUAT_QT5_KABSTRACTMODELFILTER_H

#include "knamespace"
#include "KQSortFilterProxyModel"
#include <QModelIndex>
#include <vector>

namespace kumquat {

class KIModelFilter {

public:
    KIModelFilter()
    { }

    virtual
    ~KIModelFilter()
    { }

    virtual Dimensions
    dimensions()
    const = 0;

    virtual bool
    filterAcceptsRow(const KQSortFilterProxyModel& proxyModel,
                     const int sourceRowIndex,
                     const QModelIndex& sourceParent)
    const = 0;

    virtual bool
    filterAcceptsColumn(const KQSortFilterProxyModel& proxyModel,
                        const int sourceColumnIndex,
                        const QModelIndex& sourceParent)
    const = 0;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KMODELFILTER_H
