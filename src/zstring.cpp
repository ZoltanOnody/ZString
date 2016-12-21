#include <iostream>
#include <cstring>

#include "helpers.cpp"
#include "zstring.h"


ZString::ZString(ZString const &obj){
    this->len = obj.length();
    this->data = new char[this->len+1];

    for(size_t i=0; i < this->len; this->data[i] = obj[i++]);
    this->data[this->len] = '\0';
}

ZString::ZString(char const *data) {
    size_t len = 0;
    for(;data[len] != '\0'; len++);

    this->len = len;
    this->data = new char[len+1];

    for(size_t i=0; i < len+1; this->data[i] = data[i++]);
}

ZString::ZString(char const c) {
    this->len = 1;
    this->data = new char[2];

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
    for (size_t i = 0; i < len; i++) {
        tmp[i] = data[i];
    }
    for (size_t i = 0; i < obj.length(); i++) {
        tmp[len + i] = obj[i];
    }
    tmp[new_length] = '\0';

    return ZString(tmp);
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
    for (int i = 0; i < mul; i++) { // todo: do it in O(logn)
        ans += *this;
    }

    return ans;
}

void ZString::operator*=(int const mul) {
    ZString new_obj = *this * mul;
    *this = new_obj;
}

bool ZString::operator<(ZString const obj) const {
    for (size_t i = 0; i < std::min(len, obj.length()); i++) {
        if ((*this)[i] < obj[i]) {
            return true;
        } else if ((*this)[i] > obj[i]) {
            return false;
        }
    }

    return len < obj.length();
}

