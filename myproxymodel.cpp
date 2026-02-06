#include "myproxymodel.h"
#include <QColor>
#include <QIcon>

MyProxyModel::MyProxyModel(QObject *parent) : QIdentityProxyModel(parent),
    m_colors{{"3", "#780000"}
               ,{"11", "#C1121f"}
               ,{"14", "#fdf0d5"}
               ,{"17", "#003049"}
               ,{"20", "#669bbc"}
               ,{"23", "#0096c7"}}
{}

int MyProxyModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1; // 1 column for list view
}

QVariant MyProxyModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || !sourceModel()) return QVariant();

    QModelIndex sourceIndex = mapToSource(index);

    switch(role)
    {
    case Qt::DisplayRole:
        return sourceModel()->data(sourceModel()->index(sourceIndex.row(), m_displayColumn), Qt::DisplayRole);
    case Qt::DecorationRole:
    {
        return QIcon(":/icons/violetIcon.png");
    }
    case Qt::BackgroundRole:
    {
        QString standard = sourceModel()->data(sourceModel()->index(sourceIndex.row(), m_backgroundColumn)).toString();
        if(m_colors.contains(standard))
        {
            QColor c{m_colors.value(standard)};
            c.setAlpha(123);
            return c;
        }
        return QColor(Qt::red);
    }
    case Qt::ToolTipRole:
        return sourceModel()->data(sourceModel()->index(sourceIndex.row(), m_tooltipColumn));
    }
    return QVariant();
}

void MyProxyModel::setSourceModel(QAbstractItemModel* sourceModel)
{
    QIdentityProxyModel::setSourceModel(sourceModel);
}

void MyProxyModel::setDisplayColumn(int column)
{
    m_displayColumn = column;
    emit dataChanged(index(0, 0), index(rowCount()-1, 0));
}

void MyProxyModel::setDecorationColumn(int column)
{
    m_decorationColumn = column;
    emit dataChanged(index(0, 0), index(rowCount()-1, 0));
}

void MyProxyModel::setTooltipColumn(int column)
{
    m_tooltipColumn = column;
    emit dataChanged(index(0, 0), index(rowCount()-1, 0));
}

void MyProxyModel::setBackgroundColumn(int column)
{
    m_backgroundColumn = column;
    emit dataChanged(index(0, 0), index(rowCount()-1, 0));
}
