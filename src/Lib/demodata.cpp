#include "demodata.h"
#include "Entity/contact.h"
#include "Model/contactmodel.h"
#include "qcontainerfwd.h"

#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QIODevice>
#include <QFileDialog>
#include <QFile>
#include <QDesktopServices>
#include <QString>


void DemoData::generate(QWidget *parent) {
    QStringList demoContacts = {
        "Amir,Horozović,amir.horozovic@example.com,+38761123456,Ulica Zmaja od Bosne 1,Sarajevo,FBiH,71000",
        "Lejla,Knežević,lejla.knezevic@example.com,+38762234567,Ulica Maršala Tita 10,Mostar,FBiH,88000",
        "Mirza,Bešlagić,mirza.beslagic@example.com,+38763345678,Šetalište Slobode 5,Tuzla,FBiH,75000",
        "Emina,Halilović,emina.halilovic@example.com,+38764456789,Ulica Nikole Tesle 20,Banja Luka,RS,78000",
        "Jasmin,Hadžiahmetović,jasmin.hadziahmetovic@example.com,+38765567890,Ulica Kralja Petra 15,Zenica,FBiH,72000",
        "Selma,Kovačević,selma.kovacevic@example.com,+38766678901,Obala Kulina bana 30,Sarajevo,FBiH,71000",
        "Tarik,Mehić,tarik.mehic@example.com,+38767789012,Ulica ZAVNOBiH-a 25,Bihać,FBiH,77000",
        "Aida,Hadžiselimović,aida.hadziselimovic@example.com,+38768890123,Ulica Safeta Zajke 40,Trebinje,RS,89101",
        "Dino,Pandžić,dino.pandzic@example.com,+38769901234,Ulica Mehmeda Spahe 7,Goražde,FBiH,73000",
        "Sanja,Mujkić,sanja.mujkic@example.com,+38761012345,Ulica Alije Izetbegovića 50,Travnik,FBiH,72270"
    };


    foreach (const QString &contactString, demoContacts) {
        QStringList fields = contactString.split(",");
        if (fields.size() == 8) {

            Contact contact(fields.at(0), fields.at(1), fields.at(2), fields.at(3), fields.at(4), fields.at(5), fields.at(6), fields.at(7));

            if (!ContactModel::addContact(contact)) {
                QMessageBox::critical(parent, QObject::tr("Greška"), QObject::tr("Neuspješan unos kontakta: ") + ContactModel::query().lastError().text());
                break;
            }

        }
    }

    QMessageBox::information(parent, QObject::tr("Generisanje završeno"), QObject::tr("Demo kontakti su uspješno generisani."));
}
