//
// Created by kca on 5/3/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KAUTONUMBEREDTABLEHEADER_H
#define KEVINARPE_KUMQUAT_QT5_KAUTONUMBEREDTABLEHEADER_H

#include "kabstracttableheader.h"
#include <vector>

namespace kumquat {

template<typename TValue>
class KAutoNumberedTableHeader : public KAbstractTableHeader<TValue> {

private:
    typedef KAbstractTableHeader<TValue> Base;

public:
    KAutoNumberedTableHeader()
    : Base()
    { }

    virtual
    ~KAutoNumberedTableHeader()
    { }

public:
    virtual const TValue&
    data(const std::size_t index)
    const override {
        _check(index);
        const TValue& x = _headerData[index];
        return x;
    }

private:
    void
    _check(const std::size_t index)
    const {
        std::size_t size = _headerData.size();
        if (index >= size) {
            _headerData.reserve(index);
            for (std::size_t i = size ; i <= index ; ++i) {
                const std::size_t number = size + std::size_t(1);
                // QVariant is very picky about integral types.
                const qulonglong number2 = number;
                _headerData.emplace_back(number2);
            }
        }
    }

private:
    mutable std::vector<TValue> _headerData;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KAUTONUMBEREDTABLEHEADER_H
