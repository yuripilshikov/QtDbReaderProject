#include "mysqlquerymodel.h"
#include <QColor>
#include <QIcon>

MySqlQueryModel::MySqlQueryModel(QObject *parent) : QSqlQueryModel(parent)
{
}


QVariant MySqlQueryModel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
    case Qt::DisplayRole:
        return QSqlQueryModel::data(index, Qt::DisplayRole);
    case Qt::DecorationRole:
        //return QColor(Qt::GlobalColor::green);
        return QIcon(":/icons/violetIcon.png");
    }
    return QVariant();
}
