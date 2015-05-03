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
QVariant
KTableModel::data(const QModelIndex& index, int role)
const {
    if (!index.isValid()) {
        return INVALID_VALUE;
    }

    auto iter = _roleToDataTableMap.find(role);
    if (iter == _roleToDataTableMap.end()) {
        return INVALID_VALUE;
    }
    else {
        const DataTableRef& dataTableRef = *iter;
        const DataTable& dataTable = dataTableRef.get();
        // TODO: Need to cast in to size_t?
        QVariant& x = dataTable.data(index.row(), index.column());
        return x;
    }
}

// public
QVariant
KTableModel::headerData(int sectionIndex, Qt::Orientation orientation, int role)
const {
    // TODO: Move this code into a private helper and reuse above.
    auto iter = _roleToDataTableMap.find(role);
    if (iter == _roleToDataTableMap.end()) {
        return INVALID_VALUE;
    }
    else {
        const DataTableRef& dataTableRef = *iter;
        const DataTable& dataTable = dataTableRef.get();
        // TODO: Need to cast in to size_t?
        QVariant& x = dataTable.headerData(sectionIndex, orientation);
        return x;
    }
}

// public
int
KTableModel::rowCount(const QModelIndex& parent)
const {
    std::size_t x = _dataTable0.rowCount();
    // TODO: Need to cast in to size_t?
    return x;
}

// public
int
KTableModel::columnCount(const QModelIndex& parent)
const {
    std::size_t x = _dataTable0.columnCount();
    // TODO: Need to cast in to size_t?
    return x;
}

// private static
const RoleToDataTableMap&
KTableModel::_staticCheckRoleToDataTableMap(const RoleToDataTableMap& map) {
    if (map.empty()) {
        throw std::invalid_argument("Map is empty");
    }

    std::size_t rowCount = -1;
    std::size_t columnCount = -1;
    for (const auto& key_value_pair : map) {
        const int role = key_value_pair.first;
        const DataTableRef& dataTableRef = key_value_pair.second;
        const DataTable& dataTable = dataTableRef.get();

        if (-1 == rowCount && -1 == columnCount) {
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
KTableModel::_staticGetDataTable0(const KTableModel::RoleToDataTableMap& map) {
    for (const auto& key_value_pair : map) {
        const DataTableRef& dataTableRef = key_value_pair.second;
        const DataTable& dataTable = dataTableRef.get();
        return dataTable;
    }
    throw std::logic_error("Unreachable code");
}

}  // namespace kumquat
