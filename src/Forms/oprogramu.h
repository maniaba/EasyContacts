#ifndef OPROGRAMU_H
#define OPROGRAMU_H

#include <QDialog>

namespace Ui {
class OProgramu;
}

class OProgramu : public QDialog
{
    Q_OBJECT

public:
    explicit OProgramu(QWidget *parent = nullptr);
    ~OProgramu();

private:
    Ui::OProgramu *ui;
};

#endif // OPROGRAMU_H
