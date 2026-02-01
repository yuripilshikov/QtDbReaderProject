#ifndef MYSQLRELATIONALTABLEMODEL_H
#define MYSQLRELATIONALTABLEMODEL_H

#include <QObject>
#include <QSqlRelationalTableModel>

class MySqlRelationalTableModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit MySqlRelationalTableModel(QObject* parent = nullptr);


    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const override;
};

#endif // MYSQLRELATIONALTABLEMODEL_H
