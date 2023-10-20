#pragma once
#include <string>
class User {
private:
    std::string m_name;
    std::string m_email;
    std::string m_position;
    std::string m_phoneNumber;
    std::string m_pictureLink;

public:
    User(std::string name, std::string email, std::string position, std::string phoneNumber, std::string pictureLink);
    std::string getName() const;
    std::string getEmail() const;
    std::string getPosition() const;
    std::string getPhoneNumber() const;
    std::string getPictureLink() const;
};

