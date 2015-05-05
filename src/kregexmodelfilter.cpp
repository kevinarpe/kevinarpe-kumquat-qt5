//
// Created by kca on 5/3/15.
//

#include "kregexmodelfilter.h"
#include <cassert>

namespace kumquat {

// Like 'static' for C functions (not exported: 'extern')
namespace {

// TODO: Ask Stack about 'QString' vs 'const QString&'
QString
_getStringValue(const QAbstractItemModel& model,
                const int rowIndex,
                const int columnIndex,
                const QModelIndex& sourceParent) {
    const QModelIndex& modelIndex = model.index(rowIndex, columnIndex, sourceParent);
    assert(modelIndex.isValid());
    // TODO: Qt::DisplayRole is default value.  Do we need to customise?  Not sure; but gut says "no".
    const QVariant& value = model.data(modelIndex, Qt::DisplayRole);
    // TODO: Ask stackoverflow if diff between 'const QString' and 'const QString&'
    const QString& x = value.toString();
    return x;
}

bool
_hasMatch(const KRegexModelFilter::RegexVec& regexVec, const QString& s) {
    for (const QRegExp& regex : regexVec) {
        const int matchIndex = regex.indexIn(s);
        if (-1 == matchIndex) {
            return false;
        }
    }
    return true;
}

}  // namespace (unnamed)

// public virtual
bool
KRegexModelFilter::filterAcceptsRow(const KSortFilterProxyModel& proxyModel,
                                    const int sourceRowIndex,
                                    const QModelIndex& sourceParent)
const /*override*/ {
    const QAbstractItemModel& model = *(proxyModel.sourceModel());
    const int columnCount = model.columnCount(sourceParent);
    for (int columnIndex = 0 ; columnIndex < columnCount ; ++columnIndex) {
        const QString& stringValue = _getStringValue(model, sourceRowIndex, columnIndex, sourceParent);
        if (!_hasMatch(_regexVec, stringValue)) {
            return false;
        }
    }
    return true;
}

// public virtual
bool
KRegexModelFilter::filterAcceptsColumn(const KSortFilterProxyModel& proxyModel,
                                       const int sourceColumnIndex,
                                       const QModelIndex& sourceParent)
const {
    const QAbstractItemModel& model = *(proxyModel.sourceModel());
    const int rowCount = model.rowCount(sourceParent);
    for (int rowIndex = 0 ; rowIndex < rowCount; ++rowIndex) {
        const QString& stringValue = _getStringValue(model, rowIndex, sourceColumnIndex, sourceParent);
        if (!_hasMatch(_regexVec, stringValue)) {
            return false;
        }
    }
    return true;
}

}  // namespace kumquat
