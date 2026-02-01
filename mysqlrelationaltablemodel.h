#ifndef MYSQLRELATIONALTABLEMODEL_H
#define MYSQLRELATIONALTABLEMODEL_H

#include <QObject>
#include <QSqlRelationalTableModel>
#include <QMap>

class MySqlRelationalTableModel : public QSqlRelationalTableModel
{
    Q_OBJECT

    QMap<QString, QString> m_colors;
public:
    explicit MySqlRelationalTableModel(QObject* parent = nullptr);


    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const override;
};

#endif // MYSQLRELATIONALTABLEMODEL_H
