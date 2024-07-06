#include "contact.h"

// Constructors
Contact::Contact(const QString &firstName, const QString &lastName, const QString &email, const QString &phone,
                 const QString &address, const QString &city, const QString &state, const QString &zipCode)
    : m_id(-1), m_firstName(firstName), m_lastName(lastName), m_email(email), m_phone(phone),
    m_address(address), m_city(city), m_state(state), m_zipCode(zipCode) {}

Contact::Contact(const int &id, const QString &firstName, const QString &lastName, const QString &email, const QString &phone,
                 const QString &address, const QString &city, const QString &state, const QString &zipCode)
    : m_id(id), m_firstName(firstName), m_lastName(lastName), m_email(email), m_phone(phone),
    m_address(address), m_city(city), m_state(state), m_zipCode(zipCode) {}

// Getters
int Contact::id() const {
    return m_id;
}

QString Contact::firstName() const {
    return m_firstName;
}

QString Contact::lastName() const {
    return m_lastName;
}

QString Contact::email() const {
    return m_email;
}

QString Contact::phone() const {
    return m_phone;
}

QString Contact::address() const {
    return m_address;
}

QString Contact::city() const {
    return m_city;
}

QString Contact::state() const {
    return m_state;
}

QString Contact::zipCode() const {
    return m_zipCode;
}

// Setters
void Contact::setId(const int &id) {
    m_id = id;
}

void Contact::setFirstName(const QString &firstName) {
    m_firstName = firstName;
}

void Contact::setLastName(const QString &lastName) {
    m_lastName = lastName;
}

void Contact::setEmail(const QString &email) {
    m_email = email;
}

void Contact::setPhone(const QString &phone) {
    m_phone = phone;
}

void Contact::setAddress(const QString &address) {
    m_address = address;
}

void Contact::setCity(const QString &city) {
    m_city = city;
}

void Contact::setState(const QString &state) {
    m_state = state;
}

void Contact::setZipCode(const QString &zipCode) {
    m_zipCode = zipCode;
}
