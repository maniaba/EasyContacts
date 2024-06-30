#ifndef EASYCONTACTS_H
#define EASYCONTACTS_H

#include "src/Forms/contactstoreform.h"
#include "src/Model/contactmodel.h"
#include <QMainWindow>


namespace Ui {
class EasyContacts;
}

class EasyContacts : public QMainWindow
{
    Q_OBJECT

public:
    explicit EasyContacts(QWidget *parent = nullptr);
    ~EasyContacts();

private slots:
    void on_actionIzradi_novi_kontakt_triggered();

private:
    Ui::EasyContacts *ui;
    ContactModel *m_contactModel;
    ContactStoreForm *m_contactStoreForm;
};

#endif // EASYCONTACTS_H
