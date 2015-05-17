//
// Created by kca on 5/17/15.
//

#include "KProxyDataTable"
#include "KColumnCount"

namespace kumquat {

// public static
template<
    typename TValue,
    typename TDataTable,
    typename TString,
    typename TStringDataTable,
    typename TDimensionCompareFunctor,
    typename TStringMatcher
>
const KFixedSizeMap<Qt::Orientation, Dimension>
KProxyDataTable<TValue, TDataTable, TString, TStringDataTable, TDimensionCompareFunctor, TStringMatcher>::
QT_ORIENTATION_TO_DIMENSION_MAP
    {
        { Qt::Horizontal, Dimension::Row },
        { Qt::Vertical, Dimension::Column },
    };

// public
template<
    typename TValue,
    typename TDataTable,
    typename TString,
    typename TStringDataTable,
    typename TDimensionCompareFunctor,
    typename TStringMatcher
>
std::size_t
KProxyDataTable<TValue, TDataTable, TString, TStringDataTable, TDimensionCompareFunctor, TStringMatcher>::
size(const Dimension d)
const {
    const _IndexVec& v = _dimension_To_SortFilterIndexVec_Map[d];
    const std::size_t x = v.size();
    return x;
}

// private
template<
    typename TValue,
    typename TDataTable,
    typename TString,
    typename TStringDataTable,
    typename TDimensionCompareFunctor,
    typename TStringMatcher
>
std::size_t
KProxyDataTable<TValue, TDataTable, TString, TStringDataTable, TDimensionCompareFunctor, TStringMatcher>::
_adjustIndex(const Dimension d, const std::size_t index)
const {
    const _IndexVec& indexVec = _dimension_To_SortFilterIndexVec_Map[d];
    const std::size_t x = indexVec[index];
    return x;
}

// public
template<
    typename TValue,
    typename TDataTable,
    typename TString,
    typename TStringDataTable,
    typename TDimensionCompareFunctor,
    typename TStringMatcher
>
const TValue&
KProxyDataTable<TValue, TDataTable, TString, TStringDataTable, TDimensionCompareFunctor, TStringMatcher>::
data(const std::size_t rowIndex, const std::size_t columnIndex)
const {
    const std::size_t adjRowIndex = _adjustIndex(Dimension::Row, rowIndex);
    const std::size_t adjColumnIndex = _adjustIndex(Dimension::Column, columnIndex);
    const TValue& x = _dataTablePtr->data(adjRowIndex, adjColumnIndex);
    return x;
}

// public
template<
    typename TValue,
    typename TDataTable,
    typename TString,
    typename TStringDataTable,
    typename TDimensionCompareFunctor,
    typename TStringMatcher
>
const TValue&
KProxyDataTable<TValue, TDataTable, TString, TStringDataTable, TDimensionCompareFunctor, TStringMatcher>::
headerData(const std::size_t index, Qt::Orientation orientation)
const {
    const Dimension d = QT_ORIENTATION_TO_DIMENSION_MAP[orientation];
    const std::size_t adjIndex = _adjustIndex(d, index);
    const TValue& x = _dataTablePtr->headerData(index, orientation);
    return x;
}

// public
template<
    typename TValue,
    typename TDataTable,
    typename TString,
    typename TStringDataTable,
    typename TDimensionCompareFunctor,
    typename TStringMatcher
>
void
KProxyDataTable<TValue, TDataTable, TString, TStringDataTable, TDimensionCompareFunctor, TStringMatcher>::
filter(const Dimensions& dims) {
    if (dims != _filterDimensions) {
        _filterDimensions = dims;

        for (Dimension d : DIMENSION_VALUE_VEC) {
            if (Dimensions(d) & dims) {
                _updateSortFilterIndexMap(d);
            }
        }
    }
}

// public
template<
    typename TValue,
    typename TDataTable,
    typename TString,
    typename TStringDataTable,
    typename TDimensionCompareFunctor,
    typename TStringMatcher
>
typename KProxyDataTable<TValue, TDataTable, TString, TStringDataTable, TDimensionCompareFunctor, TStringMatcher>::MatrixIndex_KStringMatchVec_PairVec
KProxyDataTable<TValue, TDataTable, TString, TStringDataTable, TDimensionCompareFunctor, TStringMatcher>::
search(TStringMatcher m) {
    MatrixIndex_KStringMatchVec_PairVec out;

    _FilterResultVec& filterResultRowVec = _dimension_To_FilterResultVec_Map[Dimension::Row];
    _resetFilterResultVec(filterResultRowVec);

    _FilterResultVec& filterResultColumnVec = _dimension_To_FilterResultVec_Map[Dimension::Column];
    _resetFilterResultVec(filterResultColumnVec);

    KStringMatchVec vec;

    const std::size_t rowCount = _stringDataTable->size(Dimension::Row);
    const std::size_t columnCount = _stringDataTable->size(Dimension::Column);

    for (std::size_t rowIndex = 0 ; rowIndex < rowCount ; ++rowIndex) {

        for (std::size_t columnIndex = 0 ; columnIndex < columnCount ; ++columnIndex) {

            const TString& value = _stringDataTable->data(rowIndex, columnIndex);

            if (m.match(value, &vec)) {
                filterResultRowVec[rowIndex] = _FilterResult::Include;
                filterResultRowVec[columnIndex] = _FilterResult::Include;
                out.emplace_back(KMatrixIndex(rowIndex, columnIndex), vec);
            }
        }
    }
    _updateSortFilterIndexMap(Dimension::Row);
    _updateSortFilterIndexMap(Dimension::Column);

    // Technically, this sorts the pairs by 'first', then 'second'.
    // However, all of the 'first' values are unique so the 'second' is never tested using operator<().
    std::sort(out.begin(), out.end());
    return out;
}

// private
template<
    typename TValue,
    typename TDataTable,
    typename TString,
    typename TStringDataTable,
    typename TDimensionCompareFunctor,
    typename TStringMatcher
>
void
KProxyDataTable<TValue, TDataTable, TString, TStringDataTable, TDimensionCompareFunctor, TStringMatcher>::
_updateSortFilterIndexMap(const Dimension d) {
    _IndexVec& sortFilterIndexVec = _dimension_To_SortFilterIndexVec_Map[d];
    const _IndexVec& sortIndexVec = _dimension_To_SortIndexVec_Map[d];

    if (!(Dimensions(d) & _filterDimensions)) {
        sortFilterIndexVec = sortIndexVec;
        return;
    }

    sortFilterIndexVec.clear();

    typedef typename _IndexVec::const_iterator        const_iterator1;
    typedef typename _FilterResultVec::const_iterator const_iterator2;

    const _FilterResultVec& filterResultVec = _dimension_To_FilterResultVec_Map[d];

    const_iterator1 sortIndexIter = sortIndexVec.begin();
    const const_iterator1 sortIndexEndIter = sortIndexVec.end();

    const_iterator2 filterResultIter = filterResultVec.begin();
    const const_iterator2 filterResultEndIter = filterResultVec.end();

    for (   ; sortIndexEndIter != sortIndexIter && filterResultEndIter != filterResultIter
        ; ++sortIndexIter, ++filterResultIter) {
        if (_FilterResult::Include == *filterResultIter) {
            sortFilterIndexVec.push_back(*sortIndexIter);
        }
    }
}

}  // namespace kumquat

