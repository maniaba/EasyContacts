#ifndef CONTACTMODEL_H
#define CONTACTMODEL_H

#include <QObject>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QTableView>

class ContactModel : public QObject {
    Q_OBJECT
public:
    explicit ContactModel(QObject *parent = nullptr);
    void setupTableView(QTableView *tableView, QSortFilterProxyModel *m_proxyModel);
    void loadContacts();
    QSqlTableModel *m_model;

private:
    QTableView *m_tableView;
};

#endif // CONTACTMODEL_H
