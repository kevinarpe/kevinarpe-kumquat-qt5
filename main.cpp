#include "mymodel.h"
#include "KVectorTableHeader"
#include "KAutoNumberedTableHeader"
#include "KQTableModel"
#include "KQSortFilterProxyModel"
#include "knamespace"
#include "KQStyledItemDelegate"
#include "KQProxyStyle"
#include "KSparseDataMatrix"
#include "KDataTable"
#include "KColumnCount"
//#define BACKWARD_HAS_DW 1
//#include "backward.hpp"
#include <QApplication>
#include <QTableView>
#include <iostream>
#include <src/kcolumncount.h>

int main(int argc, char* argv[]) {
    std::cout << "Hello, World!: " << __cplusplus << std::endl;

    typedef kumquat::KDataTable<QVariant> KDataTable;
    typedef std::shared_ptr<KDataTable> KDataTablePtr;
    typedef typename KDataTable::DataMatrix DataMatrix;
    typedef typename KDataTable::DataMatrixPtr DataMatrixPtr;
    KDataTable::TableHeaderPtr horizontalTableHeaderPtr =
        std::make_unique<kumquat::KVectorTableHeader<QVariant>>(
            std::vector<QVariant>({ "Header1", "Header2", "Header3" }));
    KDataTable::TableHeaderPtr verticalTableHeaderPtr =
        std::make_unique<kumquat::KAutoNumberedTableHeader<QVariant>>();
    DataMatrixPtr dataMatrixPtr =
        std::make_unique<kumquat::KRowDataMatrix<QVariant>>(kumquat::KColumnCount(3));
    KDataTablePtr dataTablePtr =
        std::make_shared<KDataTable>(
            std::move(horizontalTableHeaderPtr),
            std::move(verticalTableHeaderPtr),
            std::move(dataMatrixPtr));
    dataTablePtr->append({ 123, 456.789, "somedata" });

    kumquat::KQTableModel::Role_To_DataTablePtr_MapPtr role_To_DataTablePtr_MapPtr =
        kumquat::KQTableModel::Role_To_DataTablePtr_MapPtr(
            new kumquat::KQTableModel::Role_To_DataTablePtr_Map({ { Qt::DisplayRole, dataTablePtr } }));

    typedef std::shared_ptr<kumquat::KQTableModel> KQTableModelPtr;
    KQTableModelPtr tableModelPtr(new kumquat::KQTableModel(role_To_DataTablePtr_MapPtr));

    typedef std::shared_ptr<kumquat::KQSortFilterProxyModel> KQSortFilterProxyModelPtr;
    KQSortFilterProxyModelPtr proxyModelPtr(new kumquat::KQSortFilterProxyModel());
    proxyModelPtr->setSourceModel(tableModelPtr.get());

    typedef std::shared_ptr<kumquat::KQStyledItemDelegate> KQStyledItemDelegatePtr;
    KQStyledItemDelegatePtr itemDelegatePtr(new kumquat::KQStyledItemDelegate());
    itemDelegatePtr->setBackgroundBrushHilite(QBrush(Qt::GlobalColor::yellow));
    kumquat::KHiliteSegmentGroup& hiliteSegmentGroup = itemDelegatePtr->hiliteSegmentGroup();
    {
        const QModelIndex modelIndex = proxyModelPtr->index(0, 2);
        hiliteSegmentGroup[modelIndex] =
            kumquat::KHiliteSegmentVec(
                {
                    kumquat::KHiliteSegment::fromIndexAndCount(1, 1),
                    kumquat::KHiliteSegment::fromIndexAndCount(3, 2),
                });
    }

    QApplication a(argc, argv);
    QTableView tableView;

    typedef std::shared_ptr<kumquat::KQProxyStyle> KQProxyStylePtr;
    KQProxyStylePtr stylePtr(new kumquat::KQProxyStyle(tableView.style()));
    
    tableView.setStyle(stylePtr.get());
    tableView.setItemDelegate(itemDelegatePtr.get());

//    MyModel myModel(0);
//    tableView.setModel(&myModel);
    tableView.setModel(proxyModelPtr.get());
    tableView.show();
    const int exitCode = a.exec();
    return exitCode;
}
