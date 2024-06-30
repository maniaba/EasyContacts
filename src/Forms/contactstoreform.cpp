#include "contactstoreform.h"
#include "ui_contactstoreform.h"
#include "src/Database/databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>

ContactStoreForm::ContactStoreForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ContactStoreForm)
    , m_contactId(-1) // Inicijalizacija ID-a sa -1
{
    ui->setupUi(this);

    // Brisanje standardnog signala na slot, kako bi sprijecio zatvaranje dialoga prilokom validacije
    ui->buttonBox->disconnect(SIGNAL(accepted()), this);
    ui->buttonBox->disconnect(SIGNAL(rejected()), this);

    // Povezivanje signala na slot
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ContactStoreForm::onAccept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &ContactStoreForm::reject);

}

ContactStoreForm::~ContactStoreForm()
{
    delete ui;
}

void ContactStoreForm::onAccept() {
    if (validateInput()) {
        QSqlDatabase db = DatabaseManager::getDatabase();
        if (!db.isValid() || !db.isOpen()) {
            qDebug() << "Database not open or invalid";
            QMessageBox::critical(this, tr("Error"), tr("Database not open or invalid"));
            return;
        }

        QString sql;

        if (m_contactId == -1) {
            sql = "INSERT INTO contacts (firstName, lastName, email, phone, address, city, state, zipCode) "
                  "VALUES (:firstName, :lastName, :email, :phone, :address, :city, :state, :zipCode)";
        } else {
            sql = "UPDATE contacts SET firstName=:firstName, lastName=:lastName, email=:email, phone=:phone, "
                  "address=:address, city=:city, state=:state, zipCode=:zipCode WHERE id=:id";

        }

        QSqlQuery query(db);

        if (!query.prepare(sql)) {
            qDebug() << "Failed to prepare query:" << query.lastError();
            QMessageBox::critical(this, tr("Error"), tr("Failed to prepare query: ") + query.lastError().text());
            return;
        }

        if (m_contactId > 0) {
            // Ažuriranje postojećeg kontakta
            query.bindValue(":id", m_contactId);
        }

        query.bindValue(":firstName", ui->lineEdit_ime->text());
        query.bindValue(":lastName", ui->lineEdit_prezime->text());
        query.bindValue(":email", ui->lineEdit_email->text());
        query.bindValue(":phone", ui->lineEdit_telefon->text());
        query.bindValue(":address", ui->textEdit_adresa->toPlainText());
        query.bindValue(":city", ui->lineEdit_grad->text());
        query.bindValue(":state", ui->lineEdit_drzava->text());
        query.bindValue(":zipCode", ui->lineEdit_postBroj->text());

        if (query.exec()) {
            qDebug() << "Query executed successfully";
            if (m_contactId > 0) {
                QMessageBox::information(this, tr("Success"), tr("Kontakt ažuriran."));
            } else{
                QMessageBox::information(this, tr("Success"), tr("Kontakt uspješno dodan."));
            }
            clearInputs();
            accept(); // Zatvara dijalog
        } else {
            qDebug() << "Failed to execute query:" << query.lastError();
            QMessageBox::critical(this, tr("Error"), tr("Failed to add contact: ") + query.lastError().text());
        }
    }
}

bool ContactStoreForm::validateInput() {
    if (ui->lineEdit_ime->text().isEmpty() ||
        ui->lineEdit_prezime->text().isEmpty() ||
        ui->lineEdit_telefon->text().isEmpty()) {
        QMessageBox::warning(this, tr("Validation Error"), tr("Name, Last Name, and Phone are required fields."));
        return false;
    }

    static const QRegularExpression emailRegex("^\\S+@\\S+\\.\\S+$");
    if (!ui->lineEdit_email->text().isEmpty() && !emailRegex.match(ui->lineEdit_email->text()).hasMatch()) {
        QMessageBox::warning(this, tr("Validation Error"), tr("Please enter a valid email address."));
        return false;
    }

    static const QRegularExpression phoneRegex("^\\+?[0-9]*$");
    if (!phoneRegex.match(ui->lineEdit_telefon->text()).hasMatch()) {
        QMessageBox::warning(this, tr("Validation Error"), tr("Please enter a valid phone number."));
        return false;
    }

    return true;
}

void ContactStoreForm::clearInputs() {
    ui->lineEdit_ime->clear();
    ui->lineEdit_prezime->clear();
    ui->lineEdit_email->clear();
    ui->lineEdit_telefon->clear();
    ui->textEdit_adresa->clear();
    ui->lineEdit_grad->clear();
    ui->lineEdit_drzava->clear();
    ui->lineEdit_postBroj->clear();
    m_contactId = -1; // Resetuj ID na -1
}

void ContactStoreForm::setContactData(const QString &firstName, const QString &lastName, const QString &email, const QString &phone,
                                      const QString &address, const QString &city, const QString &state, const QString &zipCode, int id)
{
    ui->lineEdit_ime->setText(firstName);
    ui->lineEdit_prezime->setText(lastName);
    ui->lineEdit_email->setText(email);
    ui->lineEdit_telefon->setText(phone);
    ui->textEdit_adresa->setPlainText(address);
    ui->lineEdit_grad->setText(city);
    ui->lineEdit_drzava->setText(state);
    ui->lineEdit_postBroj->setText(zipCode);
    m_contactId = id; // Postavi ID kontakta koji se uređuje
}

