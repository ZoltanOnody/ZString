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

size_t ZString::length() {
	return len;
}

char *ZString::value() {
    return data;
}
