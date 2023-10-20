#include "User.h"

User::User(std::string name, std::string email, std::string position, std::string phoneNumber, std::string pictureLink) :
    m_name(name),
    m_email(email),
    m_position(position),
    m_phoneNumber(phoneNumber),
    m_pictureLink(pictureLink)
{
}

std::string User::getName() const {
    return m_name;
}

std::string User::getEmail() const {
    return m_email;
}

std::string User::getPosition() const {
    return m_position;
}

std::string User::getPhoneNumber() const {
    return m_phoneNumber;
}

std::string User::getPictureLink() const
{
    return m_pictureLink;
}
