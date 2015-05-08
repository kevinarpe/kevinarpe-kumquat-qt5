//
// Created by kca on 5/2/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KTABLEMODEL_H
#define KEVINARPE_KUMQUAT_QT5_KTABLEMODEL_H

#include "kabstractdatatable.h"
#include <QAbstractTableModel>
#include <unordered_map>
#include <memory>

namespace kumquat {

class KTableModel
    : public QAbstractTableModel {

    Q_OBJECT

private:
    static const QVariant INVALID_VALUE;  // = QVariant();
    typedef QAbstractTableModel Base;

public:
    typedef KAbstractDataTable<QVariant> DataTable;
    typedef std::shared_ptr<DataTable> DataTablePtr;
    typedef std::unordered_map<int, DataTablePtr> Role_To_DataTablePtr_Map;
    typedef std::shared_ptr<Role_To_DataTablePtr_Map> Role_To_DataTablePtr_MapPtr;

    KTableModel(const Role_To_DataTablePtr_MapPtr& mapPtr, QObject* parent = nullptr);

    virtual
    ~KTableModel()
    { }

    virtual QVariant
    data(const QModelIndex& index, int role)
    const override;

    virtual QVariant
    headerData(int sectionIndex, Qt::Orientation orientation, int role)
    const override;

    virtual int
    rowCount(const QModelIndex&  parent = QModelIndex())
    const override;

    virtual int
    columnCount(const QModelIndex&  parent = QModelIndex())
    const override;

private:
    const Role_To_DataTablePtr_MapPtr _role_To_DataTablePtr_MapPtr;
    const DataTablePtr& _dataTablePtr0;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KTABLEMODEL_H
