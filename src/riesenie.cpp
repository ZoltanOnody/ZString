#include <iostream>
#include <cstring>

#include "riesenie.h"

using namespace std;


// Uloha 1.
ZString::ZString(char const *data) {
    size_t len = strlen(data);
    this->len = len;
    this->data = new char[len+1];
    strcpy(this->data, data);
}

size_t ZString::length() const {
	return len;
}

char *ZString::value() const {
    return data;
}

ZString ZString::operator+(ZString const obj) const {
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

void ZString::operator+=(ZString const obj) {
    ZString new_obj = *this + obj;
    *this = new_obj;
}

ZString ZString::operator*(int const mul) const {
    if (mul < 0) {
        throw std::invalid_argument("Multiplication cannot be negative!");
    }

    ZString ans;
    for (int i = 0; i < mul; i++) {
        ans += *this;
    }

    return ans;
}

void ZString::operator*=(int const mul) {
    ZString new_obj = *this * mul;
    *this = new_obj;
}

bool ZString::operator<(ZString const obj) const {
    for (int i = 0; i < min(len, obj.length()); i++) {
        if ((*this)[i] < obj[i]) {
            return true;
        } else if ((*this)[i] > obj[i]) {
            return false;
        }
    }

    return len < obj.length();
}

bool ZString::operator>(ZString const obj) const {
    for (int i = 0; i < min(len, obj.length()); i++) {
        if ((*this)[i] > obj[i]) {
            return true;
        } else if ((*this)[i] < obj[i]) {
            return false;
        }
    }

    return len > obj.length();
}

bool ZString::operator==(ZString const obj) const {
    return !((*this) < obj || (*this) > obj);
}

bool ZString::operator<=(ZString const obj) const {
    return (*this) < obj || (*this) == obj;
}

bool ZString::operator>=(ZString const obj) const {
    return (*this) > obj || (*this) == obj;
}

bool ZString::operator!=(ZString const obj) const {
    return !((*this) == obj);
}

// Uloha 3
bool ZString::is_subset(char const *container) const {
    for (int i = 0; i < len; i++) {
        bool found = false;
        for (int j = 0; j < strlen(container); j++) {
            if ((*this)[i] == container[j]) {
                found = true;
                break;
            }
        }

        if (!found) {
            return false;
        }
    }
    return true;
}

bool ZString::empty_intersection(char const *container) const {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < strlen(container); j++) {
            if ((*this)[i] == container[j]) {
                return false;
            }
        }
    }
    return true;
}

bool ZString::isdigit() const {
    char const *allowed = "0123456789";
    return is_subset(allowed) && len > 0;
}

bool ZString::isalnum() const {
    char const *allowed = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return is_subset(allowed) && len > 0;
}

bool ZString::isalpha() const {
    char const *allowed = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return is_subset(allowed) && len > 0;
}

bool ZString::islower() const {
    char const *forbidden = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return empty_intersection(forbidden) && len > 0;
}

bool ZString::isupper() const {
    char const *forbidden = "abcdefghijklmnopqrstuvwxyz";
    return empty_intersection(forbidden) && len > 0;
}

bool ZString::isprintable() const {
    char const *allowed = "'0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\""
            "#$%&\\'()*+,-./:;<=>?@[\\\\]^_`{|}~ \\t\\n\\r\\x0b\\x0c'";
    return is_subset(allowed) && len > 0;
}

bool ZString::isspace() const {
    char const *allowed = " \\t\\n\\r\\x0b\\x0c";
    return is_subset(allowed) && len > 0;
}

// Uloha 4

unsigned int ZString::index(ZString const obj, unsigned int const start) const {
    return index(obj, start, len);
}

unsigned int ZString::index(ZString const obj, unsigned int const start, unsigned int const end) const {
    for (unsigned int i = start; i < end; i++) {
        if (check_substring(obj, i, end)) {
            return i;
        }
    }

    throw std::invalid_argument("Substring not found!");
};

unsigned int ZString::rindex(ZString const obj, unsigned int const start) const {
    return rindex(obj, start, len);
}

unsigned int ZString::rindex(ZString const obj, unsigned int const start, unsigned int const end) const {
    for (int i = end - 1; i >= (int) start; i--) {
        if (check_substring(obj, i, end)) {
            return i;
        }
    }

    throw std::invalid_argument("Substring not found!");
}

void ZString::reverse() {
    for (unsigned int i = 0; i < len / 2; i++) {
        char tmp = (*this)[i];
        (*this)[i] = (*this)[len - i - 1];
        (*this)[len - i - 1] = tmp;
    }
}


int ZString::find(ZString const obj, unsigned int const start) const {
    return find(obj, start, len);
}

int ZString::find(ZString const obj, unsigned int const start, unsigned int const end) const {
    try {
        return index(obj, start, end);
    }
    catch (std::invalid_argument const &err) {
        return -1;
    }
}

int ZString::rfind(ZString const obj, unsigned int const start) const {
    return rfind(obj, start, len);
}

int ZString::rfind(ZString const obj, unsigned int const start, unsigned int const end) const {
    try {
        return rindex(obj, start, end);
    }
    catch (std::invalid_argument const &err) {
        return -1;
    }
}

int ZString::count(ZString const obj, unsigned int const start) const {
    return count(obj, start, len);
}

int ZString::count(ZString const obj, unsigned int const start, unsigned int const end) const {
    int index = start;
    int count = 0;
    while (true) {
        index = find(obj, index, end);
        if (index == -1) {
            break;
        }

        index += obj.length();
        count++;
    }

    return count;
}

bool ZString::startswith(ZString const obj, unsigned int const start) const {
    return startswith(obj, start, len);
}

bool ZString::startswith(ZString const obj, unsigned int const start, unsigned int const end) const {
    int index = find(obj, start, end);
    return index == start;
}

bool ZString::endswith(ZString const obj, unsigned int const start) const {
    return endswith(obj, start, len);
}

bool ZString::endswith(ZString const obj, unsigned int const start, unsigned int const end) const {
    int index = rfind(obj, start, end);
    return index + obj.length() == end;
}
