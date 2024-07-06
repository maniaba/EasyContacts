#include <ContactModel.h>
#include <Entity/contact.h>
#include <QtTest>
#include "Lib/logger.h"

class TestUnit : public QObject
{
    Q_OBJECT

private slots:
    void testContactModelAddContact();
    void testContactModelDeleteContact();

    void testLoggger();

private:
    bool isContactInDatabase(const Contact &contact);
};

void TestUnit::testContactModelAddContact()
{
    Contact contact(QString("ime"), QString("prezime"), QString("email.email.tests"), QString("061/123-456"), QString("Adresa"), QString("grad"), QString("FBIH"), QString("123456"));

    bool result = ContactModel::addContact(contact);

    // Dodajte testni kod za dodavanje kontakta
    QVERIFY(result);

    // Provjerite da li je kontakt u bazi podataka
    QVERIFY(isContactInDatabase(contact));
}


void TestUnit::testContactModelDeleteContact()
{
    // Kreirajte Contact objekt
    Contact contact(QString("ime Deleted"), QString("prezime"), QString("email.email.tests"), QString("061/123-456"), QString("Adresa"), QString("grad"), QString("FBIH"), QString("123456"));

    // Dodajte kontakt koristeći ContactModel
    ContactModel model;
    model.addContact(contact);

    // Provjerite da li je kontakt u bazi podataka
    QVERIFY(isContactInDatabase(contact));

    int lastID = ContactModel::getLastInsertedId();

    // Obrišite kontakt koristeći ContactModel
    bool result = model.deleteContact(lastID); // Pretpostavimo da postoji metoda getId() za dobivanje ID-a kontakta
    QVERIFY(result);

    // Provjerite da li je kontakt obrisan iz baze podataka
    QVERIFY(!isContactInDatabase(contact));
}


bool TestUnit::isContactInDatabase(const Contact &contact)
{
    QSqlQuery query = ContactModel::query();

    query.prepare("SELECT COUNT(*) FROM contacts WHERE firstName = :first_name AND lastName = :last_name AND email = :email");
    query.bindValue(":first_name", contact.firstName());
    query.bindValue(":last_name", contact.lastName());
    query.bindValue(":email", contact.email());

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}

void TestUnit::testLoggger()
{
    // Postavite Logger da koristi privremeni fajl
    Logger &logger = Logger::instance();


    // Logirajte poruku o grešci
    QString errorMessage = "Test error message";
    logger.logError(errorMessage);

    logger.logFile.close();

    // Provjerite sadržaj log fajla
    QVERIFY(logger.logFile.open(QIODevice::ReadOnly | QIODevice::Text));
    QTextStream in(&logger.logFile);
    QString content = in.readAll();
    logger.logFile.close();

    // Provjerite da li log fajl sadrži očekivanu poruku
    QVERIFY(content.contains(errorMessage));

}


QTEST_MAIN(TestUnit)
#include "test_unit.moc"
