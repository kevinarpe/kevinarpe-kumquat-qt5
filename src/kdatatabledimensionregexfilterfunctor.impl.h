//
// Created by kca on 5/11/15.
//

#include "KDataTableDimensionRegexFilterFunctor"

namespace kumquat {

template<
    typename TValue,
    Dimension _dimension,
    typename TValueToQStringFunctor,
    typename TDataTableDataFunctor
>
bool
KDataTableDimensionRegexFilterFunctor<TValue, _dimension, TValueToQStringFunctor, TDataTableDataFunctor>::
operator()(const KIDataTable<TValue>* const dataTable,
           const std::size_t index)
const {

}

}  // namespace kumquat
