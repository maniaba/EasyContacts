#include "contact.h"

Contact::Contact(const QString &firstName, const QString &lastName, const QString &email, const QString &phone,
                 const QString &address, const QString &city, const QString &state, const QString &zipCode)
    : m_firstName(firstName), m_lastName(lastName), m_email(email), m_phone(phone),
    m_address(address), m_city(city), m_state(state), m_zipCode(zipCode) {}

QString Contact::firstName() const {
    return m_firstName;
}

void Contact::setFirstName(const QString &firstName) {
    m_firstName = firstName;
}

QString Contact::lastName() const {
    return m_lastName;
}

void Contact::setLastName(const QString &lastName) {
    m_lastName = lastName;
}

QString Contact::email() const {
    return m_email;
}

void Contact::setEmail(const QString &email) {
    m_email = email;
}

QString Contact::phone() const {
    return m_phone;
}

void Contact::setPhone(const QString &phone) {
    m_phone = phone;
}

QString Contact::address() const {
    return m_address;
}

void Contact::setAddress(const QString &address) {
    m_address = address;
}

QString Contact::city() const {
    return m_city;
}

void Contact::setCity(const QString &city) {
    m_city = city;
}

QString Contact::state() const {
    return m_state;
}

void Contact::setState(const QString &state) {
    m_state = state;
}

QString Contact::zipCode() const {
    return m_zipCode;
}

void Contact::setZipCode(const QString &zipCode) {
    m_zipCode = zipCode;
}
