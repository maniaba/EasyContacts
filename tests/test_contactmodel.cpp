#include <ContactModel.h>
#include <Entity/contact.h>
#include <QtTest>

class TestContactModel : public QObject
{
    Q_OBJECT

private slots:
    void testAddContact();
    void testDeleteContact();

private:
    bool isContactInDatabase(const Contact &contact);
};

void TestContactModel::testAddContact()
{
    Contact contact(QString("ime"), QString("prezime"), QString("email.email.tests"), QString("061/123-456"), QString("Adresa"), QString("grad"), QString("FBIH"), QString("123456"));

    bool result = ContactModel::addContact(contact);

    // Dodajte testni kod za dodavanje kontakta
    QVERIFY(result);

    // Provjerite da li je kontakt u bazi podataka
    QVERIFY(isContactInDatabase(contact));
}


void TestContactModel::testDeleteContact()
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


bool TestContactModel::isContactInDatabase(const Contact &contact)
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


QTEST_MAIN(TestContactModel)
#include "test_contactmodel.moc"
