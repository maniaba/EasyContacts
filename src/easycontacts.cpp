#include "easycontacts.h"
#include "./ui_easycontacts.h"

EasyContacts::EasyContacts(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EasyContacts)
{
    ui->setupUi(this);
}

EasyContacts::~EasyContacts()
{
    delete ui;
}
