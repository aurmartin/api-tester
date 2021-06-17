#include "RequestWidget.h"
#include "ui_RequestWidget.h"

#include <QDebug>

RequestWidget::RequestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RequestWidget)
{
    ui->setupUi(this);
    connect(ui->sendButton, &QPushButton::clicked, [this] {
        QString method = ui->methodComboBox->currentText();
        QString url = ui->urlLineEdit->text();
        mRequest.setUrl(url);
        mRequest.setAttribute(Request::CustomVerbAttribute, method);
        for (int i = 0; i < ui->headersTable->rowCount(); i++) {
            QString key = ui->headersTable->item(i, 0)->text();
            QString value = ui->headersTable->item(i, 1)->text();
            qDebug() << key << ":" << value;
            mRequest.setRawHeader(key.toUtf8(), value.toUtf8());
        }
        emit sendRequest(mRequest);
    });
}

RequestWidget::~RequestWidget()
{
    delete ui;
}

void RequestWidget::setRequest(const Request &request)
{
    ui->methodComboBox->setCurrentText(request.attribute(Request::CustomVerbAttribute).toString());
    ui->urlLineEdit->setText(request.url().toString());
    ui->headersTable->clear();
    auto headers = request.rawHeaderList();
    ui->headersTable->setRowCount(headers.size());
    for (int i = 0; i < headers.size(); i++) {
        auto keyItem = new QTableWidgetItem(QString::fromUtf8(headers.at(i)));
        auto valueItem = new QTableWidgetItem(QString::fromUtf8(request.rawHeader(headers.at(i))));
        ui->headersTable->setItem(i, 0, keyItem);
        ui->headersTable->setItem(i, 1, valueItem);
    }
    qDebug() << "headers" << request.rawHeaderList();
}
