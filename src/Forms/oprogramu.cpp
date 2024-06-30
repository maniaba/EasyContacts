#include "oprogramu.h"
#include "ui_oprogramu.h"

OProgramu::OProgramu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OProgramu)
{
    ui->setupUi(this);
}

OProgramu::~OProgramu()
{
    delete ui;
}
