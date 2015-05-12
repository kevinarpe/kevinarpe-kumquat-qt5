//
// Created by kca on 5/10/15.
//

#include "KSortFilterProxyDataTable"
#include "kfunctional"
#include "algorithm"

namespace kumquat {

namespace {

typedef std::vector<std::size_t> IndexVec;
typedef std::unordered_map<Dimension, IndexVec> Dimension_To_IndexVec_Map;

std::size_t
_adjIndex(const Dimension_To_IndexVec_Map& dimension_To_IndexVec_Map_,
          const Dimension dimension,
          const std::size_t index) {
    // Use std::vector::at() instead of std::vector::operator[]() to throw std::out_of_range exceptions.
    const IndexVec& indexVec = dimension_To_IndexVec_Map_.at(dimension);
    const std::size_t adjIndex = indexVec.empty() ? index : indexVec.at(index);
    return adjIndex;
}

}  // namespace (unnamed)

// public virtual
template<typename TValue, typename TDimensionCompareFunctor>
const TValue&
KSortFilterProxyDataTable<TValue, TDimensionCompareFunctor>::
data(const std::size_t rowIndex, const std::size_t columnIndex)
const /*override*/ {
    const std::size_t adjRowIndex = _adjIndex(_dimension_To_SortIndexVec_Map, Dimension::Row, rowIndex);
    const std::size_t adjColumnIndex = _adjIndex(_dimension_To_SortIndexVec_Map, Dimension::Column, columnIndex);
    const TValue& x = Base::data(adjRowIndex, adjColumnIndex);
    return x;
}

namespace {

typedef std::vector<std::size_t> IndexVec;

void
_resetIndexVec(IndexVec indexVec, const std::size_t size) {
    // Ref: http://stackoverflow.com/a/11965746/257299
    // Variable name rowCount_ will prevent shadowing of class member function rowCount().  Blarg.
    indexVec.reserve(size);
    // Fill from 0 to rowCount-1
    std::iota(indexVec.begin(), indexVec.end(), 0);
}

}  // namespace (unnamed)

template<typename TValue, typename TDimensionCompareFunctor>
void
KSortFilterProxyDataTable<TValue, TDimensionCompareFunctor>::
sort(const TDimensionCompareFunctor& compareFunctor) {
    const Dimension dimension = compareFunctor.dimension();
    IndexVec& indexVec = _dimension_To_SortIndexVec_Map.at(dimension);

    const std::size_t size_ = size(dimension);
    _resetIndexVec(indexVec, size_);

    std::sort(indexVec.begin(),
              indexVec.end(),
              // Ref: https://software.intel.com/sites/products/documentation/doclib/iss/2013/compiler/cpp-lin/GUID-835983D0-9779-422E-B339-0205358CAACC.htm
              // [&] capture all necessary variables (compareFunctor) by reference.
              [&](const std::size_t rowIndexA, const std::size_t rowIndexB) -> bool {
                  // Be careful: Might be slow to add extra function call.
                  // Trade-off: I don't like having a big, messy lambda.
                  // But, probably the compiler optimises away.
                  const bool x = compareFunctor(*this, rowIndexA, rowIndexB);
                  return x;
              });
}

template<typename TValue, typename TDimensionCompareFunctor, typename TDimensionFilterFunctor>
void
KSortFilterProxyDataTable<TValue, TDimensionCompareFunctor, TDimensionFilterFunctor>::
filter(const TDimensionFilterFunctor& filterFunctor) {
    const Dimension dimension = filterFunctor.dimension();
    IndexVec& indexVec = _dimension_To_SortIndexVec_Map.at(dimension);

    const std::size_t size_ = size(dimension);
    _resetIndexVec(indexVec, size_);

    auto remote_if_iter =
        std::remove_if(indexVec.begin(),
                       indexVec.end(),
                       // [&] capture all necessary variables (compareFunctor) by reference.
                       [&](const std::size_t index) -> bool {
                           const bool x = filterFunctor(*this, index);
                           return x;
                       });
    indexVec.erase(remote_if_iter, indexVec.end());
}

namespace {

typedef std::vector<std::size_t> IndexVec;
typedef std::unordered_map<Dimension, IndexVec> Dimension_To_IndexVec_Map;

void
_clearSort(const bool flag, const Dimension dimension, Dimension_To_IndexVec_Map dimension_To_IndexVec_Map) {
    if (!flag) {
        return;
    }
    IndexVec& indexVec = dimension_To_IndexVec_Map[dimension];
    indexVec.clear();
}

}  // namespace (unnamed)

// public virtual
template<typename TValue, typename TDimensionCompareFunctor>
void
KSortFilterProxyDataTable<TValue, TDimensionCompareFunctor>::
clearSort(Dimensions dimensions) {
    _clearSort(bool(dimensions & Dimension::Row), Dimension::Row, _dimension_To_SortIndexVec_Map);
    _clearSort(bool(dimensions & Dimension::Column), Dimension::Column, _dimension_To_SortIndexVec_Map);
}

}  // namespace kumquat
