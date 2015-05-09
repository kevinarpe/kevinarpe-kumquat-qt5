//
// Created by kca on 5/9/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KQSTYLEOPTIONVIEWITEM_H
#define KEVINARPE_KUMQUAT_QT5_KQSTYLEOPTIONVIEWITEM_H

#include "KHiliteSegmentGroup"
#include <QStyleOptionViewItem>

namespace kumquat {

class KQStyleOptionViewItem
    : public QStyleOptionViewItem {

private:
    typedef QStyleOptionViewItem Base;

public:
    static KQStyleOptionViewItem
    fromQStyleOptionViewItem(const QStyleOptionViewItem& other) {
        KQStyleOptionViewItem x;
        // Here be dragons.
        QStyleOptionViewItem* x2 = static_cast<QStyleOptionViewItem*>(&x);
        *x2 = other;
        return x;
    }

    enum StyleOptionVersion { Version = 256 };

    KQStyleOptionViewItem()
        : KQStyleOptionViewItem(Version)
    { }

    KQStyleOptionViewItem(const KQStyleOptionViewItem& other)
        : KQStyleOptionViewItem(Version)
    { *this = other; }

    QBrush backgroundBrushHilite;
    KHiliteSegmentVec hiliteSegmentVec;

protected:
    KQStyleOptionViewItem(int version)
        : Base(version)
    { }
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KQSTYLEOPTIONVIEWITEM_H
