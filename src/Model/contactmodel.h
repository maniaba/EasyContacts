#ifndef CONTACTMODEL_H
#define CONTACTMODEL_H

#include "Entity/contact.h"
#include <QSqlQuery>

class ContactModel
{

public:
    static bool addContact(const Contact& contact);
    static bool updateContact(int id, const Contact& contact);
    static bool deleteContact(int id);
    static bool deleteAll();
    static Contact find(int id);
    static QVector<Contact> findAll();
    static int countAll();
    static int getLastInsertedId();


    static QSqlQuery query();
};

#endif // CONTACTMODEL_H
