# Makefile - для простой сборки программы
CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = phonebook
OBJS = main.o contact.o validator.o phonebook.o

# Основная цель сборки
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Компиляция каждого .cpp файла
main.o: main.cpp phonebook.h contact.h validator.h
	$(CXX) $(CXXFLAGS) -c main.cpp

contact.o: contact.cpp contact.h
	$(CXX) $(CXXFLAGS) -c contact.cpp

validator.o: validator.cpp validator.h contact.h
	$(CXX) $(CXXFLAGS) -c validator.cpp

phonebook.o: phonebook.cpp phonebook.h contact.h
	$(CXX) $(CXXFLAGS) -c phonebook.cpp

# Очистка собранных файлов
clean:
	rm -f $(OBJS) $(TARGET)

# Запуск программы
run: $(TARGET)
	./$(TARGET)

.PHONY: clean run