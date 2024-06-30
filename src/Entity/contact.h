#ifndef CONTACT_H
#define CONTACT_H

#include <QString>

class Contact {
public:
    Contact(const QString &firstName, const QString &lastName, const QString &email, const QString &phone,
            const QString &address, const QString &city, const QString &state, const QString &zipCode);

    QString firstName() const;
    void setFirstName(const QString &firstName);

    QString lastName() const;
    void setLastName(const QString &lastName);

    QString email() const;
    void setEmail(const QString &email);

    QString phone() const;
    void setPhone(const QString &phone);

    QString address() const;
    void setAddress(const QString &address);

    QString city() const;
    void setCity(const QString &city);

    QString state() const;
    void setState(const QString &state);

    QString zipCode() const;
    void setZipCode(const QString &zipCode);

private:
    QString m_firstName;
    QString m_lastName;
    QString m_email;
    QString m_phone;
    QString m_address;
    QString m_city;
    QString m_state;
    QString m_zipCode;
};

#endif // CONTACT_H
