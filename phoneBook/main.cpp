#include <iostream>
#include "phonebook.h"
#include "validator.h"

using namespace std;

string inputWithValidation(const string& prompt, 
                          bool (*validator)(const string&),
                          const string& errorMessage = "Неверный формат. Попробуйте снова: ") {
    string input;
    while (true) {
        cout << prompt;  
        getline(cin, input);  
        
        if (validator(input)) {
            return Contact::trim(input);  
        }
        cout << errorMessage << endl;  
    }
}


void addContactMenu(PhoneBook& phoneBook) {
    cout << "=== Добавление нового контакта ===\n";
    
    string firstName = inputWithValidation(
        "Имя*: ", 
        Validator::validateName,
        "Имя должно начинаться с буквы и содержать только буквы, цифры, дефис и пробел."
    );
    
    string lastName = inputWithValidation(
        "Фамилия*: ", 
        Validator::validateName,
        "Фамилия должна начинаться с буквы и содержать только буквы, цифры, дефис и пробел."
    );
    
    string email = inputWithValidation(
        "Email*: ", 
        Validator::validateEmail,
        "Неверный формат email."
    );
    
    string phone = inputWithValidation(
        "Телефон*: ", 
        Validator::validatePhone,
        "Неверный формат телефона. Примеры: +78121234567, 88121234567, +7(812)1234567"
    );
    
    Contact contact(firstName, lastName, email, phone);
    
    cout << "Отчество (необязательно): ";
    string middleName;
    getline(cin, middleName);
    if (!middleName.empty() && Validator::validateName(middleName)) {
        contact.setMiddleName(middleName);
    }
    
    cout << "Адрес (необязательно): ";
    string address;
    getline(cin, address);
    contact.setAddress(address);
    
    string birthDate = inputWithValidation(
        "Дата рождения (ГГГГ-ММ-ДД, необязательно): ", 
        [](const string& date) { 
            return date.empty() || Validator::validateDate(date); 
        },
        "Неверный формат даты или дата в будущем. Используйте формат ГГГГ-ММ-ДД."
    );
    contact.setBirthDate(birthDate);
    
    char addMore;
    do {
        cout << "Добавить еще один телефон? (y/n): ";
        cin >> addMore;
        cin.ignore();  
        
        if (addMore == 'y' || addMore == 'Y') {
            string additionalPhone = inputWithValidation(
                "Дополнительный телефон: ", 
                Validator::validatePhone,
                "Неверный формат телефона."
            );
            contact.addPhoneNumber(additionalPhone);
        }
    } while (addMore == 'y' || addMore == 'Y');
    
    phoneBook.addContact(contact);
    cout << "Контакт успешно добавлен!\n";
}


void mainMenu() {
    PhoneBook phoneBook;  
    int choice;           
    
    do {
        cout << "\n=== ТЕЛЕФОННЫЙ СПРАВОЧНИК ===\n";
        cout << "1. Показать все контакты\n";
        cout << "2. Добавить контакт\n";
        cout << "3. Удалить контакт\n";
        cout << "4. Поиск контактов\n";
        cout << "5. Выход\n";
        cout << "Выберите действие: ";
        
        cin >> choice;   
        cin.ignore();     
        
        switch (choice) {
            case 1:  
                phoneBook.displayContacts();
                break;
                
            case 2:  
                addContactMenu(phoneBook);
                break;
                
            case 3:  
                if (phoneBook.getContacts().empty()) {
                    cout << "Телефонная книга пуста.\n";
                } else {
                    phoneBook.displayContacts();  
                    cout << "Введите номер контакта для удаления: ";
                    int index;
                    cin >> index;
                    cin.ignore();
                    phoneBook.removeContact(index - 1);  
                    cout << "Контакт удален.\n";
                }
                break;
                
            case 4: {
                cout << "Введите строку для поиска: ";
                string query;
                getline(cin, query);
                phoneBook.searchContacts(query);
                break;
            }  
            case 5:  
                cout << "Выход из программы.\n";
                break;
                
            default:  
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 5);  
}


int main() {
    setlocale(LC_ALL, "Russian"); 
    mainMenu();                   
    return 0;                     
}