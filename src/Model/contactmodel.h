#ifndef CONTACTMODEL_H
#define CONTACTMODEL_H

#include <QObject>
#include <QSqlTableModel>
#include <QTableView>

class ContactModel : public QObject {
    Q_OBJECT
public:
    explicit ContactModel(QObject *parent = nullptr);
    void setupTableView(QTableView *tableView);
    void loadContacts();

private:
    QTableView *m_tableView;
    QSqlTableModel *m_model;
};

#endif // CONTACTMODEL_H
