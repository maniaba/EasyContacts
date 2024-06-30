#include "easycontacts.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EasyContacts w;
    w.show();
    return a.exec();
}
