#ifndef CONTACT_H  
#define CONTACT_H

#include <string>
#include <vector>
using namespace std;
class Contact {
private:
    string firstName;      
    string lastName;       
    string middleName;     
    string address;        
    string birthDate;      
    string email;          
    vector<string> phoneNumbers; 
public:
    Contact(const std::string& fName, const std::string& lName, 
            const std::string& email, const std::string& phone);
    //методы получения
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getMiddleName() const;
    std::string getAddress() const;
    std::string getBirthDate() const;
    std::string getEmail() const;
    std::vector<std::string> getPhoneNumbers() const;
    //методы добавления
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setMiddleName(const std::string& middleName);
    void setAddress(const std::string& adrs);
    void setBirthDate(const std::string& date);
    void setEmail(const std::string& mail);
    //методы телефон
    void addPhoneNumber(const std::string& phone);
    void removePhoneNumber(int index);

    // Вспомогательные методы
    static std::string trim(const std::string& str);  // Удаляет лишние пробелы
    std::string toString() const;                     // Для красивого вывода
    std::string toFileString() const;                 // Для сохранения в файл
    static Contact fromFileString(const std::string& fileString); // Для загрузки из файла
};
#endif
