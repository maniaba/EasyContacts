#include "schemamanager.h"
#include "qsqlerror.h"
#include <QSqlQuery>
#include <QDebug>

SchemaManager::SchemaManager(QSqlDatabase db, QObject *parent) : QObject(parent), m_database(db) {
}

bool SchemaManager::createSchema() {
    QSqlQuery query(m_database);
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS contacts ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "firstName TEXT, "
                               "lastName TEXT, "
                               "email TEXT, "
                               "phone TEXT, "
                               "address TEXT, "
                               "city TEXT, "
                               "state TEXT, "
                               "zipCode TEXT)";
    if (!query.exec(createTableQuery)) {
        qDebug() << "Error: Unable to create table" << query.lastError();
        return false;
    }
    return true;
}
