#ifndef MYPROXYMODELWIDGET_H
#define MYPROXYMODELWIDGET_H

#include <QWidget>

namespace Ui {
class MyProxyModelWidget;
}

class MyProxyModelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyProxyModelWidget(QWidget *parent = nullptr);
    ~MyProxyModelWidget();

public slots:
    void init();

private:
    Ui::MyProxyModelWidget *ui;
};

#endif // MYPROXYMODELWIDGET_H
