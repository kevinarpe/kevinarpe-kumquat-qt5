//
// Created by kca on 5/9/15.
//

#include "KQProxyStyle"
#include "KQStyleOptionViewItem"
#include <QPainter>
#include <QTextLayout>
#include <QFontMetrics>

namespace kumquat {

// public virtual
void
KQProxyStyle::
drawControl(const ControlElement element,
            const QStyleOption* opt,
            QPainter* p,
            const QWidget* widget /*= nullptr*/)
const {
    // @Nullable
    const KQStyleOptionViewItem* vopt = qstyleoption_cast<const KQStyleOptionViewItem*>(opt);

    if (CE_ItemViewItem != element || nullptr == vopt || vopt->hiliteSegmentVec.empty()) {
        QProxyStyle::drawControl(element, opt, p, widget);
        return;
    }

    p->save();
    p->setClipRect(opt->rect);

    QRect checkRect = proxy()->subElementRect(SE_ItemViewItemCheckIndicator, vopt, widget);
    QRect iconRect = proxy()->subElementRect(SE_ItemViewItemDecoration, vopt, widget);
    QRect textRect = proxy()->subElementRect(SE_ItemViewItemText, vopt, widget);

    // draw the background
    proxy()->drawPrimitive(PE_PanelItemViewItem, opt, p, widget);

    // draw the check mark
    if (vopt->features & QStyleOptionViewItem::HasCheckIndicator) {
        QStyleOptionViewItem option(*vopt);
        option.rect = checkRect;
        option.state = option.state & ~QStyle::State_HasFocus;

        switch (vopt->checkState) {
            case Qt::Unchecked:
                option.state |= QStyle::State_Off;
                break;
            case Qt::PartiallyChecked:
                option.state |= QStyle::State_NoChange;
                break;
            case Qt::Checked:
                option.state |= QStyle::State_On;
                break;
            default:
                throw std::logic_error("Unreachable code");
        }
        proxy()->drawPrimitive(QStyle::PE_IndicatorViewItemCheck, &option, p, widget);
    }

    // draw the icon
    QIcon::Mode mode = QIcon::Normal;
    if (!(vopt->state & QStyle::State_Enabled))
        mode = QIcon::Disabled;
    else if (vopt->state & QStyle::State_Selected)
        mode = QIcon::Selected;
    QIcon::State state = vopt->state & QStyle::State_Open ? QIcon::On : QIcon::Off;
    vopt->icon.paint(p, iconRect, vopt->decorationAlignment, mode, state);

    // draw the text
    if (!vopt->text.isEmpty()) {
        QPalette::ColorGroup cg = vopt->state & QStyle::State_Enabled
                                  ? QPalette::Normal : QPalette::Disabled;
        if (cg == QPalette::Normal && !(vopt->state & QStyle::State_Active))
            cg = QPalette::Inactive;

        if (vopt->state & QStyle::State_Selected) {
            p->setPen(vopt->palette.color(cg, QPalette::HighlightedText));
        } else {
            p->setPen(vopt->palette.color(cg, QPalette::Text));
        }
        if (vopt->state & QStyle::State_Editing) {
            p->setPen(vopt->palette.color(cg, QPalette::Text));
            p->drawRect(textRect.adjusted(0, 0, -1, -1));
        }

//        d->viewItemDrawText(p, vopt, textRect);
        viewItemDrawText(p, vopt, textRect);
    }

    // draw the focus rect
    if (vopt->state & QStyle::State_HasFocus) {
        QStyleOptionFocusRect o;
        o.QStyleOption::operator=(*vopt);
        o.rect = proxy()->subElementRect(SE_ItemViewItemFocusRect, vopt, widget);
        o.state |= QStyle::State_KeyboardFocusChange;
        o.state |= QStyle::State_Item;
        QPalette::ColorGroup cg = (vopt->state & QStyle::State_Enabled)
                                  ? QPalette::Normal : QPalette::Disabled;
        o.backgroundColor = vopt->palette.color(cg, (vopt->state & QStyle::State_Selected)
                                                    ? QPalette::Highlight : QPalette::Window);
        proxy()->drawPrimitive(QStyle::PE_FrameFocusRect, &o, p, widget);
    }

    p->restore();
}

static QSizeF viewItemTextLayout(QTextLayout &textLayout, int lineWidth)
{
    qreal height = 0;
    qreal widthUsed = 0;
    textLayout.beginLayout();
    while (true) {
        QTextLine line = textLayout.createLine();
        if (!line.isValid())
            break;
        line.setLineWidth(lineWidth);
        line.setPosition(QPointF(0, height));
        height += line.height();
        widthUsed = qMax(widthUsed, line.naturalTextWidth());
    }
    textLayout.endLayout();
    return QSizeF(widthUsed, height);
}

// protected virtual
void
KQProxyStyle::
viewItemDrawText(QPainter* p, const KQStyleOptionViewItem* option, const QRect& rect)
const
{
    const QWidget *widget = option->widget;
//    const int textMargin = proxyStyle->pixelMetric(QStyle::PM_FocusFrameHMargin, 0, widget) + 1;
    const int textMargin = proxy()->pixelMetric(QStyle::PM_FocusFrameHMargin, 0, widget) + 1;

    QRect textRect = rect.adjusted(textMargin, 0, -textMargin, 0); // remove width padding
    const bool wrapText = option->features & QStyleOptionViewItem::WrapText;
    QTextOption textOption;
    textOption.setWrapMode(wrapText ? QTextOption::WordWrap : QTextOption::ManualWrap);
    textOption.setTextDirection(option->direction);
    textOption.setAlignment(QStyle::visualAlignment(option->direction, option->displayAlignment));
    QTextLayout textLayout(option->text, option->font);
    textLayout.setTextOption(textOption);

    viewItemTextLayout(textLayout, textRect.width());

//    const QFontMetrics fontMetrics(option->font);
    const QFontMetricsF fontMetrics(option->font);
    QString elidedText;
    qreal height = 0;
    qreal width = 0;
    int elidedIndex = -1;
    const int lineCount = textLayout.lineCount();
    for (int j = 0; j < lineCount; ++j) {
        const QTextLine line = textLayout.lineAt(j);
        if (j + 1 <= lineCount - 1) {
            const QTextLine nextLine = textLayout.lineAt(j + 1);
            if ((nextLine.y() + nextLine.height()) > textRect.height()) {
                int start = line.textStart();
                int length = line.textLength() + nextLine.textLength();
//                const QStackTextEngine engine(textLayout.text().mid(start, length), option->font);
//                elidedText = engine.elidedText(option->textElideMode, textRect.width());
                elidedText = fontMetrics.elidedText(textLayout.text().mid(start, length), option->textElideMode, textRect.width());
                height += line.height();
                width = textRect.width();
                elidedIndex = j;
                break;
            }
        }
        if (line.naturalTextWidth() > textRect.width()) {
            int start = line.textStart();
            int length = line.textLength();
//            const QStackTextEngine engine(textLayout.text().mid(start, length), option->font);
//            elidedText = engine.elidedText(option->textElideMode, textRect.width());
            elidedText = fontMetrics.elidedText(textLayout.text().mid(start, length), option->textElideMode, textRect.width());
            height += line.height();
            width = textRect.width();
            elidedIndex = j;
            break;
        }
        width = qMax<qreal>(width, line.width());
        height += line.height();
    }

    const QRect layoutRect = QStyle::alignedRect(option->direction, option->displayAlignment,
                                                 QSize(int(width), int(height)), textRect);
    const QPointF position = layoutRect.topLeft();
    KHiliteSegmentVec::const_iterator hiliteSegmentIter = option->hiliteSegmentVec.cbegin();
    const KHiliteSegmentVec::const_iterator hiliteSegmentEnd = option->hiliteSegmentVec.cend();
    for (int i = 0; i < lineCount; ++i) {
        const QTextLine line = textLayout.lineAt(i);
        while (hiliteSegmentEnd != hiliteSegmentIter) {
            const KHiliteSegment& hs = *hiliteSegmentIter;
            const int targetBegin = hs.index();
            const int targetEnd = targetBegin + hs.count();
            const int actualBegin = line.textStart();
            const int actualEnd = actualBegin + line.textLength();
            const int maxBegin = qMax(targetBegin, actualBegin);
            const int minEnd = qMin(targetEnd, actualEnd);
            // Is there overlap?
            if (maxBegin < minEnd) {
                const int beforeHiliteBegin = actualBegin;
                const int beforeHiliteEnd = qMax(actualBegin, targetBegin);
                const int hiliteBegin = beforeHiliteEnd;
                const int hiliteEnd = qMin(actualEnd, targetEnd);
                Q_ASSERT(hiliteBegin < hiliteEnd);
//                const int afterHiliteBegin = hiliteEnd;
//                const int afterHiliteEnd = actualEnd;
                // Paint!
                qreal x = position.x() + line.x();
                if (beforeHiliteBegin < beforeHiliteEnd) {
                    const QString& beforeHiliteText = option->text.mid(beforeHiliteBegin, beforeHiliteEnd - beforeHiliteBegin);
                    const qreal width = fontMetrics.width(beforeHiliteText);
                    x += width;
                }
                {  // begin scope
                    // Save QString copy if all text has hilite.
                    const QString& hiliteText = (hiliteBegin == actualBegin && hiliteEnd == actualEnd)
                                                ? option->text
                                                : option->text.mid(hiliteBegin, hiliteEnd - hiliteBegin);
                    const qreal width = fontMetrics.width(hiliteText);
                    const qreal y = position.y() + line.y();
                    const qreal height = line.height();
                    p->fillRect(QRectF(x, y, width, height), option->backgroundBrushHilite);
                }  // end scope
            }
            // Prepare for next iteration
            int targetEnd2 = targetEnd;
            while (actualEnd >= targetEnd2) {
                ++hiliteSegmentIter;
                if (hiliteSegmentEnd == hiliteSegmentIter) {
                    break;
                }
                const KHiliteSegment& hs2 = *hiliteSegmentIter;
                targetEnd2 = hs2.index() + hs2.count();
            }
        }
        if (i == elidedIndex) {
            qreal x = position.x() + line.x();
            qreal y = position.y() + line.y() + line.ascent();
            p->save();
            p->setFont(option->font);
            p->drawText(QPointF(x, y), elidedText);
            p->restore();
            break;
        }
        line.draw(p, position);
    }
}

}  // namespace kumquat
