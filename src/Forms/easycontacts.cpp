#include "src/Forms/easycontacts.h"
#include "src/Model/contactmodel.h"
#include "src/Database/databasemanager.h"
#include "ui_easycontacts.h"
#include <QSqlError>
#include <QDebug>



EasyContacts::EasyContacts(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EasyContacts)
    , m_contactModel(new ContactModel(this))
    , m_contactStoreForm(nullptr)  // Inicijalizacija pointera
{
    ui->setupUi(this);

    // Postavi kolone i učitaj podatke
    m_contactModel->setupTableView(ui->tableView);
    m_contactModel->loadContacts();

    // Povezivanje akcije "Izradi novi kontakt" sa slotom
    connect(ui->actionIzradi_novi_kontakt, &QAction::triggered, this, &EasyContacts::on_actionIzradi_novi_kontakt_triggered);
}

EasyContacts::~EasyContacts() {
    DatabaseManager::closeDatabase();
    delete ui;
}

void EasyContacts::on_actionIzradi_novi_kontakt_triggered() {
    if (!m_contactStoreForm) {
        m_contactStoreForm = new ContactStoreForm(this);
    }
    m_contactStoreForm->show();
}
