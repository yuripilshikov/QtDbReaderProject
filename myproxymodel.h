#ifndef MYPROXYMODEL_H
#define MYPROXYMODEL_H

#include <QObject>
#include <QIdentityProxyModel>
#include <QMap>

class MyProxyModel : public QIdentityProxyModel
{
    Q_OBJECT
    QMap<QString, QString> m_colors;
public:
    explicit MyProxyModel(QObject *parent = nullptr);

    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void setSourceModel(QAbstractItemModel *sourceModel) override;

    void setDisplayColumn(int column);
    void setDecorationColumn(int column);
    void setTooltipColumn(int column);
    void setBackgroundColumn(int column);

signals:

private:
    int m_displayColumn = 0;
    int m_decorationColumn = -1;
    int m_tooltipColumn = -1;
    int m_backgroundColumn = -1;

};

#endif // MYPROXYMODEL_H
