#include "vcardhandler.h"
#include "Model/contactmodel.h"


#include <QDebug>
#include <QMessageBox>
#include <QIODevice>
#include <QFileDialog>
#include <QFile>
#include <QDesktopServices>

#include "Entity/contact.h"

bool VCardHandler::exportContacts(const QString &fileName)
{
    try {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(nullptr, QObject::tr("Greška"), QObject::tr("Ne mogu otvoriti datoteku za pisanje: ") + file.errorString());
            return false;
        }

        QTextStream out(&file);
        ContactModel contactModel;
        QVector<Contact> contacts = contactModel.findAll();

        for (const Contact &contact : contacts) {
            out << "BEGIN:VCARD\n";
            out << "VERSION:3.0\n";
            out << "FN:" << contact.firstName() << " " << contact.lastName() << "\n";
            out << "EMAIL:" << contact.email() << "\n";
            out << "TEL:" << contact.phone() << "\n";
            out << "ADR:" << contact.address() << ";" << contact.city() << ";" << contact.state() << ";" << contact.zipCode() << "\n";
            out << "END:VCARD\n";
        }

        file.close();
        QMessageBox::information(nullptr, QObject::tr("Izvoz završen"), QObject::tr("Kontakti su uspješno izvezeni u vCard format."));
        return true;
    } catch (const std::exception &e) {
        QMessageBox::critical(nullptr, QObject::tr("Greška"), e.what());
        qDebug() << "Izuzetak uhvaćen:" << e.what();
        return false;
    }
}

bool VCardHandler::importContacts(const QString &fileName)
{
    try {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(nullptr, QObject::tr("Greška"), QObject::tr("Ne mogu otvoriti datoteku za čitanje: ") + file.errorString());
            return false;
        }

        QTextStream in(&file);

        QString firstName, lastName, email, phone, address, city, state, zipCode;
        ContactModel contactModel;
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.startsWith("FN:")) {
                QStringList nameParts = line.mid(3).split(" ");
                if (nameParts.size() >= 2) {
                    firstName = nameParts.at(0);
                    lastName = nameParts.at(1);
                } else if (nameParts.size() == 1) {
                    firstName = nameParts.at(0);
                    lastName = "";
                }
            } else if (line.startsWith("EMAIL:")) {
                email = line.mid(6);
            } else if (line.startsWith("TEL:")) {
                phone = line.mid(4);
            } else if (line.startsWith("ADR:")) {
                QStringList addressParts = line.mid(4).split(";");
                if (addressParts.size() >= 4) {
                    address = addressParts.at(0);
                    city = addressParts.at(1);
                    state = addressParts.at(2);
                    zipCode = addressParts.at(3);
                }
            } else if (line.startsWith("END:VCARD")) {
                Contact contact(firstName, lastName, email, phone, address, city, state, zipCode);
                if (!contactModel.addContact(contact)) {
                    QMessageBox::critical(nullptr, QObject::tr("Greška"), QObject::tr("Neuspješan unos kontakta"));
                    return false;
                }
            }
        }

        file.close();
        QMessageBox::information(nullptr, QObject::tr("Uvoz završen"), QObject::tr("Kontakti su uspješno uvezeni iz vCard formata."));
        return true;

    } catch (const std::exception &e) {
        QMessageBox::critical(nullptr, QObject::tr("Greška"), e.what());
        qDebug() << "Izuzetak uhvaćen:" << e.what();
        return false;
    }
}
