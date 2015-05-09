//
// Created by kca on 5/3/15.
//

#include "KRegexModelFilter"

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
    Q_ASSERT(modelIndex.isValid());
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

const KRegexModelFilter::RegexVec&
_checkRegexVec(const KRegexModelFilter::RegexVec& regexVec) {
    if (regexVec.empty()) {
        throw std::invalid_argument("Argument 'regexVec' is empty");
    }

    const std::size_t size = regexVec.size();
    for (std::size_t i = 0 ; i < size ; ++i) {
        const QRegExp& regex = regexVec[i];
        if (regex.isEmpty()) {
            throw std::invalid_argument("Argument 'regexVec[" + std::to_string(i) + "]' is an empty regex");
        }
        else if (!regex.isValid()) {
            throw std::invalid_argument("Argument 'regexVec[" + std::to_string(i) + "]' is an invalid regex");
        }
    }

    return regexVec;
}

}  // namespace (unnamed)

// public
KRegexModelFilter::
KRegexModelFilter(const Dimensions dim, const RegexVec& regexVec)
    : Base(),
      _dimensions(dim),
      _regexVec(_checkRegexVec(regexVec))
{ }

// public virtual
bool
KRegexModelFilter::
filterAcceptsRow(const KQSortFilterProxyModel& proxyModel,
                 const int sourceRowIndex,
                 const QModelIndex& sourceParent)
const /*override*/ {
    if (!(_dimensions & Dimension::Row)) {
        return true;
    }
    const QAbstractItemModel& model = *(proxyModel.sourceModel());
    const int columnCount = model.columnCount(sourceParent);
    for (int columnIndex = 0; columnIndex < columnCount; ++columnIndex) {
        const QString& stringValue = _getStringValue(model, sourceRowIndex, columnIndex, sourceParent);
        if (!_hasMatch(_regexVec, stringValue)) {
            return false;
        }
    }
    return true;
}

// public virtual
bool
KRegexModelFilter::
filterAcceptsColumn(const KQSortFilterProxyModel& proxyModel,
                    const int sourceColumnIndex,
                    const QModelIndex& sourceParent)
const /*override*/ {
    if (!(_dimensions & Dimension::Column)) {
        return true;
    }
    const QAbstractItemModel& model = *(proxyModel.sourceModel());
    const int rowCount = model.rowCount(sourceParent);
    for (int rowIndex = 0; rowIndex < rowCount; ++rowIndex) {
        const QString& stringValue = _getStringValue(model, rowIndex, sourceColumnIndex, sourceParent);
        if (!_hasMatch(_regexVec, stringValue)) {
            return false;
        }
    }
    return true;
}

}  // namespace kumquat
