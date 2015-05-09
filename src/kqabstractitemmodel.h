//
// Created by kca on 5/9/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KABSTRACTITEMMODEL_H
#define KEVINARPE_KUMQUAT_QT5_KABSTRACTITEMMODEL_H

#include <QAbstractItemModel>
#include <functional>

namespace std {

// Ref: http://stackoverflow.com/a/21029900/257299
template<>
struct hash<QModelIndex> {

    size_t
    operator()(const QModelIndex& value)
    const {
        // Ref: https://bugreports.qt.io/browse/PYSIDE-41
        const quintptr x = value.internalId();
        // Ref: http://stackoverflow.com/a/21062520/257299
        const size_t y = hash<quintptr>()(x);
        return y;
    }
};

}

#endif //KEVINARPE_KUMQUAT_QT5_KABSTRACTITEMMODEL_H
