#include "contactstoreform.h"
#include "ui_contactstoreform.h"

ContactStoreForm::ContactStoreForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ContactStoreForm)
{
    ui->setupUi(this);
}

ContactStoreForm::~ContactStoreForm()
{
    delete ui;
}
