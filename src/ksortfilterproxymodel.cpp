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
void
KSortFilterProxyModel::setModelFilterPtrVec(ModelFilterPtrVec& modelFilterPtrVec) {
    _modelFilterPtrVec = std::move(modelFilterPtrVec);
}

// protected
bool
KSortFilterProxyModel::filterAcceptsRow(int sourceRowIndex, const QModelIndex& sourceParent)
const {
    // TODO: Impl filterAcceptsColumn() with lambda & helper method
    for (const ModelFilterPtr& modelFilterPtr : _modelFilterPtrVec) {
        if (!modelFilterPtr->filterAcceptsRow(*this, sourceRowIndex, sourceParent)) {
            return false;
        }
    }
    return true;
}

// protected
bool
KSortFilterProxyModel::filterAcceptsColumn(int sourceColumnIndex, const QModelIndex& sourceParent)
const {
    return true;
}

}  // namespace kumquat
