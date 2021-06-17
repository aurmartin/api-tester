#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "RequestTabWidget.h"
#include "Collection.h"
#include "Application.h"

#include <QDebug>
#include <iostream>
#include <QtNetwork>
#include <QDesktopWidget>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->requestTabWidget->clear();

    move(QApplication::desktop()->screen()->rect().center() - rect().center());
    ui->splitter->setStretchFactor(1, 2);

    QStandardItemModel *model = new QStandardItemModel();
    QStandardItem *parentItem = model->invisibleRootItem();

    QFile collectionFile(Application::settings().value("collectionsPath").toString().append("/collectionTest.json"));
    if (collectionFile.open(QFile::ReadWrite)) {
        auto content = collectionFile.readAll();
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(content, &error);
        if (error.error != QJsonParseError::NoError) {
            qWarning() << "Error parsing file:" << error.errorString();
        }

        Collection* collection = Collection::fromJson(doc);
        parentItem->appendRow(collection);

        collectionFile.close();
    } else {
        qWarning() << "Error opening file";
    }

    ui->collectionsTreeView->setModel(model);

    connect(ui->requestTabWidget, &QTabWidget::currentChanged, [this] (int index) {
        auto widget = ui->requestTabWidget->widget(index);
        if (QString("RequestTabWidget").compare(widget->metaObject()->className()) > 0) {
            RequestTabWidget *tab = new RequestTabWidget(ui->requestTabWidget, "Untitled", Request());
            widget->deleteLater();
            ui->requestTabWidget->addTab(tab, tab->name());
            ui->requestTabWidget->addTab(new QWidget(), "+");
        }
    });

    QFile file("./request.json");
    if (file.open(QFile::ReadWrite)) {
        auto content = file.readAll();
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(content, &error);
        if (error.error != QJsonParseError::NoError) {
            qWarning() << "Error parsing file:" << error.errorString();
        }

        RequestTabWidget *tab = new RequestTabWidget(ui->requestTabWidget, "Untitled", Request::fromJson(doc));
        ui->requestTabWidget->addTab(tab, tab->name());

        ui->requestTabWidget->addTab(new QWidget(), "+");

        file.close();
    } else {
        qWarning() << "Error opening file";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
