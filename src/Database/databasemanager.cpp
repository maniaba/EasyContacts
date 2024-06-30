#include "databasemanager.h"
#include "schemamanager.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>

QSqlDatabase DatabaseManager::m_database = QSqlDatabase();

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent) {
}

QSqlDatabase DatabaseManager::getDatabase() {
    if (!m_database.isValid()) {
        QString dbPath = QCoreApplication::applicationDirPath() + "/contacts.db";
        qDebug() << "Database path:" << dbPath;

        bool dbExists = QFile::exists(dbPath);
        m_database = QSqlDatabase::addDatabase("QSQLITE");
        m_database.setDatabaseName(dbPath);

        if (!m_database.open()) {
            qDebug() << "Error: Unable to open database" << m_database.lastError();
            return QSqlDatabase();
        }

        if (!dbExists) {
            SchemaManager schemaManager(m_database);
            if (!schemaManager.createSchema()) {
                qDebug() << "Error: Unable to create schema";
                m_database.close();
                return QSqlDatabase();
            }
        }

        qDebug() << "Database opened successfully";
    }

    return m_database;
}

void DatabaseManager::closeDatabase() {
    if (m_database.isOpen()) {
        m_database.close();
    }
}
