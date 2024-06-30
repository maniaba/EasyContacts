#ifndef SCHEMAMANAGER_H
#define SCHEMAMANAGER_H

#include <QObject>
#include <QSqlDatabase>

class SchemaManager : public QObject {
    Q_OBJECT
public:
    explicit SchemaManager(QSqlDatabase db, QObject *parent = nullptr);
    bool createSchema();

private:
    QSqlDatabase m_database;
};

#endif // SCHEMAMANAGER_H
