#include "Collection.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QIcon>

Collection::Collection(const QString& name) :
    QStandardItem(name)
{
    this->setIcon(QIcon(":/icons/archive.png"));
}

Collection* Collection::fromJson(const QJsonDocument& doc)
{
    QString title = doc["title"].toString();
    Collection* collection = new Collection(title);

    auto items = doc["items"].toArray();

    for (const auto& item : items) {
        auto itemObj = item.toObject();
        QString itemType = itemObj["type"].toString();
        if (itemType.compare("folder") == 0) {
            collection->appendRow(CollectionFolder::fromJson(itemObj));
        } else if (itemType.compare("request") == 0) {
            collection->appendRow(CollectionRequest::fromJson(itemObj));
        } else {
            throw QString("Invalid object type %1").arg(itemType);
        }
    }

    return collection;
}

CollectionFolder::CollectionFolder(const QString& name) :
    QStandardItem(name)
{
    this->setIcon(QIcon(":/icons/folder.png"));
}

CollectionFolder* CollectionFolder::fromJson(const QJsonObject& obj)
{
    QString title = obj["title"].toString();
    CollectionFolder* folder = new CollectionFolder(title);

    auto items = obj["items"].toArray();

    for (const auto& item : items) {
        auto itemObj = item.toObject();
        QString itemType = itemObj["type"].toString();
        if (itemType.compare("folder") == 0) {
            folder->appendRow(CollectionFolder::fromJson(itemObj));
        } else if (itemType.compare("request") == 0) {
            folder->appendRow(CollectionRequest::fromJson(itemObj));
        } else {
            throw QString("Invalid object type %1").arg(itemType);
        }
    }

    return folder;
}

CollectionRequest::CollectionRequest(const QString& name) :
    QStandardItem(name)
{
    qDebug() << "CollectionRequest::CollectionRequest" << name;
    this->setIcon(QIcon(":/icons/globe.png"));
}

CollectionRequest* CollectionRequest::fromJson(const QJsonObject& obj)
{
    QString title = obj["title"].toString();
    CollectionRequest* request = new CollectionRequest(title);
    return request;
}
