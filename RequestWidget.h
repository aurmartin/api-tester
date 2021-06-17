#ifndef REQUESTWIDGET_H
#define REQUESTWIDGET_H

#include <QWidget>
#include <QtNetwork>
#include "Request.h"

namespace Ui {
class RequestWidget;
}

class RequestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RequestWidget(QWidget *parent = nullptr);
    ~RequestWidget();

    void setRequest(const Request& request);

signals:
    void sendRequest(const Request& request);

private:
    Ui::RequestWidget *ui;
    Request mRequest;
};

#endif // REQUESTWIDGET_H
