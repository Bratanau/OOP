#include "seven.h"
#include <stdexcept>
#include <algorithm>


unsigned char Seven::charToDigit(char c) const {
    if (c >= '0' && c <= '7') return c - '0';
    throw std::invalid_argument("invalid character");
}

char Seven::digitToChar(unsigned char digit) const {
    if (digit < 8) return '0' + digit;
    throw std::out_of_range("invalid digit");
}

void Seven::validateString(const std::string& str) const {
    for (char c : str) {
        if (!(c >= '0' && c <= '7')) {
            throw std::invalid_argument("string contains non-base-7 character");
        }
    }
}

void Seven::removeLeadingZeros() {
    while (arraySize > 1 && dataArray[arraySize - 1] == 0) {
        arraySize--;
    }
}

Seven::Seven() : arraySize(1), dataArray(new unsigned char[1]) {
    dataArray[0] = 0;
}

Seven::Seven(const size_t& arraySize, unsigned char defaultValue) {
    if (defaultValue >= 7) {
        throw std::invalid_argument("digit must be < 7");
    }
    
    this->arraySize = arraySize;
    this->dataArray = new unsigned char[arraySize];
    
    for (size_t i = 0; i < arraySize; ++i) {
        this->dataArray[i] = defaultValue;
    }
}

Seven::Seven(const std::initializer_list<unsigned char>& initialValues) {
    if (initialValues.size() == 0) {
        throw std::invalid_argument("initializer list cant be empty");
    }
    
    arraySize = initialValues.size();
    dataArray = new unsigned char[arraySize];
    
    size_t index = 0;
    for (const auto& value : initialValues) {
        if (value >= 7) {
            throw std::invalid_argument("digit must be < 7");
        }
        dataArray[index++] = value;
    }
    
    std::reverse(dataArray, dataArray + arraySize);
    removeLeadingZeros();
}

Seven::Seven(const std::string& sourceString) {
    if (sourceString.empty()) {
        throw std::invalid_argument("empty string");
    }
    
    validateString(sourceString);
    
    arraySize = sourceString.size();
    dataArray = new unsigned char[arraySize];
    

    for (size_t i = 0; i < arraySize; ++i) {
        dataArray[i] = charToDigit(sourceString[arraySize - 1 - i]);
    }
    
    removeLeadingZeros();
}

Seven::Seven(const Seven& other) {
    arraySize = other.arraySize;
    dataArray = new unsigned char[arraySize];
    
    for (size_t i = 0; i < arraySize; ++i) {
        dataArray[i] = other.dataArray[i];
    }
}

Seven::Seven(Seven&& other) noexcept {
    arraySize = other.arraySize;
    dataArray = other.dataArray;
    
    other.arraySize = 0;
    other.dataArray = nullptr;
}

Seven Seven::add(const Seven& other) const {
    size_t maxSize = std::max(arraySize, other.arraySize);
    unsigned char* resultDigits = new unsigned char[maxSize + 1];
    unsigned char carry = 0;
    size_t resultSize = 0;

    for (size_t i = 0; i < maxSize || carry; ++i) {
        unsigned char a = (i < arraySize) ? dataArray[i] : 0;
        unsigned char b = (i < other.arraySize) ? other.dataArray[i] : 0;
        unsigned char sum = a + b + carry;
        
        carry = sum / 7;
        resultDigits[resultSize++] = sum % 7;
    }

    Seven result;
    delete[] result.dataArray;
    result.arraySize = resultSize;
    result.dataArray = resultDigits;
    
    return result;
}

Seven Seven::subtract(const Seven& other) const {
    if (less(other)) {
        throw std::logic_error("cannot subtract larger number from smaller");
    }

    unsigned char* resultDigits = new unsigned char[arraySize];
    unsigned char borrow = 0;
    size_t resultSize = arraySize;

    for (size_t i = 0; i < arraySize; ++i) {
        int a = dataArray[i];
        int b = (i < other.arraySize) ? other.dataArray[i] : 0;
        int diff = a - b - borrow;
        
        if (diff < 0) {
            diff += 7;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        resultDigits[i] = diff;
    }

    Seven result;
    delete[] result.dataArray;
    result.arraySize = resultSize;
    result.dataArray = resultDigits;
    result.removeLeadingZeros();
    
    return result;
}

Seven Seven::copy() const {
    return Seven(*this);
}

bool Seven::equals(const Seven& other) const {
    if (arraySize != other.arraySize) return false;
    
    for (size_t i = 0; i < arraySize; ++i) {
        if (dataArray[i] != other.dataArray[i]) return false;
    }
    
    return true;
}

bool Seven::less(const Seven& other) const {
    if (arraySize != other.arraySize) return arraySize < other.arraySize;
    
    for (size_t i = arraySize; i-- > 0;) {
        if (dataArray[i] != other.dataArray[i]) {
            return dataArray[i] < other.dataArray[i];
        }
    }
    
    return false;
}

bool Seven::greater(const Seven& other) const {
    return other.less(*this);
}

std::ostream& Seven::print(std::ostream& outputStream) const {
    for (size_t i = arraySize; i-- > 0;) {
        outputStream << digitToChar(dataArray[i]);
    }
    return outputStream;
}

Seven::~Seven() noexcept {
    if (dataArray != nullptr) {
        delete[] dataArray;
        dataArray = nullptr;
    }
    
    arraySize = 0;
}