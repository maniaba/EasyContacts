#include "src/Forms/easycontacts.h"
#include "qsqlquery.h"
#include "src/Forms/oprogramu.h"
#include "src/Model/contactmodel.h"
#include "src/Database/databasemanager.h"
#include "ui_easycontacts.h"
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QIODevice>
#include <QFileDialog>
#include <QFile>
#include <QDesktopServices>


EasyContacts::EasyContacts(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EasyContacts)
    , m_contactModel(new ContactModel(this))
    , m_proxyModel(new QSortFilterProxyModel(this)) // Inicijalizacija proxy modela
    , m_contactStoreForm(nullptr)
    , m_oProgramuForm(nullptr)
{
    ui->setupUi(this);

    // Postavi kolone i učitaj podatke
    m_contactModel->setupTableView(ui->tableView, m_proxyModel);
    m_contactModel->loadContacts();

    // Povezivanje signala selekcije tabele sa slotom
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &EasyContacts::onSelectionChanged);
}

EasyContacts::~EasyContacts() {
    DatabaseManager::closeDatabase();
    delete ui;
}

void EasyContacts::on_actionIzradi_novi_kontakt_triggered() {
    if (!m_contactStoreForm) {
        m_contactStoreForm = new ContactStoreForm(this);
    }
    m_contactStoreForm->exec();  // Koristi exec() umjesto show() da bi bio modalni
    qDebug() << "m_contactStoreForm exec()";
    m_contactModel->loadContacts();
}

void EasyContacts::on_lineEdit_pretraga_textChanged(const QString &text)
{
    m_proxyModel->setFilterKeyColumn(-1); // Postavi na -1 za pretragu svih kolona
    m_proxyModel->setFilterFixedString(text);
    qDebug() << "Promjena vrijednosti filtera: " + text;
}


void EasyContacts::on_pushButton_uredi_clicked()
{
    // Dohvati trenutno selektovani red
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
    if (selection.empty()) {
        QMessageBox::warning(this, tr("Warning"), tr("No contact selected"));
        return;
    }

    QModelIndex index = selection.at(0);
    int row = index.row();

    // Kreiraj dijalog za uređivanje ako već nije kreiran
    if (!m_contactStoreForm) {
        m_contactStoreForm = new ContactStoreForm(this);
    }

    // Postavi podatke iz selektovanog reda u dijalog
    m_contactStoreForm->setContactData(m_proxyModel->index(row, 1).data().toString(),  // First Name
                                       m_proxyModel->index(row, 2).data().toString(),  // Last Name
                                       m_proxyModel->index(row, 3).data().toString(),  // Email
                                       m_proxyModel->index(row, 4).data().toString(),  // Phone
                                       m_proxyModel->index(row, 5).data().toString(),  // Address
                                       m_proxyModel->index(row, 6).data().toString(),  // City
                                       m_proxyModel->index(row, 7).data().toString(),  // State
                                       m_proxyModel->index(row, 8).data().toString(),  // Zip Code
                                       m_proxyModel->index(row, 0).data().toInt());    // ID

    // Otvori dijalog za uređivanje
    if (m_contactStoreForm->exec() == QDialog::Accepted) {
        // Ako je dijalog zatvoren sa "Ok", osvježi podatke
        m_contactModel->loadContacts();
    }
}


void EasyContacts::onSelectionChanged() {
    // Omogućavanje/Onemogućavanje dugmadi za uređivanje i brisanje na osnovu selekcije
    bool hasSelection = ui->tableView->selectionModel()->hasSelection();
    ui->pushButton_uredi->setEnabled(hasSelection);
    ui->pushButton_obrisati->setEnabled(hasSelection);
}

void EasyContacts::on_pushButton_obrisati_clicked()
{
    // Dohvati trenutno selektovane redove
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
    if (selection.empty()) {
        QMessageBox::warning(this, tr("Upozorenje"), tr("Nije odabran nijedan kontakt"));
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Potvrdi brisanje"), tr("Da li ste sigurni da želite obrisati odabrane kontakte?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        bool success = true;

        foreach (const QModelIndex &index, selection) {
            int id = m_proxyModel->index(index.row(), 0).data().toInt();
            query.prepare("DELETE FROM contacts WHERE id = :id");
            query.bindValue(":id", id);
            if (!query.exec()) {
                success = false;
                QMessageBox::critical(this, tr("Greška"), tr("Neuspješno brisanje kontakta: ") + query.lastError().text());
                break;
            }
        }

        if (success) {
            m_contactModel->loadContacts();
        }
    }
}


