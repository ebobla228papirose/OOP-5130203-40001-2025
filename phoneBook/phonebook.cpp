#include "phonebook.h"
#include "contact.h"
#include <fstream>  
#include <iostream>  
#include <algorithm> 

using namespace std;

PhoneBook::PhoneBook(const string& file) : filename(file) {
    loadFromFile();  
}

PhoneBook::~PhoneBook() {
    saveToFile(); 
}

void PhoneBook::addContact(const Contact& contact) {
    contacts.push_back(contact);  
    saveToFile(); 
}

void PhoneBook::removeContact(int index) {
    if (index >= 0 && index < contacts.size()) {
        contacts.erase(contacts.begin() + index);  
        saveToFile();                             
    }
}

void PhoneBook::editContact(int index, const Contact& newContact) {
    if (index >= 0 && index < contacts.size()) {
        contacts[index] = newContact; 
        saveToFile();                  
    }
}

const vector<Contact>& PhoneBook::getContacts() const {
    return contacts;  
}


void PhoneBook::displayContacts() const {
    if (contacts.empty()) {
        cout << "Телефонная книга пуста.\n";
        return;
    }

    for (size_t i = 0; i < contacts.size(); ++i) {
        cout << "=== Контакт #" << i + 1 << " ===\n";
        cout << contacts[i].toString() << "\n\n";
    }
}

void PhoneBook::searchContacts(const string& query) const {
    bool found = false;  
    string lowerQuery = toLower(query);  


    for (size_t i = 0; i < contacts.size(); ++i) {
        const Contact& contact = contacts[i];  
        
        
        string contactData = toLower(contact.getFirstName() + " " + 
                                    contact.getLastName() + " " + 
                                    contact.getMiddleName() + " " + 
                                    contact.getEmail());

        if (contactData.find(lowerQuery) != string::npos) {
            if (!found) {
                cout << "=== Результаты поиска ===\n";
                found = true;  
            }
            cout << "Контакт #" << i + 1 << ":\n";
            cout << contact.toString() << "\n\n";
        }
    }
    if (!found) {
        cout << "Контакты не найдены.\n";
    }
}

void PhoneBook::loadFromFile() {
    ifstream file(filename);  
    
    if (!file.is_open()) {
        return;
    }

    contacts.clear();  
    string line;       
    
    while (getline(file, line)) {
        if (!line.empty()) {
            try {
                contacts.push_back(Contact::fromFileString(line));
            } catch (const exception& e) {
                cerr << "Ошибка загрузки контакта: " << e.what() << endl;
            }
        }
    }
    
    file.close();  
}

void PhoneBook::saveToFile() {
    ofstream file(filename); 
    
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для записи.\n";
        return;
    }

    for (const auto& contact : contacts) {
        file << contact.toFileString() << "\n";  
    }
    
    file.close();  
}

string PhoneBook::toLower(const string& str) const {
    string result = str; 
    
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    
    return result;
}