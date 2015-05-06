//
// Created by kca on 5/3/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KREGEXMODELFILTER_H
#define KEVINARPE_KUMQUAT_QT5_KREGEXMODELFILTER_H

#include "kabstractmodelfilter.h"
#include <QRegExp>

namespace kumquat {

class KRegexModelFilter : public KAbstractModelFilter {

private:
    typedef KAbstractModelFilter Base;

public:
    typedef std::vector<QRegExp> RegexVec;

    KRegexModelFilter(const RegexVec& regexVec);

    virtual
    ~KRegexModelFilter()
    { }

    virtual bool
    filterAcceptsRow(const KSortFilterProxyModel& proxyModel,
                     const int sourceRowIndex,
                     const QModelIndex& sourceParent)
    const override;

    virtual bool
    filterAcceptsColumn(const KSortFilterProxyModel& proxyModel,
                        const int sourceColumnIndex,
                        const QModelIndex& sourceParent)
    const override;

private:
    const RegexVec _regexVec;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KREGEXMODELFILTER_H