#include <algorithm>

namespace kumquat {

namespace {

template<typename T>
T&
_assert(T& value, const bool predicateResult, const std::string& message) {
    if (!predicateResult) {
        std::cerr << message << std::endl;
        std::abort();
    }
    return value;
}

}  // namespace (unnamed)

// private static
template<
    typename TValue,
    typename TDataTable,
    typename TString,
    typename TStringDataTable,
    typename TDimensionCompareFunctor,
    typename TStringMatcher
>
TStringDataTable
KProxyDataTable<TValue, TDataTable, TString, TStringDataTable, TDimensionCompareFunctor, TStringMatcher>::
_createStringDataTable(const DataTablePtr& dataTablePtr) {

    const std::size_t columnCount = dataTablePtr->size(Dimension::Column);
    TStringDataTable t(KColumnCount(columnCount));

    typedef typename DataTable::const_iterator const_iterator;
    const_iterator dataTableIter = dataTablePtr->begin();
    const const_iterator dataTableIterEnd = dataTablePtr->end();

    QString rowArr[columnCount];
    do {
        for (std::size_t columnIndex = 0; columnIndex < columnCount; ++columnIndex) {
            const TValue& v = *dataTableIter;
            const QString& s = v.toString();
            rowArr[columnIndex] = s;
        }
        t.append(rowArr, rowArr + columnCount);
    }
    while (dataTableIterEnd != dataTableIter);

    return t;
}

// private static
template<
    typename TValue,
    typename TDataTable,
    typename TString,
    typename TStringDataTable,
    typename TDimensionCompareFunctor,
    typename TStringMatcher
>
typename KProxyDataTable<TValue, TDataTable, TString, TStringDataTable, TDimensionCompareFunctor, TStringMatcher>::_IndexVec&
KProxyDataTable<TValue, TDataTable, TString, TStringDataTable, TDimensionCompareFunctor, TStringMatcher>::
_resetIndexVec(_IndexVec& v) {
    // Ref: http://stackoverflow.com/a/11965746/257299
    // Fill from 0 to rowCount-1
    std::iota(v.begin(), v.end(), 0);
    return v;
}

// private static
template<
    typename TValue,
    typename TDataTable,
    typename TString,
    typename TStringDataTable,
    typename TDimensionCompareFunctor,
    typename TStringMatcher
>
typename KProxyDataTable<TValue, TDataTable, TString, TStringDataTable, TDimensionCompareFunctor, TStringMatcher>::_FilterResultVec&
KProxyDataTable<TValue, TDataTable, TString, TStringDataTable, TDimensionCompareFunctor, TStringMatcher>::
_resetFilterResultVec(_FilterResultVec& v) {
    std::fill(v.begin(), v.end(), _FilterResult::Include);
    return v;
}

// public
template<
    typename TValue,
    typename TDataTable,
    typename TString,
    typename TStringDataTable,
    typename TDimensionCompareFunctor,
    typename TStringMatcher
>
KProxyDataTable<TValue, TDataTable, TString, TStringDataTable, TDimensionCompareFunctor, TStringMatcher>::
KProxyDataTable(DataTablePtr dataTablePtr)
    : _dataTablePtr(_assert(_dataTablePtr, nullptr != _dataTablePtr, "Argument '_dataTablePtr' is null")),
      _stringDataTable(_createStringDataTable(dataTablePtr)),
      _dimension_To_SortIndexVec_Map(
          {
              { Dimension::Row, _resetIndexVec(_IndexVec(dataTablePtr->size(Dimension::Row))) },
              { Dimension::Column, _resetIndexVec(_IndexVec(dataTablePtr->size(Dimension::Column))) },
          }),
      _dimension_To_FilterResultVec_Map(
          {
              { Dimension::Row, _FilterResultVec(dataTablePtr->size(Dimension::Row), _FilterResult::Include) },
              { Dimension::Column, _FilterResultVec(dataTablePtr->size(Dimension::Column), _FilterResult::Include) },
          }),
      _dimension_To_SortFilterIndexVec_Map(
          {
              { Dimension::Row, _resetIndexVec(_IndexVec(dataTablePtr->size(Dimension::Row))) },
              { Dimension::Column, _resetIndexVec(_IndexVec(dataTablePtr->size(Dimension::Column))) },
          })
{ }

// public
template<
    typename TValue,
    typename TDataTable,
    typename TString,
    typename TStringDataTable,
    typename TDimensionCompareFunctor,
    typename TStringMatcher
>
void
KProxyDataTable<TValue, TDataTable, TString, TStringDataTable, TDimensionCompareFunctor, TStringMatcher>::
sort(TDimensionCompareFunctor fn) {
    const Dimension d = fn.dimension();
    _IndexVec& indexVec = _dimension_To_SortIndexVec_Map.at(d);
    _resetIndexVec(indexVec);

    std::sort(indexVec.begin(),
              indexVec.end(),
        // Ref: https://software.intel.com/sites/products/documentation/doclib/iss/2013/compiler/cpp-lin/GUID-835983D0-9779-422E-B339-0205358CAACC.htm
        // [&] capture all necessary variables (compareFunctor) by reference.
              [&](const std::size_t rowIndexA, const std::size_t rowIndexB) -> bool {
                  // Be careful: Might be slow to add extra function call.
                  // Trade-off: I don't like having a big, messy lambda.
                  // But, probably the compiler optimises away.
                  const bool x = fn(*this, rowIndexA, rowIndexB);
                  return x;
              });
    _updateSortFilterIndexMap(d);
}

// public
template<
    typename TValue,
    typename TDataTable,
    typename TString,
    typename TStringDataTable,
    typename TDimensionCompareFunctor,
    typename TStringMatcher
>
void
KProxyDataTable<TValue, TDataTable, TString, TStringDataTable, TDimensionCompareFunctor, TStringMatcher>::
resetSort(const Dimension d) {
    _IndexVec& indexVec = _dimension_To_SortIndexVec_Map.at(d);
    _resetIndexVec(indexVec);
    _updateSortFilterIndexMap(d);
}

}  // namespace kumquat
