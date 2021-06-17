#ifndef REQUEST_H
#define REQUEST_H

#include <QString>
#include <QVector>
#include <QPair>
#include <QJsonDocument>
#include <QNetworkRequest>

class Request : public QNetworkRequest
{
public:
    QJsonDocument toJson() const;
    static Request fromJson(const QJsonDocument& doc);
};

#endif // REQUEST_H
