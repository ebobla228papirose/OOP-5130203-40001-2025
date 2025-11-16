#include "contact.h"
#include <sstream>
#include <algorithm>

Contact::Contact(const std::string& fName, const std::string& lName, 
                 const std::string& email, const std::string& phone)
    : firstName(trim(fName)), lastName(trim(lName)), email(trim(email)) {
    addPhoneNumber(phone);
}

string Contact::getFirstName() const { 
    return firstName; 
}

std::string Contact::getLastName() const { 
    return lastName; 
}

std::string Contact::getMiddleName() const { 
    return middleName; 
}

std::string Contact::getAddress() const { 
    return address; 
}

std::string Contact::getBirthDate() const { 
    return birthDate; 
}

std::string Contact::getEmail() const { 
    return email; 
}

std::vector<std::string> Contact::getPhoneNumbers() const { 
    return phoneNumbers; 
}

void Contact::setFirstName(const std::string& firstName) { 
    this->firstName = trim(firstName); 
}

void Contact::setLastName(const std::string& lastName) { 
    this->lastName = trim(lastName); 
}

void Contact::setMiddleName(const std::string& middleName) { 
    this->middleName = trim(middleName); 
}

void Contact::setAddress(const std::string& adrs) { 
    this->address = trim(adrs); 
}

void Contact::setBirthDate(const std::string& birthDate) { 
    this->birthDate = trim(birthDate); 
}

void Contact::setEmail(const std::string& email) { 
    this->email = trim(email); 
}


void Contact::addPhoneNumber(const string& phone) {
    string trimmed = trim(phone);  // Очистка номера от пробелов
    if (!trimmed.empty()) {        // Если номер не пустой
        phoneNumbers.push_back(trimmed); // Добавляем в конец списка
    }
}


void Contact::removePhoneNumber(int index) {
    if (index >= 0 && index < phoneNumbers.size()) {
        phoneNumbers.erase(phoneNumbers.begin() + index);
    }
}
//удаление лишних пробелов
string Contact::trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");  
    size_t end = str.find_last_not_of(" \t\n\r");
    return (start == string::npos) ? "" : str.substr(start, end - start + 1);
}


string Contact::toString() const {
    stringstream ss;  
    
    ss << "Имя: " << firstName << "\n"
       << "Фамилия: " << lastName << "\n"
       << "Отчество: " << (middleName.empty() ? "Не указано" : middleName) << "\n"
       << "Адрес: " << (address.empty() ? "Не указан" : address) << "\n"
       << "Дата рождения: " << (birthDate.empty() ? "Не указана" : birthDate) << "\n"
       << "Email: " << email << "\n"
       << "Телефоны: ";
    
    if (phoneNumbers.empty()) {
        ss << "Не указаны";
    } else {
        for (size_t i = 0; i < phoneNumbers.size(); ++i) {
            ss << phoneNumbers[i];
            if (i < phoneNumbers.size() - 1) ss << ", ";
        }
    }
    
    return ss.str();  
}

string Contact::toFileString() const {
    stringstream ss;

    ss << firstName << "|" << lastName << "|" << middleName << "|"
       << address << "|" << birthDate << "|" << email << "|";
    
    for (size_t i = 0; i < phoneNumbers.size(); ++i) {
        ss << phoneNumbers[i];
        if (i < phoneNumbers.size() - 1) ss << ";";
    }
    
    return ss.str();
}


Contact Contact::fromFileString(const string& fileString) {
    vector<string> parts; 
    stringstream ss(fileString);
    string part;  
    
    while (getline(ss, part, '|')) {
        parts.push_back(part); 
    }
    
    if (parts.size() < 6) {
        throw invalid_argument("Неверный формат строки контакта");
    }
    
    Contact contact(parts[0], parts[1], parts[5], "");
    
    contact.setMiddleName(parts[2]);
    contact.setAddress(parts[3]);
    contact.setBirthDate(parts[4]);
    
    if (parts.size() > 6) {
        stringstream phones(parts[6]);  
        string phone;  
        
        while (getline(phones, phone, ';')) {
            contact.addPhoneNumber(phone);
        }
    }
    
    return contact;
}
