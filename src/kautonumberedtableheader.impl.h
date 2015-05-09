//
// Created by kca on 5/3/15.
//

#include "KAutoNumberedTableHeader"
#include <vector>

namespace kumquat {

// public virtual
template<typename TValue>
const TValue&
KAutoNumberedTableHeader<TValue>::
data(const std::size_t index)
const /*override*/ {
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
    const TValue& x = _headerData[index];
    return x;
}

}  // namespace kumquat
