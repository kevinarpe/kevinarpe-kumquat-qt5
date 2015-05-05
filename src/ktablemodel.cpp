//
// Created by kca on 5/2/15.
//

#include "ktablemodel.h"
#include <stdexcept>
#include <string>

namespace kumquat {

// static
const QVariant KTableModel::INVALID_VALUE = QVariant();


// public
KTableModel::KTableModel(const Role_To_DataTablePtr_Map& map, QObject* parent /*= nullptr*/)
    : Base(parent),
      _roleToDataTableMap(_staticCheckRoleToDataTableMap(map)),
      _dataTable0(_staticGetDataTable0(map))
{ }

// public virtual
QVariant
KTableModel::data(const QModelIndex& index, int role)
const /*override*/ {
    if (!index.isValid()) {
        return INVALID_VALUE;
    }

    auto iter = _roleToDataTableMap.find(role);
    if (iter == _roleToDataTableMap.end()) {
        return INVALID_VALUE;
    }
    else {
        const DataTablePtr& dataTablePtr = iter->second;
        const DataTable& dataTable = *dataTablePtr;
        const QVariant& x = dataTable.data(std::size_t(index.row()), std::size_t(index.column()));
        return x;
    }
}

// public virtual
QVariant
KTableModel::headerData(int sectionIndex, Qt::Orientation orientation, int role)
const /*override*/ {
    // TODO: Move this code into a private helper and reuse above.
    auto iter = _roleToDataTableMap.find(role);
    if (iter == _roleToDataTableMap.end()) {
        return INVALID_VALUE;
    }
    else {
        const DataTablePtr& dataTablePtr = iter->second;
        const DataTable& dataTable = *dataTablePtr;
        const QVariant& x = dataTable.headerData(std::size_t(sectionIndex), orientation);
        return x;
    }
}

// public virtual
int
KTableModel::rowCount(const QModelIndex& /* parent = QModelIndex() */)
const /*override*/ {
    std::size_t x = _dataTable0.rowCount();
    // TODO: Need to cast in to size_t?
    return int(x);
}

// public virtual
int
KTableModel::columnCount(const QModelIndex& /* parent = QModelIndex() */)
const /*override*/ {
    std::size_t x = _dataTable0.columnCount();
    // TODO: Need to cast in to size_t?
    return int(x);
}

// private static
const KTableModel::Role_To_DataTablePtr_Map&
KTableModel::_staticCheckRoleToDataTableMap(const Role_To_DataTablePtr_Map& map) {
    static const std::size_t UNSET_COUNT = std::size_t(-1);

    if (map.empty()) {
        throw std::invalid_argument("Map is empty");
    }

    std::size_t rowCount = UNSET_COUNT;
    std::size_t columnCount = UNSET_COUNT;
    for (const auto& key_value_pair : map) {
        const int role = key_value_pair.first;
        const DataTablePtr& dataTablePtr = key_value_pair.second;
        const DataTable& dataTable = *dataTablePtr;

        if (UNSET_COUNT == rowCount && UNSET_COUNT == columnCount) {
            rowCount = dataTable.rowCount();
            columnCount = dataTable.columnCount();
        }
        else {
            const std::size_t currRowSize = dataTable.rowCount();
            _staticAssertSize(role, "rowCount", rowCount, currRowSize);

            const std::size_t currColumnSize = dataTable.columnCount();
            _staticAssertSize(role, "columnCount", columnCount, currColumnSize);
        }
    }
    return map;
}

// private static
void
KTableModel::_staticAssertSize(const int role, const std::string sizeDesc, const size_t expectedSize,
                               const size_t actualSize) {
    if (expectedSize != actualSize) {
        const std::string msg =
                "Role " + std::to_string(role)
                + ": Expected " + sizeDesc + "=" + std::to_string(expectedSize)
                + ", but found " + std::to_string(actualSize);
        throw std::invalid_argument(msg);
    }
}

// private static
const KTableModel::DataTable&
KTableModel::_staticGetDataTable0(const KTableModel::Role_To_DataTablePtr_Map& map) {
    for (const auto& key_value_pair : map) {
        const DataTablePtr& dataTablePtr = key_value_pair.second;
        const DataTable& dataTable = *dataTablePtr;
        return dataTable;
    }
    throw std::logic_error("Unreachable code");
}

}  // namespace kumquat
