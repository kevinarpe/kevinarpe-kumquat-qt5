//
// Created by kca on 5/11/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KDATATABLEDIMENSIONFILTERFUNCTOR_H
#define KEVINARPE_KUMQUAT_QT5_KDATATABLEDIMENSIONFILTERFUNCTOR_H

#include "knamespace"
#include "KDataTableDataFunctor"
#include "KIDataTable"
#include <QVariant>
#include <functional>

namespace kumquat {

template<
    typename TValue,
    Dimension _dimension,
    typename TValueToQStringFunctor = std::bind(QVariant::toString),
    typename TDataTableDataFunctor = KDataTableDataFunctor<_dimension, TValue>
>
class KDataTableDimensionRegexFilterFunctor {

public:
    typedef std::vector<QRegExp> RegexVec;

    KDataTableDimensionRegexFilterFunctor(const RegexVec& regexVec)
        : _regexVec(regexVec)
    { }

    constexpr Dimension
    dimension()
    const noexcept {
        return _dimension;
    }

    bool
    operator()(const KIDataTable<TValue>* const dataTable,
               const std::size_t index)
    const;

private:
    const RegexVec _regexVec;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KDATATABLEDIMENSIONFILTERFUNCTOR_H
