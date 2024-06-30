#ifndef EASYCONTACTS_H
#define EASYCONTACTS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class EasyContacts;
}
QT_END_NAMESPACE

class EasyContacts : public QMainWindow
{
    Q_OBJECT

public:
    EasyContacts(QWidget *parent = nullptr);
    ~EasyContacts();

private:
    Ui::EasyContacts *ui;
};
#endif // EASYCONTACTS_H
