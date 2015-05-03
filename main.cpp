#include "mymodel.h"
#include "kvectortableheader.h"
#include "krowvectordatatable.h"
#include "kautonumberedtableheader.h"
#include "ktablemodel.h"
#include "ksortfilterproxymodel.h"
#include <QApplication>
#include <QTableView>
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Hello, World!: " << __cplusplus << std::endl;

    typedef kumquat::KRowVectorDataTable<QVariant> KQRowVectorDataTable;
    KQRowVectorDataTable::TableHeaderPtr horizontalTableHeader =
        std::make_unique<kumquat::KVectorTableHeader<QVariant>>(std::vector<QVariant>({ "abc", "def", "ghi" }));
    KQRowVectorDataTable::TableHeaderPtr verticalTableHeader =
        std::make_unique<kumquat::KAutoNumberedTableHeader<QVariant>>();
    kumquat::KRowVectorDataTable<QVariant> dataTable(std::move(horizontalTableHeader), std::move(verticalTableHeader));
    dataTable.appendRow({ 123, 456.789, "data" });
    kumquat::KTableModel x()

    QApplication a(argc, argv);
    QTableView tableView;
    MyModel myModel(0);
    tableView.setModel(&myModel);
    tableView.show();
    const int exitCode = a.exec();
    return exitCode;
}
