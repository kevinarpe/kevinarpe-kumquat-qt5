//
// Created by kca on 5/16/15.
//

#include "kstdlib"
#include <string>
#include <iostream>
#include <sstream>

namespace kumquat {

void
kabort(std::string message) {
      std::cerr << message << std::endl;
      std::abort();
}

void
__kabort(std::string message, const char* const filePath, unsigned int lineNumber, const char* const prettyFunc) {
    std::ostringstream str;
    str << filePath << ":" << lineNumber << " " << prettyFunc << "\n" << message;
    const std::string& final_message = str.str();
    kabort(final_message);
//    throw std::logic_error(final_message);
}

}  // namespace kumquat
/*
const mapped_type& kumquat::KFixedSizeMap<TKey, TValue, TCompare, TAllocator>::operator[](const key_type&) const [with TKey = Qt::Orientation; TValue = std::shared_ptr<kumquat::KITableHeader<QVariant> >; TCompare = std::less<Qt::Orientation>; TAllocator = std::allocator<std::pair<const Qt::Orientation, std::shared_ptr<kumquat::KITableHeader<QVariant> > > >; kumquat::KFixedSizeMap<TKey, TValue, TCompare, TAllocator>::mapped_type = std::shared_ptr<kumquat::KITableHeader<QVariant> >; kumquat::KFixedSizeMap<TKey, TValue, TCompare, TAllocator>::key_type = Qt::Orientation]

const mapped_type&
kumquat::KFixedSizeMap<TKey, TValue, TCompare, TAllocator>::
operator[](const key_type&)
const [ with
    TKey =
        Qt::Orientation; TValue = std::shared_ptr<kumquat::KITableHeader<QVariant> >
    TCompare =
        std::less<Qt::Orientation>
    TAllocator =
        std::allocator<std::pair<const Qt::Orientation, std::shared_ptr<kumquat::KITableHeader<QVariant> > > >
    kumquat::KFixedSizeMap<TKey, TValue, TCompare, TAllocator>::mapped_type =
        std::shared_ptr<kumquat::KITableHeader<QVariant> >
    kumquat::KFixedSizeMap<TKey, TValue, TCompare, TAllocator>::key_type =
        Qt::Orientation
]
*/