//
// Created by kca on 5/10/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KABSTRACTSORTEDFORWARDINGDATATABLE_H
#define KEVINARPE_KUMQUAT_QT5_KABSTRACTSORTEDFORWARDINGDATATABLE_H

#include "KAbstractForwardingDataTable"
#include "KDataTableDimensionCompareFunctor"
#include "knamespace"
#include <unordered_map>
#include <memory>
#include <deque>

namespace kumquat {

template<typename TValue, typename TDimensionCompareFunctor>
class KSortFilterProxyDataTable
    : public KAbstractForwardingDataTable<TValue> {

private:
    typedef KAbstractForwardingDataTable<TValue> Base;

public:
    typedef std::shared_ptr<KIDataTable<TValue>> DataTablePtr;
    // TODO: ctor/dtor
    KSortFilterProxyDataTable(const DataTablePtr& dataTablePtr)
        : Base(),
          _dataTablePtr(dataTablePtr),
          _dimension_To_SortIndexVec_Map(
              {
                  { Dimension::Row, IndexVec() },
                  { Dimension::Column, IndexVec() },
              })
    { }

    virtual ~KSortFilterProxyDataTable()
    { }

    // Ref: http://stackoverflow.com/questions/5286922/g-template-parameter-error
    // error: there are no arguments to ‘rowCount’ that depend on a template parameter, so a declaration of ‘rowCount’ must be available [-fpermissive]
    using KAbstractForwardingDataTable<TValue>::size;

    virtual const TValue&
    data(const std::size_t rowIndex, const std::size_t columnIndex)
    const override;

    /**
     * @param rowCompareFunc
     *        Implements the following interface:
     *            bool
     *            operator()(const KIDataTable<TValue>* const dataTable,
     *                       const std::size_t rowIndexA,
     *                       const std::size_t rowIndexB)
     *            const;
     *
     *            Dimension
     *            dimension()
     *            const;
     *
     * @see KDataTableDimensionCompareFunctor
     * @see make_dimension_compare_functor()
     */
    virtual void
    sort(const TDimensionCompareFunctor& compareFunctor);

    /**
     * Reverts to original, unsorted, underlying table.
     */
    virtual void
    reset(Dimensions dimensions);

    // TODO: LAST: Add filtering to same class


protected:
    virtual const KIDataTable<TValue>&
    dataTableDelegate()
    const override {
        const KIDataTable<TValue>& x = *_dataTablePtr;
        return x;
    }

private:
    const DataTablePtr _dataTablePtr;

    typedef std::vector<std::size_t> IndexVec;
    typedef std::unordered_map<Dimension, IndexVec> Dimension_To_IndexVec_Map;
    // Sort permutation (unfiltered)
    // "Always" same length as _dataTablePtr.size()
    // Ref: http://stackoverflow.com/a/17074810/257299
    Dimension_To_IndexVec_Map _dimension_To_SortIndexVec_Map;

    // Avoid std::vector<bool>
    // Ref: http://stackoverflow.com/a/670322/257299
    typedef std::deque<bool> FilterDeque;
    typedef std::unordered_map<Dimension, FilterDeque> Dimension_To_IncludeDeque_Map;
    // Filter result (unsorted) -- if true, include
    // "Always" same length as _dataTablePtr.size()
    Dimension_To_IncludeDeque_Map _dimension_To_FilterDeque_Map;

    // Filtered sort permutation
    // "Always" same length as number of true values in FilterDeque
    Dimension_To_IndexVec_Map _dimension_To_SortFilterIndexVec_Map;

    // TODO: GUI idea: Multiple search items get multiple colors
    // Typing in the lineedit will automatically change font color
    // And search results will match
    // TODO: LAST: Third dimension
    // Sort, Search, Filter
    // ... where Search might be match results of std::vector<QRegexp> (std::vector<Match{index, count}>)
    // Filter could be a simple algo to decide if row/column has at least one cell with at least one match -> true!
};

}  // namespace kumquat

#include "ksortfilterproxydatatable.impl.h"

#endif //KEVINARPE_KUMQUAT_QT5_KABSTRACTSORTEDFORWARDINGDATATABLE_H
