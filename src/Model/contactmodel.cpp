#include "contactmodel.h"
#include "qheaderview.h"
#include "src/Database/databasemanager.h"
#include "qsqlquery.h"
#include <QSqlError>
#include <QDebug>

ContactModel::ContactModel(QObject *parent)
    : QObject(parent), m_tableView(nullptr), m_model(new QSqlTableModel(this, DatabaseManager::getDatabase())) {
}

void ContactModel::setupTableView(QTableView *tableView) {
    m_tableView = tableView;

    // Isključivanje vertikalnih zaglavlja
    m_tableView->verticalHeader()->setVisible(false);

    // Omogućavanje selektovanja celog reda
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Onemogućavanje editovanja u tabeli
    m_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // Onemogućavanje editovanja
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_model->setTable("contacts");

    if (!m_model->select()) {
        qDebug() << "Failed to select data:" << m_model->lastError().text();
    } else {
        qDebug() << "SQL query executed by model:" << m_model->query().executedQuery();
    }



    m_model->setHeaderData(1, Qt::Horizontal, tr("First Name"));
    m_model->setHeaderData(2, Qt::Horizontal, tr("Last Name"));
    m_model->setHeaderData(3, Qt::Horizontal, tr("Email"));
    m_model->setHeaderData(4, Qt::Horizontal, tr("Phone"));
    m_model->setHeaderData(5, Qt::Horizontal, tr("Address"));
    m_model->setHeaderData(6, Qt::Horizontal, tr("City"));
    m_model->setHeaderData(7, Qt::Horizontal, tr("State"));
    m_model->setHeaderData(8, Qt::Horizontal, tr("Zip Code"));


    m_tableView->setModel(m_model);


    m_tableView->setColumnHidden(m_model->fieldIndex("id"), true);


    // Automatsko prilagođavanje širine kolona
    QHeaderView *header = m_tableView->horizontalHeader();
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
    qDebug() << "Table view model set:" << m_tableView->model()->rowCount();
}

void ContactModel::loadContacts() {
    // Možeš dodati dodatne funkcionalnosti za učitavanje specifičnih podataka ili filtriranje ovdje
    m_model->select();
}
