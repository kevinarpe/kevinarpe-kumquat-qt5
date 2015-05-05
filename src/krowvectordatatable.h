//
// Created by kca on 5/2/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KROWVECTORDATATABLE_H
#define KEVINARPE_KUMQUAT_QT5_KROWVECTORDATATABLE_H

#include "kabstracttableheader.h"
#include "kabstractdatatable.h"
#include "krowvectordatamatrix.h"

namespace std {

// Ref: http://stackoverflow.com/a/21029900/257299
template<class TEnum>
class hash {

private:
    using sfinae = typename std::enable_if<std::is_enum<TEnum>::value, TEnum>::type;

public:
    size_t
    operator()(const TEnum& value)
    const {
        size_t x = std::hash<typename std::underlying_type<TEnum>::type>()(value);
        return x;
    }
};

}

//namespace std {
//
//// Ref: http://stackoverflow.com/a/21029900/257299
//template<>
//class hash<Qt::Orientation> {
//
//public:
//    size_t
//    operator()(Qt::Orientation value)
//    const {
//        size_t x = std::hash<typename std::underlying_type<Qt::Orientation>::type>()(value);
//        return x;
//    }
//};
//
//}

#include <functional>
#include <unordered_map>
#include <memory>

namespace kumquat {

// TODO: Move the impls into separate header
template<typename TValue>
class KRowVectorDataTable : public KAbstractDataTable<TValue> {

private:
    typedef KAbstractDataTable<TValue> Base;

public:
    typedef KRowVectorDataTable<TValue> Self;
    typedef typename KRowVectorDataMatrix<TValue>::RowVec RowVec;
    typedef KAbstractTableHeader<TValue> TableHeader;
    typedef std::unique_ptr<TableHeader> TableHeaderPtr;

    // Ref: http://stackoverflow.com/a/8114913/257299
    KRowVectorDataTable(TableHeaderPtr horizontalTableHeader,
                        TableHeaderPtr verticalTableHeader)
    : Base(),
      _orientation_To_TableHeaderPtr_Map(_newMap(horizontalTableHeader, verticalTableHeader))
    { }

    virtual
    ~KRowVectorDataTable()
    { }

public:
    virtual std::size_t
    rowCount()
    const override {
        const std::size_t x = _dataMatrix.rowCount();
        return x;
    }

public:
    virtual std::size_t
    columnCount()
    const override {
        const std::size_t x = _dataMatrix.columnCount();
        return x;
    }

public:
    virtual const TValue&
    data(std::size_t rowIndex, std::size_t columnIndex)
    const override {
        const TValue& x = _dataMatrix.data(rowIndex, columnIndex);
        return x;
    }

public:
    virtual const TValue&
    headerData(const std::size_t index, Qt::Orientation orientation)
    const override {
        const TableHeaderPtr& tableHeader = _orientation_To_TableHeaderPtr_Map.at(orientation);
        const TValue& x = tableHeader->data(index);
        return x;
    }

public:
    virtual Self&
    appendRow(const RowVec& rowVec) {
        _dataMatrix.appendRow(rowVec);
        return *this;
    }

private:
    typedef std::unordered_map<Qt::Orientation, TableHeaderPtr> QtOrientation_To_TableHeaderPtr_Map;
    QtOrientation_To_TableHeaderPtr_Map _orientation_To_TableHeaderPtr_Map;
    KRowVectorDataMatrix<TValue> _dataMatrix;

    // TODO: Ask a question on StackOverflow about the difference between:
    // (a) const x& -- does not work
    // (b) x& -- works
    // (c) x -- works
    // (d) x&& -- did not try
    static QtOrientation_To_TableHeaderPtr_Map
    _newMap(TableHeaderPtr& horizontalTableHeader,
            TableHeaderPtr& verticalTableHeader) {
        // Ref: http://stackoverflow.com/a/21057289/257299
        typedef typename QtOrientation_To_TableHeaderPtr_Map::value_type MapValueType;
        QtOrientation_To_TableHeaderPtr_Map map;
        map.insert(MapValueType(Qt::Horizontal, std::move(horizontalTableHeader)));
        map.insert(MapValueType(Qt::Vertical, std::move(verticalTableHeader)));
        return map;
    }
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KROWVECTORDATATABLE_H
