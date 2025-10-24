#pragma once

#include <string>
#include <iostream>

class Seven {
public:
    // === КОНСТРУКТОРЫ ===
    
    // Конструктор по умолчанию
    Seven();
    
    // Конструктор с заполнением (размер + значение по умолчанию)
    Seven(const size_t& arraySize, unsigned char defaultValue = 0);
    
    // Конструктор из списка инициализации (C++11)
    Seven(const std::initializer_list<unsigned char>& initialValues);
    
    // Конструктор из строки
    Seven(const std::string& sourceString);
    
    // === КОПИРУЮЩИЕ И ПЕРЕМЕЩАЮЩИЕ ОПЕРАЦИИ ===
    
    // Копирующий конструктор (Правило пяти)
    Seven(const Seven& other);
    
    // Перемещающий конструктор (C++11) - Правило пяти
    Seven(Seven&& other) noexcept;

    // === ОПЕРАЦИИ С МАССИВАМИ ===
    
    // Сложение массивов (создает новый массив)
    Seven add(const Seven& other) const;
    
    // Вычитание массивов (может выбрасывать исключение)
    Seven subtract(const Seven& other) const;

    Seven copy() const;
    
    // Сравнение массивов по размеру
    bool equals(const Seven& other) const;
    bool less(const Seven& other) const;
    bool greater(const Seven& other) const;
    
    // Вывод массива в поток
    std::ostream& print(std::ostream& outputStream) const;

    // === ДЕСТРУКТОР ===
    
    // Виртуальный деструктор (Правило пяти)
    virtual ~Seven() noexcept;

private:
    // === ДАННЫЕ-ЧЛЕНЫ ===
    
    size_t arraySize;           // Размер массива
    unsigned char* dataArray;   // Указатель на динамический массив

    unsigned char charToDigit(char c) const;
    char digitToChar(unsigned char digit) const;
    void validateString(const std::string& str) const;
    void removeLeadingZeros();
};