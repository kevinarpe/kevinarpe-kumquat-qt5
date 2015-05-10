//
// Created by kca on 5/3/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KREGEXMODELFILTER_H
#define KEVINARPE_KUMQUAT_QT5_KREGEXMODELFILTER_H

#include "KIModelFilter"
#include <QRegExp>

namespace kumquat {

class KRegexModelFilter
    : public KIModelFilter {

private:
    typedef KIModelFilter Base;

public:
    typedef std::vector<QRegExp> RegexVec;

    KRegexModelFilter(const Dimensions dim, const RegexVec& regexVec);

    virtual
    ~KRegexModelFilter()
    { }

    virtual Dimensions
    dimensions()
    const override {
        return _dimensions;
    }

    virtual bool
    filterAcceptsRow(const KQSortFilterProxyModel& proxyModel,
                     const int sourceRowIndex,
                     const QModelIndex& sourceParent)
    const override;

    virtual bool
    filterAcceptsColumn(const KQSortFilterProxyModel& proxyModel,
                        const int sourceColumnIndex,
                        const QModelIndex& sourceParent)
    const override;

private:
    const Dimensions _dimensions;
    const RegexVec _regexVec;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KREGEXMODELFILTER_H
