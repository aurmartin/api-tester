#ifndef REQUESTTABWIDGET_H
#define REQUESTTABWIDGET_H

#include <QWidget>

#include <QNetworkAccessManager>
#include <QElapsedTimer>

#include "Request.h"

namespace Ui {
class RequestTabWidget;
}

class RequestTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RequestTabWidget(QWidget *parent, const QString& name, const Request &request);
    ~RequestTabWidget();

    const QString& name() const;

private slots:
    void sendRequest(const Request& request);

private:
    Ui::RequestTabWidget *ui;
    QNetworkAccessManager mManager;
    QElapsedTimer mRequestTimer;
    QString mName;
};

#endif // REQUESTTABWIDGET_H
