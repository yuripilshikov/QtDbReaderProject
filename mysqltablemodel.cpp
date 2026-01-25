#include "mysqltablemodel.h"
#include <QIcon>

MySqlTableModel::MySqlTableModel(QObject *parent)
{

}


QVariant MySqlTableModel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
    case Qt::DisplayRole:
        return QSqlTableModel::data(index, Qt::DisplayRole);
    case Qt::DecorationRole:
        return QIcon(":/icons/violetIcon.png");
    }
    return QVariant();
}
