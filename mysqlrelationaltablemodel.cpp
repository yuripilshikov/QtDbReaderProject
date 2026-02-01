#include "mysqlrelationaltablemodel.h"

#include <QIcon>

MySqlRelationalTableModel::MySqlRelationalTableModel(QObject *parent)
    : QSqlRelationalTableModel(parent)
{}


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
        return QIcon(":/icons/violetIcon.png");
    }
    return QVariant();
}

