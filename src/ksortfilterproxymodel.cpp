//
// Created by kca on 5/3/15.
//

#include "ksortfilterproxymodel.h"
#include "kabstractmodelfilter.h"

namespace kumquat {

// TODO: Allow table to transpose.
// That means we need to support sorting on rows

// b/c sorting is stable, multi-column sorting isn't really necessary.
// Just click the column headers, one by one, to sort by mulitple keys

// Types of KModelFilter
// multi-regexp for all rows/columns
// multi-regexp for specific rows and/or columns

// Option: Hide non-matching rows/column?

// Allow result to by queried from SQLite
// GUI can show a sample query with all column names

// public
KSortFilterProxyModel::KSortFilterProxyModel(QObject* parent /*= nullptr*/)
    : Base(parent)
{ }

// public virtual
KSortFilterProxyModel::~KSortFilterProxyModel()
{ }

// public
void
KSortFilterProxyModel::setModelFilterPtrVec(ModelFilterPtrVec& modelFilterPtrVec) {
    _modelFilterPtrVec = std::move(modelFilterPtrVec);
}

// protected virtual
bool
KSortFilterProxyModel::filterAcceptsRow(const int sourceRowIndex, const QModelIndex& sourceParent)
const /*override*/ {
    for (const ModelFilterPtr& modelFilterPtr : _modelFilterPtrVec) {
        if (!modelFilterPtr->filterAcceptsRow(*this, sourceRowIndex, sourceParent)) {
            return false;
        }
    }
    return true;
}

// protected virtual
bool
KSortFilterProxyModel::filterAcceptsColumn(const int sourceColumnIndex, const QModelIndex& sourceParent)
const /*override*/ {
    for (const ModelFilterPtr& modelFilterPtr : _modelFilterPtrVec) {
        if (!modelFilterPtr->filterAcceptsColumn(*this, sourceColumnIndex, sourceParent)) {
            return false;
        }
    }
    return true;
}

}  // namespace kumquat
