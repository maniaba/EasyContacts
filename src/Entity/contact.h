#ifndef CONTACT_H
#define CONTACT_H

#include <QString>

class Contact {
public:
    // Constructors
    Contact(const QString &firstName, const QString &lastName, const QString &email, const QString &phone,
            const QString &address, const QString &city, const QString &state, const QString &zipCode);

    Contact(const int &id, const QString &firstName, const QString &lastName, const QString &email, const QString &phone,
            const QString &address, const QString &city, const QString &state, const QString &zipCode);

    // Getters
    int id() const;
    QString firstName() const;
    QString lastName() const;
    QString email() const;
    QString phone() const;
    QString address() const;
    QString city() const;
    QString state() const;
    QString zipCode() const;

    // Setters
    void setId(const int &id);
    void setFirstName(const QString &firstName);
    void setLastName(const QString &lastName);
    void setEmail(const QString &email);
    void setPhone(const QString &phone);
    void setAddress(const QString &address);
    void setCity(const QString &city);
    void setState(const QString &state);
    void setZipCode(const QString &zipCode);

private:
    int m_id;
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
