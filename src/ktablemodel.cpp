//
// Created by kca on 5/2/15.
//

#include "ktablemodel.h"

namespace kumquat {

// Like 'static' for C functions (not exported: 'extern')
namespace {

void
_assertSize(const int role, const std::string sizeDesc, const size_t expectedSize,
            const size_t actualSize) {
    if (expectedSize != actualSize) {
        const std::string msg =
            "Role " + std::to_string(role)
            + ": Expected " + sizeDesc + "=" + std::to_string(expectedSize)
            + ", but found " + std::to_string(actualSize);
        throw std::invalid_argument(msg);
    }
}

const KTableModel::Role_To_DataTablePtr_MapPtr&
_checkRoleToDataTableMap(const KTableModel::Role_To_DataTablePtr_MapPtr& mapPtr) {
    static const std::size_t UNSET_COUNT = std::size_t(-1);

    if (mapPtr->empty()) {
        throw std::invalid_argument("Map is empty");
    }

    std::size_t rowCount = UNSET_COUNT;
    std::size_t columnCount = UNSET_COUNT;

    for (const auto& key_value_pair : *mapPtr) {
        const int role = key_value_pair.first;
        const KTableModel::DataTablePtr& dataTablePtr = key_value_pair.second;
        const KTableModel::DataTable& dataTable = *dataTablePtr;

        if (UNSET_COUNT == rowCount && UNSET_COUNT == columnCount) {
            rowCount = dataTable.rowCount();
            columnCount = dataTable.columnCount();
        }
        else {
            const std::size_t currRowSize = dataTable.rowCount();
            _assertSize(role, "rowCount", rowCount, currRowSize);

            const std::size_t currColumnSize = dataTable.columnCount();
            _assertSize(role, "columnCount", columnCount, currColumnSize);
        }
    }
    return mapPtr;
}

const KTableModel::DataTablePtr&
_getDataTable0(const KTableModel::Role_To_DataTablePtr_MapPtr& mapPtr) {
    for (const auto& key_value_pair : *mapPtr) {
        const KTableModel::DataTablePtr& dataTablePtr = key_value_pair.second;
        return dataTablePtr;
    }
    throw std::logic_error("Unreachable code: Expected argument 'mapPtr' not to be empty");
}

}  // namespace (unnamed)

// static
const QVariant KTableModel::INVALID_VALUE = QVariant();

// public
KTableModel::
KTableModel(const Role_To_DataTablePtr_MapPtr& mapPtr, QObject* parent /*= nullptr*/)
    : Base(parent),
      _role_To_DataTablePtr_MapPtr(_checkRoleToDataTableMap(mapPtr)),
      _dataTablePtr0(_getDataTable0(mapPtr))
{ }

// public virtual
QVariant
KTableModel::data(const QModelIndex& index, int role)
const /*override*/ {
    if (!index.isValid()) {
        return INVALID_VALUE;
    }

    auto iter = _role_To_DataTablePtr_MapPtr->find(role);
    if (iter == _role_To_DataTablePtr_MapPtr->end()) {
        return INVALID_VALUE;
    }
    else {
        const DataTablePtr& dataTablePtr = iter->second;
        const DataTable& dataTable = *dataTablePtr;
        const std::size_t rowIndex = std::size_t(index.row());
        const std::size_t columnIndex = std::size_t(index.column());
        const QVariant& x = dataTable.data(rowIndex, columnIndex);
        return x;
    }
}

// public virtual
QVariant
KTableModel::headerData(int sectionIndex, Qt::Orientation orientation, int role)
const /*override*/ {
    auto iter = _role_To_DataTablePtr_MapPtr->find(role);
    if (iter == _role_To_DataTablePtr_MapPtr->end()) {
        return INVALID_VALUE;
    }
    else {
        const DataTablePtr& dataTablePtr = iter->second;
        const DataTable& dataTable = *dataTablePtr;
        const std::size_t sectionIndex2 = std::size_t(sectionIndex);
        const QVariant& x = dataTable.headerData(sectionIndex2, orientation);
        return x;
    }
}

// public virtual
int
KTableModel::rowCount(const QModelIndex& /* parent = QModelIndex() */)
const /*override*/ {
    const std::size_t x = _dataTablePtr0->rowCount();
    const int y = int(x);
    return y;
}

// public virtual
int
KTableModel::columnCount(const QModelIndex& /* parent = QModelIndex() */)
const /*override*/ {
    const std::size_t x = _dataTablePtr0->columnCount();
    const int y = int(x);
    return y;
}

}  // namespace kumquat
