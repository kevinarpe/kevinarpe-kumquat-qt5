//
// Created by kca on 5/3/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KSORTFILTERPROXYMODEL_H
#define KEVINARPE_KUMQUAT_QT5_KSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <memory>
#include <vector>

namespace kumquat {

class KAbstractModelFilter;

class KSortFilterProxyModel : public QSortFilterProxyModel {

    Q_OBJECT

private:
    typedef QSortFilterProxyModel Base;

public:
    // Ref: http://stackoverflow.com/a/6089065/257299
    typedef std::unique_ptr<KAbstractModelFilter> ModelFilterPtr;
    typedef std::vector<ModelFilterPtr> ModelFilterPtrVec;

    KSortFilterProxyModel(QObject* parent = nullptr);

    virtual
    ~KSortFilterProxyModel();

    void
    setModelFilterPtrVec(ModelFilterPtrVec& modelFilterPtrVec);

protected:
    virtual bool
    filterAcceptsRow(const int sourceRowIndex, const QModelIndex& sourceParent)
    const override;

    virtual bool
    filterAcceptsColumn(const int sourceColumnIndex, const QModelIndex& sourceParent)
    const override;

private:
    ModelFilterPtrVec _modelFilterPtrVec;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KSORTFILTERPROXYMODEL_H
