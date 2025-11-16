#include "validator.h"
#include "contact.h"  
#include <sstream>
#include <iomanip>  
using namespace std;


bool Validator::validateName(const string& name) {
    string trimmedName = Contact::trim(name);
    
    
    if (trimmedName.empty()) {
        return false;
    }
    
    // Регулярное выражение для проверки:
    // ^ - начало строки
    // [a-zA-Zа-яА-Я] - должна начинаться с буквы (русской или английской)
    // [a-zA-Zа-яА-Я0-9\s-]* - может содержать буквы, цифры, пробелы и дефисы
    // [a-zA-Zа-яА-Я0-9]$ - должна заканчиваться буквой или цифрой (не дефисом)
    // |^[a-zA-Zа-яА-Я]$ - или состоять из одной буквы
    regex pattern("^[a-zA-Zа-яА-Я][a-zA-Zа-яА-Я0-9\\s-]*[a-zA-Zа-яА-Я0-9]$|^[a-zA-Zа-яА-Я]$");
    
    return regex_match(trimmedName, pattern);
}


bool Validator::validatePhone(const string& phone) {
    string trimmedPhone = Contact::trim(phone);
    
    // Регулярное выражение для российских номеров:
    // (\+7|8) - начинается с +7 или 8
    // [\\(]?[0-9]{3}[\\)]? - необязательные скобки вокруг кода города (3 цифры)
    // [0-9]{3} - следующие 3 цифры
    // [-]?[0-9]{2}[-]?[0-9]{2} - возможные дефисы между группами цифр
    regex pattern("^(\\+7|8)[\\(]?[0-9]{3}[\\)]?[0-9]{3}[-]?[0-9]{2}[-]?[0-9]{2}$");
    
    return regex_match(trimmedPhone, pattern);
}


bool Validator::validateEmail(const string& email) {
    string trimmedEmail = Contact::trim(email);
    
    // Регулярное выражение для email:
    // [a-zA-Z0-9._%+-]+ - имя пользователя (буквы, цифры, спецсимволы)
    // @ - символ собаки
    // [a-zA-Z0-9.-]+ - доменное имя
    // \\.[a-zA-Z]{2,} - доменная зона (минимум 2 буквы)
    regex pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    
    return regex_match(trimmedEmail, pattern);
}

bool Validator::validateDate(const string& date) {
    if (date.empty()) {
        return true;
    }
    
    regex pattern("^\\d{4}-\\d{2}-\\d{2}$");
    if (!regex_match(date, pattern)) {
        return false;
    }
    
    tm tm = {};  
    istringstream ss(date);
    ss >> get_time(&tm, "%Y-%m-%d");  
    
    if (ss.fail()) {
        return false;
    }
    
    // Проверка
    time_t inputDate = mktime(&tm);     // Преобразуем в секунды
    time_t currentTime = time(nullptr); // Текущее время в секундах
    
    return inputDate < currentTime;  
}