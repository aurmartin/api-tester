#include "RequestTabWidget.h"
#include "ui_RequestTabWidget.h"
#include "HtmlHighlighter.h"

RequestTabWidget::RequestTabWidget(QWidget *parent, const QString& name, const Request &request) :
    QWidget(parent),
    ui(new Ui::RequestTabWidget),
    mManager(this),
    mName(name)
{
    ui->setupUi(this);

    ui->requestWidget->setRequest(request);

    new HtmlHighlighter(ui->responseBodyText->document());

    connect(ui->requestWidget, &RequestWidget::sendRequest, this, &RequestTabWidget::sendRequest);
    connect(&mManager, &QNetworkAccessManager::finished, [this] (QNetworkReply *reply) {
        qint64 elapsed = mRequestTimer.elapsed();

        qDebug() << "Reply:" << reply->errorString();

        if (reply->error() == QNetworkReply::NoError) {
            QString statusText("%1 %2 - %3 ms");
            statusText = statusText
                    .arg(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString())
                    .arg(reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString())
                    .arg(elapsed);

            ui->responseStatusLabel->setText(statusText);
            ui->responseBodyText->setPlainText(reply->readAll());
        } else {
            QString statusText("Error: %1");
            statusText = statusText
                    .arg(reply->errorString());

            ui->responseStatusLabel->setText(statusText);
            ui->responseBodyText->setPlainText(reply->readAll());
        }
    });
}

RequestTabWidget::~RequestTabWidget()
{
    delete ui;
}

const QString &RequestTabWidget::name() const
{
    return mName;
}

void RequestTabWidget::sendRequest(const Request& request)
{
    QString method = request.attribute(QNetworkRequest::CustomVerbAttribute).toString();

    qDebug() << "Sending request:" << method << request.url().toString();

    if (method == "GET") {
        mRequestTimer.start();
        mManager.get(request);
    }

    auto doc = request.toJson();
    QFile file("./request.json");
    file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    file.write(doc.toJson());
    file.close();
}
