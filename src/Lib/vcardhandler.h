#ifndef VCARDHANDLER_H
#define VCARDHANDLER_H

#include <QString>


class VCardHandler
{
public:
    static bool exportContacts(const QString &fileName);
    static bool importContacts(const QString &fileName);
};

#endif // VCARDHANDLER_H
