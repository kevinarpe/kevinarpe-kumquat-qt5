//
// Created by kca on 5/9/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KPROXYSTYLE_H
#define KEVINARPE_KUMQUAT_QT5_KPROXYSTYLE_H

#include <QProxyStyle>

class QStyleOptionViewItem;

namespace kumquat {

class KQStyleOptionViewItem;

class KQProxyStyle
    : public QProxyStyle {

    Q_OBJECT

private:
    typedef QProxyStyle Base;

public:
    KQProxyStyle(QStyle* style = nullptr)
        : Base(style)
    { }

    KQProxyStyle(const QString& key)
        : Base(key)
    { }

    virtual ~KQProxyStyle()
    { }

    virtual void
    drawControl(const ControlElement element,
                const QStyleOption* opt,
                QPainter* p,
                const QWidget* widget = nullptr)
    const override;

protected:
    virtual void
    viewItemDrawText(QPainter* p, const KQStyleOptionViewItem* option, const QRect& rect)
    const;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KPROXYSTYLE_H
