#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>

class DatabaseManager : public QObject {
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);

    static QSqlDatabase getDatabase();
    static void closeDatabase();

private:
    static QSqlDatabase m_database;
};

#endif // DATABASEMANAGER_H