bool ZString::operator>(ZString const obj) const {
    for (size_t i = 0; i < std::min(len, obj.length()); i++) {
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

bool ZString::is_subset(char const *container) const {
    for (size_t i = 0; i < len; i++) {
        bool found = false;
        for (size_t j = 0; j < strlen(container); j++) {
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
    for (size_t i = 0; i < len; i++) {
        for (size_t j = 0; j < strlen(container); j++) {
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

size_t ZString::index(ZString const obj, size_t const start) const {
    return index(obj, start, len);
}

size_t ZString::index(ZString const obj, size_t start, size_t end) const {
    for (size_t i = start; i < end; i++) {
        if (check_substring(obj, i, end)) {
            return i;
        }
    }

    throw std::invalid_argument("Substring not found!");
};

size_t ZString::rindex(ZString const obj, size_t const start) const {
    return rindex(obj, start, len);
}

size_t ZString::rindex(ZString const obj, size_t const start, size_t const end) const {
    for (size_t i = end - 1; i-- > start;) {
        if (check_substring(obj, i, end)) {
            return i;
        }
    }

    throw std::invalid_argument("Substring not found!");
}

ZString ZString::reverse() const {
    ZString stmp = *this;

    for (size_t i = 0; i < len / 2; i++) {
        char tmp = stmp[i];
        stmp[i] = stmp[len - i - 1];
        stmp[len - i - 1] = tmp;
    }

    return stmp;
}

int ZString::find(ZString const obj, size_t const start) const {
    return find(obj, start, len);
}

int ZString::find(ZString const obj, size_t const start, size_t const end) const {
    try {
        return (int) index(obj, start, end);
    }
    catch (std::invalid_argument const &err) {
        return -1;
    }
}

int ZString::rfind(ZString const obj, size_t const start) const {
    return rfind(obj, start, len);
}

int ZString::rfind(ZString const obj, size_t const start, size_t const end) const {
    try {
        return (int) rindex(obj, start, end);
    }
    catch (std::invalid_argument const &err) {
        return -1;
    }
}

unsigned int ZString::count(ZString const obj, size_t const start) const {
    return count(obj, start, len);
}

unsigned int ZString::count(ZString const obj, size_t const start, size_t const end) const {
    int index = (int) start;
    unsigned int count = 0;
    while (true) {
        index = find(obj, (size_t) index, end);
        if (index == -1) {
            break;
        }

        index += obj.length();
        count++;
    }

    return count;
}

bool ZString::startswith(ZString const obj, size_t const start) const {
    return startswith(obj, start, len);
}

bool ZString::startswith(ZString const obj, size_t const start, size_t const end) const {
    int index = find(obj, start, end);
    return index == (int) start;
}

bool ZString::endswith(ZString const obj, size_t const start) const {
    return endswith(obj, start, len);
}

bool ZString::endswith(ZString const obj, size_t const start, size_t const end) const {
    int index = rfind(obj, start, end);
    return index + obj.length() == end;
}

ZString ZString::lower() const {
    ZString tmp(*this);

    for(char &c: tmp){
        c = to_lower_letter(c);
    }

    return tmp;
}

ZString ZString::upper() const {
    ZString tmp(*this);

    for(char &c: tmp){
        c = to_upper_letter(c);
    }

    return tmp;
}

ZString ZString::replace(ZString const what, ZString const by, int count) const {

    int tmp_count = this->count(what);
    if (count < 0 || count > tmp_count){
        count = tmp_count;
    }

    size_t new_size = length() - (count*what.length()) + (count*by.length()); // length of the new string
    char *tmp = new char[new_size+1];

    size_t tmp_index = 0, last_position = 0;
    for(size_t i=0; i < (size_t) count; i++){
        int start_position = this->find(what, last_position);

        if(start_position > 0){
            for(size_t j=last_position; j < (size_t) start_position; j++) {
                tmp[tmp_index++] = data[j];
            }
        }
        for(size_t j=0; j < by.length(); j++){
            tmp[tmp_index++] = by.value()[j];
        }

        last_position = start_position + what.length();
    }

    for(size_t j=last_position; j < length(); j++){
        tmp[tmp_index++] = data[j];
    }
    tmp[new_size] = '\0';

    return ZString(tmp);
}

ZString ZString::zfill(unsigned int len) const {
    if(len <= this->length()){
        return ZString(*this);
    }

    char *tmp = new char[len+1];
    for(size_t i=0; i < len-this->length(); i++){
        tmp[i] = '0';
    }
    for(size_t i=0; i < this->length(); i++){
        tmp[i+len-this->length()] = data[i];
    }
    tmp[len] = '\0';

    return ZString(tmp);
}

ZString ZString::swapcase() const {
    ZString tmp(*this);

    for(char &c: tmp){
        if(is_lower_letter(c)){
            c = to_upper_letter(c);
        } else if (is_upper_letter(c)){
            c = to_lower_letter(c);
        }
    }

    return tmp;
}


ZString ZString::center(size_t len, char const fill) const {
    if(this->length() > len){
        len = this->length();
    }

    char *tmp = new char [len];

    int last_index = 0;
    for(size_t i=0; i < (len-this->length())/2; i++){
        tmp[last_index++] = fill;
    }

    for(size_t i=0; i < this->length(); i++){
        tmp[last_index++] = data[i];
    }

    for(size_t i=0; i < (len-this->length()+1)/2; i++){
        tmp[last_index++] = fill;
    }

    return ZString(tmp);
}

ZString ZString::ljust(size_t len, char fill) const {
    if(this->length() > len){
        len = this->length();
    }

    char *tmp = new char [len];

    size_t last_index = 0;
    for(size_t i=0; i < (len-this->length()); i++){
        tmp[last_index++] = fill;
    }

    for(size_t i=0; i < this->length(); i++){
        tmp[last_index++] = data[i];
    }

    return ZString(tmp);
}

ZString ZString::title() const {
    char *tmp = new char [this->length()+1];

    for (size_t i=0; i < this->length(); i++) {
        tmp[i] = data[i];
        if (i == 0 || !ZString(tmp[i-1]).isalpha()) {
            tmp[i] = to_upper_letter(tmp[i]);
        } else {
            tmp[i] = to_lower_letter(tmp[i]);
        }
    }
    tmp[this->length()] = '\0';

    return ZString(tmp);
}

ZString ZString::capitalize() const {
    ZString tmp(*this);

    for(char &c: tmp){
        c = to_lower_letter(c);
    }
    tmp[0] = to_upper_letter(tmp[0]);

    return tmp;
}

ZString ZString::lstrip(char const data[], size_t data_len) const {
    char *tmp = new char [this->length()];

    bool remove=true;
    int index = 0;
    for (size_t i=0; i < this->length(); i++) {
        if(remove){
            bool removed = false;
            for(size_t j=0; j < data_len; j++){
                if(this->data[i] == data[j]){
                    removed = true;
                    break;
                }
            }

            if(!removed){
                tmp[index++] = this->data[i];
                remove=false;
            }
        } else {
            tmp[index++] = this->data[i];
        }
    }

    tmp[index] = '\0';

    return ZString(tmp);
}
ZString ZString::rstrip(char const data[], int const data_len) const {
    char *tmp = new char [length()];

    size_t index = length()-1;
    for (size_t i=index+1; i-- > 0;) {
        bool found = false;
        for(int j=0; j < data_len; j++){
            if(this->data[i] == data[j]){
                found = true;
                break;
            }
        }
        if(!found){
            index = i;
            break;
        }
    }

    for(int i=0; i <= index; i++){
        tmp[i] = this->data[i];
    }
    tmp[index+1] = '\0';

    return ZString(tmp);
}

ZString ZString::strip(char const data[], int const data_len) const {
    return this->lstrip(data, data_len).rstrip(data, data_len);
}
// todo: check the code bellow
std::vector <ZString> ZString::split(ZString const delimiter, int const limit) const {
    std::vector <ZString> vdata;

    size_t last = 0;
    for (size_t i=0; i < this->length(); i++) {
        bool found = false;
        ZString tmp;
        for (size_t j=i; j < this->length(); j++) {
            tmp = tmp + ZString(data[j]);

            if (tmp == delimiter) {
                found = true;
                break;
            }
        }

        if(found){
            ZString ans;
            for(size_t j=last; j < i; j++){
                ZString chr(data[j]);
                ans += chr;
            }

            vdata.push_back(ans);
            last = i+delimiter.length();
            i = last;
        }

        if(vdata.size() == limit && limit != -1){
            break;
        }
    }

    ZString ans;
    for(size_t j=last; j < length(); j++){
        ans += ZString(data[j]);
    }
    vdata.push_back(ans);

    return vdata;
}

std::vector <ZString> ZString::rsplit(ZString const delimiter, int const limit) const {
    ZString tmp = this->reverse();

    ZString tmp_del = delimiter.reverse();

    std::vector <ZString> tmp_data = tmp.split(tmp_del, limit);
    for(ZString &s: tmp_data){
        s = s.reverse();
    }

    std::vector <ZString> data;
    for(size_t i=tmp_data.size(); i-- > 0;){
        data.push_back(tmp_data[i]);
    }

    return data;
}
