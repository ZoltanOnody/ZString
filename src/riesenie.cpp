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

ZString::ZString(char const c) {

    size_t len = 1;
    this->len = len;
    this->data = new char[len+1];

    data[0] = c;
    data[1] = '\0';
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

ZString ZString::lower() const {
    ZString tmp(*this);

    for(unsigned int i=0; i < tmp.length(); i++){
        if('A' <= tmp[i] && tmp[i] <= 'Z'){
            tmp[i] += 32;
        }
    }
    return tmp;
}

ZString ZString::upper() const {
    ZString tmp(*this);

    for(unsigned int i=0; i < tmp.length(); i++){
        if('a' <= tmp[i] && tmp[i] <= 'z'){
            tmp[i] -= 32;
        }
    }
    return tmp;
}

void ZString::replace(ZString const what, ZString const by, int count) {
    int tmp_count = this->count(what);

    if (count < 0 || count > tmp_count){
        count = tmp_count;
    }

    size_t new_size = length()-count*what.length()+count*by.length(); // length of the new string
    char *tmp = new char[new_size+1];

    int tmp_index = 0;
    int last_position = 0;
    for(int i=0; i < count; i++){
        int start_position = this->find(what, last_position);

        for(int j=last_position; j < start_position; j++) {
            tmp[tmp_index++] = data[j];
        }
        for(int j=0; j < by.length(); j++){
            tmp[tmp_index++] = by.value()[j];
        }

        last_position = start_position + what.length();
    }

    for(int j=last_position; j < length(); j++){
        tmp[tmp_index++] = data[j];
    }
    tmp[new_size] = '\0';

    data = tmp;
}

ZString ZString::zfill(int len) const {
    if(len <= this->length()){
        ZString tmp(*this);
        return tmp;
    }
    char *tmp = new char[len+1];
    for(int i=0; i < len-this->length(); i++){
        tmp[i] = '0';
    }
    for(int i=0; i < this->length(); i++){
        tmp[i+len-this->length()] = data[i];
    }

    tmp[len] = '\0';

    ZString s(tmp);
    return s;
}

ZString ZString::swapcase() const {
    ZString tmp(*this);

    for(char &c: tmp){
        if('a' <= c && c <= 'z'){
            c -= 32;
        } else if ('A' <= c && c <= 'Z'){
            c += 32;
        }
    }

    return tmp;
}


ZString ZString::center(int len, char fill) const {
    if(this->length() > len){
        len = this->length();
    }

    char *tmp_data = new char [len];
    int last_index = 0;

    for(int i=0; i < (len-this->length())/2; i++){
        tmp_data[last_index++] = fill;
    }

    for(int i=0; i < this->length(); i++){
        tmp_data[last_index++] = data[i];
    }

    for(int i=0; i < (len-this->length()+1)/2; i++){
        tmp_data[last_index++] = fill;
    }

    ZString tmp(tmp_data);
    return tmp;
}

ZString ZString::ljust(int len, char fill) const {
    if(this->length() > len){
        len = this->length();
    }

    char *tmp_data = new char [len];
    int last_index = 0;

    for(int i=0; i < (len-this->length()); i++){
        tmp_data[last_index++] = fill;
    }

    for(int i=0; i < this->length(); i++){
        tmp_data[last_index++] = data[i];
    }

    ZString tmp(tmp_data);
    return tmp;
}

ZString ZString::title() const {
    char *tmp = new char [this->length()+1];

    for (int i=0; i < this->length(); i++) {
        tmp[i] = data[i];
        if (i == 0 || !ZString(tmp[i-1]).isalpha()) {
            if('a' <= tmp[i] && tmp[i] <= 'z'){
                tmp[i] -= 32;
            }
        } else {
            if('A' <= tmp[i] && tmp[i] <= 'Z'){
                tmp[i] += 32;
            }
        }
    }

    tmp[this->length()] = '\0';

    ZString ztmp(tmp);
    return ztmp;
}

ZString ZString::capitalize() const {
    ZString tmp(*this);

    for(char &c: tmp){
        if('A' <= c && c <= 'Z'){
            c += 32;
        }
    }

    if('a' <= tmp[0] && tmp[0] <= 'z'){
        tmp[0] -= 32;
    }

    return tmp;
}