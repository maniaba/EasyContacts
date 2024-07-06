#ifndef EASYCONTACTS_H
#define EASYCONTACTS_H

#include "Forms/contactstoreform.h"
#include "Forms/oprogramu.h"
#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QSqlTableModel>


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

    void on_lineEdit_pretraga_textChanged(const QString &arg1);

    void on_pushButton_uredi_clicked();

    void onSelectionChanged();

    void on_pushButton_obrisati_clicked();

    void on_actionUvoz_triggered();

    void on_actionIzvoz_triggered();

    void on_actionGeneri_i_Demo_podatke_triggered();

    void on_actionO_programu_triggered();

    void on_actionDokumentacija_triggered();

private:
    Ui::EasyContacts *ui;
    QSortFilterProxyModel *m_proxyModel; // Proxy model za filtriranje
    ContactStoreForm *m_contactStoreForm;
    OProgramu *m_oProgramuForm;
    QSqlTableModel *m_model;

    void setupTableView();
    void loadContacts();

};

#endif // EASYCONTACTS_H
