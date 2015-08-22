//
// Created by kca on 5/17/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KPROXYDATATABLE_H
#define KEVINARPE_KUMQUAT_QT5_KPROXYDATATABLE_H

#include "KDataTable"
#include "KFixedSizeMap"
#include "KQStringMatcherByQRegExp"
#include "KStringMatch"
#include "KMatrixIndex"
#include <QVariant>
#include <unordered_map>

namespace kumquat {


// Sample matches classes: QVariant
// template TValue
// {
//     QString toString() const;
// };

template<
    typename TValue                   = QVariant,
    typename TDataTable               = KDataTable<TValue>,
    typename TString                  = QString,
    typename TStringDataTable         = KDataTable<TString>,
    typename TDimensionCompareFunctor = int,  // ???
    typename TStringMatcher           = KQStringMatcherByQRegExp
>
class KProxyDataTable {

public:
    typedef TDataTable DataTable;
    typedef std::shared_ptr<DataTable> DataTablePtr;
    using TDataTable::const_iterator;
    typedef std::vector<KMatrixIndex, KStringMatchVec> MatrixIndex_KStringMatchVec_PairVec;

    KProxyDataTable(DataTablePtr dataTablePtr);

    std::size_t
    size(const Dimension d)
    const;

    const TValue&
    data(const std::size_t rowIndex, const std::size_t columnIndex)
    const;

    const TValue&
    headerData(const std::size_t index, Qt::Orientation orientation)
    const;

    void
    sort(TDimensionCompareFunctor fn);

    void
    resetSort(const Dimension d);

    MatrixIndex_KStringMatchVec_PairVec
    search(TStringMatcher m);

    // Use Dimensions(0) to clear.
    void
    filter(const Dimensions& dims);

private:
    enum class _FilterResult {
        Include = 0x1,
        Exclude = 0x2,
    };

    typedef std::vector<std::size_t> _IndexVec;
    typedef KFixedSizeMap<Dimension, _IndexVec> _Dimension_To_IndexVec_Map;
    // Avoid std::vector<bool>
    // Ref: http://stackoverflow.com/a/670322/257299
    typedef std::vector<_FilterResult> _FilterResultVec;
    typedef KFixedSizeMap<Dimension, _FilterResultVec> _Dimension_To_FilterResultVec_Map;

    static const KFixedSizeMap<Qt::Orientation, Dimension> QT_ORIENTATION_TO_DIMENSION_MAP;

    const DataTablePtr _dataTablePtr;
    const TStringDataTable _stringDataTable;

    // Sort permutation (unfiltered)
    // "Always" same length as _dataTablePtr.size()
    // Ref: http://stackoverflow.com/a/17074810/257299
    _Dimension_To_IndexVec_Map _dimension_To_SortIndexVec_Map;

    // Filter result (unsorted) -- if true, include
    // "Always" same length as _dataTablePtr.size()
    _Dimension_To_FilterResultVec_Map _dimension_To_FilterResultVec_Map;

    Dimensions _filterDimensions;

    // Filtered sort permutation
    // "Always" same length as number of true values in FilterDeque
    _Dimension_To_IndexVec_Map _dimension_To_SortFilterIndexVec_Map;

    static _IndexVec&
    _resetIndexVec(_IndexVec& v);

    static _FilterResultVec&
    _resetFilterResultVec(_FilterResultVec& v);

    static TStringDataTable
    _createStringDataTable(const DataTablePtr& dataTablePtr);

    void
    _updateSortFilterIndexMap(const Dimension d);

    std::size_t
    _adjustIndex(const Dimension d, const std::size_t index)
    const;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KPROXYDATATABLE_H
