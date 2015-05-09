//
// Created by kca on 5/9/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KSTYLEDITEMDELEGATE_H
#define KEVINARPE_KUMQUAT_QT5_KSTYLEDITEMDELEGATE_H

#include "KHiliteSegmentGroup"
#include <QStyledItemDelegate>

namespace kumquat {

class KQStyledItemDelegate
    : public QStyledItemDelegate {

private:
    typedef QStyledItemDelegate Base;

public:
    explicit KQStyledItemDelegate(QObject* parent = nullptr)
        : Base(parent)
    { }

    virtual ~KQStyledItemDelegate()
    { }

    virtual void
    paint(QPainter* painter,
          const QStyleOptionViewItem& option,
          const QModelIndex& index)
    const override;

    const QBrush&
    backgroundBrushHilite()
    const {
        return _backgroundBrushHilite;
    }

    void
    setBackgroundBrushHilite(const QBrush& b) {
        _backgroundBrushHilite = b;
    }

    KHiliteSegmentGroup&
    hiliteSegmentGroup() {
        return _hiliteSegmentGroup;
    }

private:
    QBrush _backgroundBrushHilite;
    KHiliteSegmentGroup _hiliteSegmentGroup;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KSTYLEDITEMDELEGATE_H