void EasyContacts::on_actionIzvoz_triggered() {
    try {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Izvoz kontakata"), "", tr("vCard datoteke (*.vcf)"));
        if (fileName.isEmpty()) {
            return;
        }

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Greška"), tr("Ne mogu otvoriti datoteku za pisanje: ") + file.errorString());
            return;
        }

        QTextStream out(&file);
        for (int row = 0; row < m_contactModel->m_model->rowCount(); ++row) {
            out << "BEGIN:VCARD\n";
            out << "VERSION:3.0\n";
            out << "FN:" << m_contactModel->m_model->data(m_contactModel->m_model->index(row, 1)).toString() << " " << m_contactModel->m_model->data(m_contactModel->m_model->index(row, 2)).toString() << "\n";
            out << "EMAIL:" << m_contactModel->m_model->data(m_contactModel->m_model->index(row, 3)).toString() << "\n";
            out << "TEL:" << m_contactModel->m_model->data(m_contactModel->m_model->index(row, 4)).toString() << "\n";
            out << "ADR:" << m_contactModel->m_model->data(m_contactModel->m_model->index(row, 5)).toString() << ";" << m_contactModel->m_model->data(m_contactModel->m_model->index(row, 6)).toString() << ";" << m_contactModel->m_model->data(m_contactModel->m_model->index(row, 7)).toString() << ";" << m_contactModel->m_model->data(m_contactModel->m_model->index(row, 8)).toString() << "\n";
            out << "END:VCARD\n";
        }

        file.close();
    QMessageBox::information(this, tr("Izvoz završen"), tr("Kontakti su uspješno izvezeni u vCard format."));
    } catch (const std::exception &e) {
        QMessageBox::critical(this, tr("Greška"), tr(e.what()));
        qDebug() << "Izuzetak uhvaćen:" << e.what();
        logError("Izuzetak uhvaćen: " + QString::fromStdString(e.what()));
    }
}

void EasyContacts::on_actionUvoz_triggered() {
    try {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Uvoz kontakata"), "", tr("vCard datoteke (*.vcf)"));
        if (fileName.isEmpty()) {
            return;
        }

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Greška"), tr("Ne mogu otvoriti datoteku za čitanje: ") + file.errorString());
            return;
        }

        QTextStream in(&file);
        QSqlQuery query;
        query.prepare("INSERT INTO contacts (firstName, lastName, email, phone, address, city, state, zipCode) "
                      "VALUES (:firstName, :lastName, :email, :phone, :address, :city, :state, :zipCode)");

        QString firstName, lastName, email, phone, address, city, state, zipCode;
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
                query.bindValue(":firstName", firstName);
                query.bindValue(":lastName", lastName);
                query.bindValue(":email", email);
                query.bindValue(":phone", phone);
                query.bindValue(":address", address);
                query.bindValue(":city", city);
                query.bindValue(":state", state);
                query.bindValue(":zipCode", zipCode);
                if (!query.exec()) {
                    QMessageBox::critical(this, tr("Greška"), tr("Neuspješan unos kontakta: ") + query.lastError().text());
                    return;
                }
            }
        }

        file.close();
        m_contactModel->loadContacts();
        QMessageBox::information(this, tr("Uvoz završen"), tr("Kontakti su uspješno uvezeni iz vCard formata."));
    } catch (const std::exception &e) {
        QMessageBox::critical(this, tr("Greška"), tr(e.what()));
        qDebug() << "Izuzetak uhvaćen:" << e.what();
        logError("Izuzetak uhvaćen: " + QString::fromStdString(e.what()));
    }
}


void EasyContacts::on_actionGeneri_i_Demo_podatke_triggered()
{
    QSqlQuery query;

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


    query.prepare("INSERT INTO contacts (firstName, lastName, email, phone, address, city, state, zipCode) "
                  "VALUES (:firstName, :lastName, :email, :phone, :address, :city, :state, :zipCode)");

    foreach (const QString &contact, demoContacts) {
        QStringList fields = contact.split(",");
        if (fields.size() == 8) {
            query.bindValue(":firstName", fields.at(0));
            query.bindValue(":lastName", fields.at(1));
            query.bindValue(":email", fields.at(2));
            query.bindValue(":phone", fields.at(3));
            query.bindValue(":address", fields.at(4));
            query.bindValue(":city", fields.at(5));
            query.bindValue(":state", fields.at(6));
            query.bindValue(":zipCode", fields.at(7));

            if (!query.exec()) {
                QMessageBox::critical(this, tr("Greška"), tr("Neuspješan unos kontakta: ") + query.lastError().text());
                return;
            }
        }
    }

    m_contactModel->loadContacts();
    QMessageBox::information(this, tr("Generisanje završeno"), tr("Demo kontakti su uspješno generisani."));

}


void EasyContacts::on_actionO_programu_triggered()
{
    if (!m_oProgramuForm) {
        m_oProgramuForm = new OProgramu(this);
    }
    m_oProgramuForm->exec();  // Koristi exec() umjesto show() da bi bio modalni
}


void EasyContacts::on_actionDokumentacija_triggered()
{
    QUrl url("https://maniaba.github.io/EasyContacts");
    QDesktopServices::openUrl(url);
}

void EasyContacts::logError(const QString &message) {
    QFile file("error_log.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << ": " << message << "\n";
        file.close();
    }
}


