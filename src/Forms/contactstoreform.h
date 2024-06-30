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

private:
    Ui::ContactStoreForm *ui;
};

#endif // CONTACTSTOREFORM_H
