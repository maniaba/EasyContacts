#ifndef CONTACTSTOREFORM_H
#define CONTACTSTOREFORM_H

#include <QDialog>

namespace Ui {
class ContactStoreForm;
}

class ContactStoreForm : public QDialog
{
    Q_OBJECT

public:
    explicit ContactStoreForm(QWidget *parent = nullptr);
    ~ContactStoreForm();

    void setContactData(const QString &firstName, const QString &lastName, const QString &email, const QString &phone,
                        const QString &address, const QString &city, const QString &state, const QString &zipCode, int id);


private slots:
    void onAccept();

    void on_buttonBox_accepted();

private:
    bool validateInput();
    void clearInputs();

    Ui::ContactStoreForm *ui;
    int m_contactId; // ID kontakta koji se uređuje
};

#endif // CONTACTSTOREFORM_H
