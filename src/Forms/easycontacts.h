#ifndef EASYCONTACTS_H
#define EASYCONTACTS_H

#include "src/Forms/contactstoreform.h"
#include "src/Forms/oprogramu.h"
#include "src/Model/contactmodel.h"
#include <QMainWindow>
#include <QSortFilterProxyModel>


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
    ContactModel *m_contactModel;
    QSortFilterProxyModel *m_proxyModel; // Proxy model za filtriranje
    ContactStoreForm *m_contactStoreForm;
    OProgramu *m_oProgramuForm;

    void logError(const QString &message);

};

#endif // EASYCONTACTS_H
