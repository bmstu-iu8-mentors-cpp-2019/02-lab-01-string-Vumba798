// Copyright 2020 Vumba798
// Created by alexey on 16.03.2020.
//
#include "string.hpp"

String::~String(){
    if (Data != nullptr){
        delete[] Data;
        Data = nullptr;
    }
}

String::String(){
    Data = nullptr;
}

String::String(const String &rhs){
    if (this != &rhs) {
        size_t len = rhs.Size();
        Data = new char[len + 1];
        for (size_t i = 0; i < len; ++i) {
            Data[i] = rhs.Data[i];
        }
        Data[rhs.Size()] = 0;
    }
}

String::String(const char* data){
    size_t len = 0;
    while (data[len]) {
        ++len;
    }
    Data = new char[len + 1];
    for (size_t i = 0; i < len; ++i){
        Data[i] = data[i];
    }
    Data[len] = 0;
}

String& String::operator=(const String& rhs){
    if (&rhs != this) {
        if (Data != nullptr) { // Очищаем память если она не пуста
            delete[] Data;
        }
        size_t len = rhs.Size();
        Data = new char[len + 1];
        for (size_t i = 0; i < len; ++i) {
            Data[i] = rhs.Data[i];
        }
        Data[len] = 0;
    }
    return *this;
}

String& String::operator+=(const String& rhs){
    // модификатор static позволяет переменной пережить выход из блока  
    size_t len = Size();
    size_t rhsLen = rhs.Size();
    size_t newLen = len + rhsLen;
    char* newStr = new char[newLen + 1];
    for (size_t i = 0; i < len; ++i){
        newStr[i] = Data[i];
    }
    for (size_t j = 0; j < newLen; ++j){
        newStr[j + len] = rhs.Data[j];
    }
    newStr[newLen] = 0;
    if (Data != nullptr) {
        delete[] Data;
    }
    Data = newStr;
    return *this;
}

String& String::operator*=(unsigned int m){
    size_t len = Size();
    static char* new_str = new char[len * m + 1];
    for (unsigned int i = 0; i < m; ++i) {
        for (size_t j = 0; j < len; ++j) {
            new_str[j + len * i] = Data[j];
        }
    }
    new_str[len * m] = 0;
    if (Data != nullptr) {
        delete[] Data;
    }
    Data = new_str;
    return *this;
}

bool String::operator==(const String &rhs) const {
    size_t len = Size();
    size_t rhsLen = rhs.Size();
    if (len == rhsLen){
        for (size_t i = 0; i < len; ++i){
            if (Data[i] != rhs[i]){
                return false;
            }
        }
        return true;
    }else{
        return false;
    }
}


bool String::operator<(const String& rhs) const{
    size_t len = Size();
    size_t rhsLen = rhs.Size();
    size_t minLen = len < rhsLen ? len : rhsLen;
    for (size_t i = 0; i < minLen; ++i){
        if (Data[i] < rhs.Data[i]){
            return true;
        }else{
            continue;
        }
    }
    if (minLen == len){
        return true;
    }else{
        return false;
    }
}

size_t String::Find(const String& substr) const {
    size_t len = Size();
    size_t substrLen = substr.Size();
    for (size_t i = 0; i < len - substrLen + 1; ++i) {
        if (substr.Data[0] == Data[i]) {
            for (size_t j = 0; j < substrLen; ++j) {
                if (substr.Data[j] != Data[i + j]) {
                    break;
                }else if (j+ 1 == substrLen){
                    return i;
                }
            }
        }
        continue;
    }
    return -1;
}



void String::Replace(char oldSymbol, char newSymbol) {
    size_t len = Size();
    for (size_t i = 0; i < len; ++i){
        if (Data[i] == oldSymbol){
            Data[i] = newSymbol;
        }
    }
}

size_t String::Size() const{
    size_t len = 0;
    if (Data != nullptr) {
        while (Data[len]) {
            ++len;
        }
    }
    return len;
}

bool String::Empty() const{
    if (Size() == 0){
        return true;
    }else{
        return false;
    }
}

char String::operator[](size_t index) const {
    char ch = Data[index];
    return ch;
}

char& String::operator[](size_t index) {
    return Data[index];
}

void String::LTrim(char symbol) {
    size_t index = 0;
    size_t len = Size();
    for (size_t i = 0; i < len; ++i){
        if (Data[i] == symbol){
            ++index;
        }else{
            break;
        }
    }
    if  (index!= len - 1){
        static char* newStr = new char[len - index];
        for (size_t j = 0; j < len; ++j){
           newStr[j] = Data[index + j];
        }
        newStr[len - index] = 0;
        delete[] Data;
        Data = newStr;
    }
}

void String::RTrim(char symbol) {
    size_t len = Size();
    size_t index = len - 1;
    for (size_t i = len - 1; i != 0; --i){
        if (Data[i] != symbol){
            break;
        }else{
            --index;
        }
    }
    char* tmp = new char[index + 2];
    for (size_t j = 0; j <= index; ++j){
        tmp[j] = Data[j];
    }
    tmp[index + 1] = 0;
    delete[] Data;
    Data = tmp;
}

void String::swap(String &oth) {
    char* tmpStr = Data;
    Data = oth.Data;
    oth.Data = tmpStr;
}

String operator+(const String &a, const String &b){
    size_t aLen = a.Size();
    size_t bLen = b.Size();
    static char* newData = new char[aLen + bLen + 1];
    for (size_t i = 0; i < aLen; ++i){
        newData[i] = a[i];
    }
    for (size_t j = 0; j < bLen; ++j){
        newData[aLen + j] = b[j];
    }
    newData[aLen + bLen] = 0;
    static String newString(newData);
    return newString;
}

String operator*(const String &a, unsigned int b){
    size_t len = a.Size();
    size_t newLen = len * b;
    static char* newData = new char[newLen + 1];
    for (size_t i = 0; i < b; ++i){
        for (size_t j = 0; j < len; ++j){
            newData[(i * len) + j] = a[j];
        }
    }
    static String newString(newData);
    return newString;
}

bool operator!=(const String &a, const String &b){
   return a != b;
}

bool operator>(const String &a, const String &b){
    return a > b;
}

std::ostream& operator<<(std::ostream& out, const String& str){
    out << str.Data;
    return out;
}
