#ifndef COLLECTION_H
#define COLLECTION_H

#include <QStandardItem>

class Collection : public QStandardItem
{
public:
    Collection(const QString& name);

    static Collection* fromJson(const QJsonDocument& doc);
};

class CollectionFolder : public QStandardItem
{
public:
    CollectionFolder(const QString& name);

    static CollectionFolder* fromJson(const QJsonObject& doc);
};

class CollectionRequest : public QStandardItem
{
public:
    CollectionRequest(const QString& name);

    static CollectionRequest* fromJson(const QJsonObject& doc);
};

#endif // COLLECTION_H
