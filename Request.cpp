#include "Request.h"

#include <QJsonArray>
#include <QJsonObject>

QJsonDocument Request::toJson() const
{
    QJsonDocument doc;
    QJsonArray headers;

    for (auto key : rawHeaderList()) {
        headers.append(QJsonObject{{key, QString(rawHeader(key))}});
    }

    doc.setObject(QJsonObject{
                      {"url", url().toString()},
                      {"method", attribute(QNetworkRequest::CustomVerbAttribute).toString()},
                      {"headers", headers}
                  });
    return doc;
}

Request Request::fromJson(const QJsonDocument &doc)
{
    Request request;

    request.setUrl(doc.object().value("url").toString());
    request.setAttribute(QNetworkRequest::CustomVerbAttribute, doc.object().value("method").toString());

    for (auto header : doc.object().value("headers").toArray()) {
        QJsonObject headerObject = header.toObject();
        QString key = headerObject.keys().at(0);
        QString value = headerObject.find(key)->toString();
        request.setRawHeader(key.toUtf8(), value.toUtf8());
    }

    return request;
}
