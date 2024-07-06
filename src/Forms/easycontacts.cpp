#include "Forms/easycontacts.h"
#include "Lib/demodata.h"
#include "Model/contactmodel.h"
#include "qsqlquery.h"
#include "Forms/oprogramu.h"
#include "Lib/vcardhandler.h"
#include "Database/databasemanager.h"
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
    , m_proxyModel(new QSortFilterProxyModel(this)) // Inicijalizacija proxy modela
    , m_contactStoreForm(nullptr)
    , m_oProgramuForm(nullptr)
    , m_model(new QSqlTableModel(this, DatabaseManager::getDatabase()))
{
    ui->setupUi(this);

    // Postavi kolone i učitaj podatke
    this->setupTableView();
    this->loadContacts();

    // Povezivanje signala selekcije tabele sa slotom
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &EasyContacts::onSelectionChanged);
}

EasyContacts::~EasyContacts() {
    DatabaseManager::closeDatabase();
    delete ui;
}

void EasyContacts::loadContacts() {
    // Možeš dodati dodatne funkcionalnosti za učitavanje specifičnih podataka ili filtriranje ovdje
    m_model->select();
}

void EasyContacts::on_actionIzradi_novi_kontakt_triggered() {
    if (!m_contactStoreForm) {
        m_contactStoreForm = new ContactStoreForm(this);
    }
    m_contactStoreForm->exec();  // Koristi exec() umjesto show() da bi bio modalni
    qDebug() << "m_contactStoreForm exec()";
    this->loadContacts();
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
        this->loadContacts();
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
        bool success = true;

        foreach (const QModelIndex &index, selection) {
            int id = m_proxyModel->index(index.row(), 0).data().toInt();

            if (!ContactModel::deleteContact(id)) {
                success = false;
                QMessageBox::critical(this, tr("Greška"), tr("Neuspješno brisanje kontakta: ") + ContactModel::query().lastError().text());
                break;
            }
        }

        if (success) {
            this->loadContacts();
        }
    }
}


void EasyContacts::on_actionIzvoz_triggered() {

        QString fileName = QFileDialog::getSaveFileName(this, tr("Izvoz kontakata"), "", tr("vCard datoteke (*.vcf)"));
        if (!fileName.isEmpty()) {
            VCardHandler::exportContacts(fileName);
            this->loadContacts();
        }
}

void EasyContacts::on_actionUvoz_triggered() {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Uvoz kontakata"), "", tr("vCard datoteke (*.vcf)"));
        if (!fileName.isEmpty()) {
            VCardHandler::importContacts(fileName);
            this->loadContacts();
        }
}


void EasyContacts::on_actionGeneri_i_Demo_podatke_triggered()
{
    DemoData::generate(this);
    this->loadContacts();
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

void EasyContacts::setupTableView() {

    // Isključivanje vertikalnih zaglavlja
    ui->tableView->verticalHeader()->setVisible(false);

    // Omogućavanje selektovanja celog reda
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Onemogućavanje editovanja u tabeli
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // Onemogućavanje editovanja
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_model->setTable("contacts");

    if (!m_model->select()) {
        qDebug() << "Failed to select data:" << m_model->lastError().text();
    } else {
        qDebug() << "SQL query executed by model:" << m_model->query().executedQuery();
    }


    // Poveži model sa proxy modelom
    m_proxyModel->setSourceModel(m_model); // Koristi m_contactModel direktno
    m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive); // Postavi osjetljivost na velika/mala slova

    // Poveži proxy model sa table view
    ui->tableView->setModel(m_proxyModel);


    m_model->setHeaderData(1, Qt::Horizontal, tr("First Name"));
    m_model->setHeaderData(2, Qt::Horizontal, tr("Last Name"));
    m_model->setHeaderData(3, Qt::Horizontal, tr("Email"));
    m_model->setHeaderData(4, Qt::Horizontal, tr("Phone"));
    m_model->setHeaderData(5, Qt::Horizontal, tr("Address"));
    m_model->setHeaderData(6, Qt::Horizontal, tr("City"));
    m_model->setHeaderData(7, Qt::Horizontal, tr("State"));
    m_model->setHeaderData(8, Qt::Horizontal, tr("Zip Code"));


    ui->tableView->setModel(m_proxyModel);


    ui->tableView->setColumnHidden(m_model->fieldIndex("id"), true);


    // Automatsko prilagođavanje širine kolona
    QHeaderView *header = ui->tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Interactive);

    // Postavljanje stretch faktora za određene kolone
    header->setSectionResizeMode(5, QHeaderView::Stretch);  // Address
    header->setSectionResizeMode(6, QHeaderView::Stretch);  // City
    header->setSectionResizeMode(7, QHeaderView::Stretch);  // State

    // Ostale kolone da se automatski prilagođavaju
    header->setSectionResizeMode(1, QHeaderView::ResizeToContents);  // First Name
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents);  // Last Name
    header->setSectionResizeMode(3, QHeaderView::ResizeToContents);  // Email
    header->setSectionResizeMode(4, QHeaderView::ResizeToContents);  // Phone
    header->setSectionResizeMode(8, QHeaderView::ResizeToContents);  // Zip Code


    // Provjera prikaza table view
    qDebug() << "Table view model set:" << ui->tableView->model()->rowCount();
}


