//
// Created by kca on 5/3/15.
//

#include "kregexmodelfilter.h"
#include <cassert>

namespace kumquat {

// public
bool
KRegexModelFilter::filterAcceptsRow(const KSortFilterProxyModel& proxyModel,
                                    const int sourceRowIndex,
                                    const QModelIndex& sourceParent)
const {
    // TODO: Impl filterAcceptsColumn() using a lambda + generic helper method
    // Only getStringValue() needs to be lambda'd.
    const QAbstractItemModel& model = *(proxyModel.sourceModel());
    const int columnCount = model.columnCount(sourceParent);
    for (int columnIndex = 0 ; columnIndex < columnCount ; ++columnIndex) {
        const QString& stringValue = getStringValue(model, sourceRowIndex, columnIndex, sourceParent);
        if (!hasMatch(stringValue)) {
            return false;
        }
    }
    return true;
}

// protected
QString
KRegexModelFilter::getStringValue(const QAbstractItemModel& model,
                                  const int rowIndex,
                                  const int columnIndex,
                                  const QModelIndex& sourceParent)
const {
    const QModelIndex& modelIndex = model.index(rowIndex, columnIndex, sourceParent);
    assert(modelIndex.isValid());
    // TODO: Qt::DisplayRole is default value.  Do we need to customise?  Not sure; but gut says "no".
    const QVariant& value = model.data(modelIndex, Qt::DisplayRole);
    // TODO: Ask stackoverflow if diff between 'const QString' and 'const QString&'
    const QString& x = value.toString();
    return x;
}

// protected
bool
KRegexModelFilter::hasMatch(const QString& s)
const {
    for (const QRegExp& regex : _regexVec) {
        const int matchIndex = regex.indexIn(s);
        if (-1 == matchIndex) {
            return false;
        }
    }
    return true;
}

// public
bool
KRegexModelFilter::filterAcceptsColumn(const KSortFilterProxyModel& proxyModel,
                                       const int sourceColumnIndex,
                                       const QModelIndex& sourceParent)
const {
    return true;
}

}  // namespace kumquat
