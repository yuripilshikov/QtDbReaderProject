#ifndef MYSQLRELATIONALDELEGATE_H
#define MYSQLRELATIONALDELEGATE_H

#include <QObject>
#include <QSqlRelationalDelegate>

class MySqlRelationalDelegate : public QSqlRelationalDelegate
{
    Q_OBJECT
public:
    explicit MySqlRelationalDelegate(QObject* parent);


    // QAbstractItemDelegate interface
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // MYSQLRELATIONALDELEGATE_H
