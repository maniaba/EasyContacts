#include "contactmodel.h"
#include "Database/databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool ContactModel::addContact(const Contact& contact)
{
    QSqlDatabase db = DatabaseManager::getDatabase();
    QSqlQuery query(db);
    query.prepare("INSERT INTO contacts (firstName, lastName, email, phone, address, city, state, zipCode) "
                  "VALUES (:firstName, :lastName, :email, :phone, :address, :city, :state, :zipCode)");
    query.bindValue(":firstName", contact.firstName());
    query.bindValue(":lastName", contact.lastName());
    query.bindValue(":email", contact.email());
    query.bindValue(":phone", contact.phone());
    query.bindValue(":address", contact.address());
    query.bindValue(":city", contact.city());
    query.bindValue(":state", contact.state());
    query.bindValue(":zipCode", contact.zipCode());

    if (!query.exec()) {
        qDebug() << "Failed to add contact:" << query.lastError().text();
        return false;
    }

    return true;
}

bool ContactModel::updateContact(int id, const Contact& contact)
{
    QSqlDatabase db = DatabaseManager::getDatabase();
    QSqlQuery query(db);
    query.prepare("UPDATE contacts SET firstName = :firstName, lastName = :lastName, email = :email, phone = :phone, "
                  "address = :address, city = :city, state = :state, zipCode = :zipCode WHERE id = :id");
    query.bindValue(":firstName", contact.firstName());
    query.bindValue(":lastName", contact.lastName());
    query.bindValue(":email", contact.email());
    query.bindValue(":phone", contact.phone());
    query.bindValue(":address", contact.address());
    query.bindValue(":city", contact.city());
    query.bindValue(":state", contact.state());
    query.bindValue(":zipCode", contact.zipCode());
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to update contact:" << query.lastError().text();
        return false;
    }
    return true;
}

bool ContactModel::deleteContact(int id)
{
    QSqlDatabase db = DatabaseManager::getDatabase();
    QSqlQuery query(db);
    query.prepare("DELETE FROM contacts WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to delete contact:" << query.lastError().text();
        return false;
    }
    return true;
}


QSqlQuery ContactModel::query() {
    QSqlQuery query(DatabaseManager::getDatabase());
    return query;
}

Contact ContactModel::find(int id) {
    QSqlDatabase db = DatabaseManager::getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT id, firstName, lastName, email, phone, address, city, state, zipCode FROM contacts WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to find contact:" << query.lastError().text();
        return Contact("", "", "", "", "", "", "", "");
    }

    if (query.next()) {
        return Contact(
            query.value("id").toInt(),
            query.value("firstName").toString(),
            query.value("lastName").toString(),
            query.value("email").toString(),
            query.value("phone").toString(),
            query.value("address").toString(),
            query.value("city").toString(),
            query.value("state").toString(),
            query.value("zipCode").toString()
            );
    }

    return Contact("", "", "", "", "", "", "", "");
}

QVector<Contact> ContactModel::findAll() {
    QSqlDatabase db = DatabaseManager::getDatabase();
    QSqlQuery query(db);
    QVector<Contact> contacts;

    if (!query.exec("SELECT id, firstName, lastName, email, phone, address, city, state, zipCode FROM contacts")) {
        qDebug() << "Failed to retrieve contacts:" << query.lastError().text();
        return contacts;
    }

    while (query.next()) {
        contacts.append(Contact(
            query.value("id").toInt(),
            query.value("firstName").toString(),
            query.value("lastName").toString(),
            query.value("email").toString(),
            query.value("phone").toString(),
            query.value("address").toString(),
            query.value("city").toString(),
            query.value("state").toString(),
            query.value("zipCode").toString()
            ));
    }

    return contacts;
}

int ContactModel::countAll() {
    QSqlDatabase db = DatabaseManager::getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM contacts");

    if (!query.exec() || !query.next()) {
        qDebug() << "Failed to count contacts:" << query.lastError().text();
        return 0;
    }

    return query.value(0).toInt();
}

int ContactModel::getLastInsertedId()
{
    QSqlDatabase db = DatabaseManager::getDatabase();
    QSqlQuery query(db);

    if (query.exec("SELECT last_insert_rowid()") && query.next()) {
        return query.value(0).toInt();
    }

    return -1;
}
