//
// Created by kca on 5/9/15.
//

#include "KQStyledItemDelegate"
#include "KQStyleOptionViewItem"
#include <QApplication>

namespace kumquat {

//public virtual
void
KQStyledItemDelegate::
paint(QPainter* painter,
      const QStyleOptionViewItem& option,
      const QModelIndex& index)
const /*override*/ {
    // This code is 99% borrowed from QStyledItemDelegate::paint().
    Q_ASSERT(index.isValid());

    KQStyleOptionViewItem opt = KQStyleOptionViewItem::fromQStyleOptionViewItem(option);
    QStyledItemDelegate::initStyleOption(&opt, index);
    opt.backgroundBrushHilite = _backgroundBrushHilite;
    opt.hiliteSegmentVec = _hiliteSegmentGroup[index];

    const QWidget* widget = option.widget;
    const QStyle* style = widget ? widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, widget);
}

}  // namespace kumquat
