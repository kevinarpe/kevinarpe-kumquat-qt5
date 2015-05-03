//
// Created by kca on 5/2/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KTABLEMODEL_H
#define KEVINARPE_KUMQUAT_QT5_KTABLEMODEL_H

#include "kabstractdatatable.h"
#include <QAbstractTableModel>
#include <unordered_map>
#include <functional>

namespace kumquat {

class KTableModel : public QAbstractTableModel {

    Q_OBJECT

private:
    static const QVariant INVALID_VALUE;  // = QVariant();
    typedef QAbstractTableModel Base;

public:
    typedef KAbstractDataTable<QVariant> DataTable;
    // TODO: LAST: Convert to use shared_ptr
    xyz
    typedef std::reference_wrapper<DataTable> DataTableRef;
    typedef std::unordered_map<int, DataTableRef> RoleToDataTableMap;

    KTableModel(const RoleToDataTableMap& roleToDataTableMap, QObject* parent = nullptr)
    : Base(parent),
      _roleToDataTableMap(_staticCheckRoleToDataTableMap(roleToDataTableMap)),
      _dataTable0(_staticGetDataTable0(roleToDataTableMap))
    { }

    virtual QVariant
    data(const QModelIndex& index, int role)
    const override;

    virtual QVariant
    headerData(int section, Qt::Orientation orientation, int role)
    const override;

    virtual int
    rowCount(const QModelIndex& parent)
    const override;

    virtual int
    columnCount(const QModelIndex& parent)
    const override;

private:
    const RoleToDataTableMap& _roleToDataTableMap;
    const DataTable& _dataTable0;

    static const RoleToDataTableMap&
    _staticCheckRoleToDataTableMap(const RoleToDataTableMap& map);

    static void
    _staticAssertSize(const int role, const std::string sizeDesc, const size_t expectedSize, const size_t actualSize);

    static const DataTable&
    _staticGetDataTable0(const RoleToDataTableMap& map);
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KTABLEMODEL_H
