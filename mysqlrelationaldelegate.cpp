#include "mysqlrelationaldelegate.h"

#include <QPainter>

MySqlRelationalDelegate::MySqlRelationalDelegate(QObject *parent)
    : QSqlRelationalDelegate(parent)
{

}


void MySqlRelationalDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect rec = option.rect;

    // paint for different standards
    QColor cpp03{0x78, 0, 0, 123};
    QColor cpp11{0xC1, 0x12, 0x1F, 123};
    QColor cpp14{0xFD, 0xF0, 0xD5, 123};
    QColor cpp17{0, 0x30, 0x49, 123};
    QColor cpp20{0x66, 0x9B, 0xBC, 123};
    QColor cpp23{0, 0x96, 0xC7, 123};

    if(index.column() == 2)
    {
        if(index.data() == "C++03") painter->fillRect(rec, cpp03);
        else if (index.data() == "C++11") painter->fillRect(rec, cpp11);
        else if (index.data() == "C++14") painter->fillRect(rec, cpp14);
        else if (index.data() == "C++17") painter->fillRect(rec, cpp17);
        else if (index.data() == "C++20") painter->fillRect(rec, cpp20);
        else if (index.data() == "C++23") painter->fillRect(rec, cpp23);
    }



    // paint selected
    painter->save();
    if(bool(option.state & QStyle::State_Selected))
    {
        painter->setBrush(QBrush(QColor(Qt::GlobalColor::darkCyan)));
        painter->drawRect(rec);
    }
    painter->restore();
    painter->save();

    painter->drawText(rec.x(), rec.y() + (rec.height()/2 + 8), index.data().toString());



    painter->restore();
}
