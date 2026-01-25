#ifndef MYSQLTABLEMODEL_H
#define MYSQLTABLEMODEL_H

#include <QObject>
#include <QSqlTableModel>

class MySqlTableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit MySqlTableModel(QObject* parent = nullptr);

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const override;
};

#endif // MYSQLTABLEMODEL_H
