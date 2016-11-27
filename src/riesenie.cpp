#include <iostream>
#include <cstring>

#include "riesenie.h"

using namespace std;


// Uloha 1.
ZString::ZString(const char *data) {
    size_t len = strlen(data);
    this->len = len;
    this->data = new char[len+1];
    strcpy(this->data, data);
}

char ZString::operator[](int i) const {
    if (i >= len) {
        throw std::out_of_range("Index out of range!");
    }
    return data[i];
}

size_t ZString::length() {
	return len;
}

char *ZString::value() {
    return data;
}

ZString ZString::operator+(ZString obj) {
    size_t new_length = len + obj.length();

    char *tmp = new char[new_length + 1];
    for (int i = 0; i < len; i++) {
        tmp[i] = data[i];
    }
    for (int i = 0; i < obj.length(); i++) {
        tmp[len + i] = obj[i];
    }
    tmp[new_length] = '\0';

    ZString new_obj(tmp);

    return new_obj;
}

void ZString::operator+=(ZString obj) {
    ZString new_obj = *this + obj;
    *this = new_obj;
}

ZString ZString::operator*(int mul) {
    if (mul < 0) {
        throw std::invalid_argument("Multiplication cannot be negative!");
    }

    ZString ans;
    for (int i = 0; i < mul; i++) {
        ans += *this;
    }

    return ans;
}


void ZString::operator*=(int mul) {
    ZString new_obj = *this * mul;
    *this = new_obj;
}