#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include "contact.h"
#include <vector>
#include <string>

using namespace std;

class PhoneBook {
private:
    vector<Contact> contacts;  
    string filename;           

public:
    PhoneBook(const string& file = "phonebook.txt");

    ~PhoneBook();
    
    void addContact(const Contact& contact);      
    void removeContact(int index);                
    void editContact(int index, const Contact& newContact); 
    
    const vector<Contact>& getContacts() const;   
    void displayContacts() const;                 
    void searchContacts(const string& query) const; 
    
private:
    void loadFromFile();    
    void saveToFile();      
    
    
    string toLower(const string& str) const; // Преобразовать строку в нижний регистр
};

#endif 