#include <stdexcept>

#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_

class ZString {
    size_t len = 0;
    char *data = nullptr;

    bool is_subset(char const *container) const;

    bool empty_intersection(char const *container) const;

    bool check_substring(ZString const obj, unsigned int const i, unsigned const end) const {
        for (unsigned int j = 0; j < obj.length(); j++) {
            if (i + j >= end) {
                throw std::invalid_argument("Substring not found!");
            }

            if ((*this)[i + j] != obj[j]) {
                return false;
            }
        }
        return true;
    }

public:
    ZString() : ZString("") {};

    ZString(char const *data);

    char operator[](int const index) const {
        if (index >= len) {
            throw std::out_of_range("Index out of range!");
        }
        return data[index];
    }

    char &operator[](int const index) {
        if (index >= len) {
            throw std::out_of_range("Index out of range!");
        }
        return data[index];
    }

    ZString operator+(ZString const obj) const;

    ZString operator*(int const mul) const;

    void operator+=(ZString const obj);

    void operator*=(int const mul);

    bool operator<(ZString const obj) const;

    bool operator>(ZString const obj) const;

    bool operator==(ZString const obj) const;

    bool operator<=(ZString const obj) const;

    bool operator>=(ZString const obj) const;

    bool operator!=(ZString const obj) const;

    size_t length() const;

    char *value() const;

    bool isdigit() const;

    bool isalnum() const;

    bool isalpha() const;

    bool islower() const;

    bool isupper() const;

    bool isprintable() const;

    bool isspace() const;

    // Uloha 4
    unsigned int index(ZString const obj, unsigned int const start = 0) const;
    unsigned int index(ZString const obj, unsigned int const start, unsigned int const end) const;

    unsigned int rindex(ZString const obj, unsigned int const start = 0) const;
    unsigned int rindex(ZString const obj, unsigned int const start, unsigned int const end) const;

    int find(ZString const obj, unsigned int const start = 0) const;

    int find(ZString const obj, unsigned int const start, unsigned int const end) const;

    int rfind(ZString const obj, unsigned int const start = 0) const;

    int rfind(ZString const obj, unsigned int const start, unsigned int const end) const;

    int count(ZString const obj, unsigned int const start = 0) const;

    int count(ZString const obj, unsigned int const start, unsigned int const end) const;

    void reverse();

};

#endif
