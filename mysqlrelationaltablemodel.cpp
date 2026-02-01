#include "mysqlrelationaltablemodel.h"

#include <QIcon>
#include <QColor>

MySqlRelationalTableModel::MySqlRelationalTableModel(QObject *parent)
    : QSqlRelationalTableModel(parent)
    , m_colors{{"C++03", "#780000"}
               ,{"C++11", "#C1121f"}
               ,{"C++14", "#fdf0d5"}
               ,{"C++17", "#003049"}
               ,{"C++20", "#669bbc"}
               ,{"C++23", "#0096c7"}}
{

}


QVariant MySqlRelationalTableModel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
    case Qt::DisplayRole:
        //return QSqlTableModel::data(index, Qt::DisplayRole);
        return QSqlTableModel::data(index);
    case Qt::ToolTipRole:
        return QSqlTableModel::data(index);
    case Qt::DecorationRole:
        if(index.column() == 1) return QIcon(":/icons/violetIcon.png");
        break;
    case Qt::BackgroundColorRole:
        QString standard = QSqlTableModel::data(this->index(index.row(), 2)).toString();
        if(m_colors.contains(standard))
        {
            QColor c{m_colors.value(standard)};
            c.setAlpha(123);
            return c;
        }
        else
            return QVariant();
        break;
    }
    return QVariant();
}
