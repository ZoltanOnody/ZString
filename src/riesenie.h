#include <stdexcept>

#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_

class ZString {
    size_t len = 0;
    char *data = nullptr;

    bool is_subset(char const *container) const;

    bool empty_intersection(char const *container) const;

public:
    ZString() : ZString("") {};

    ZString(char const *data);

    char operator[](int const i) const;

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
    unsigned int index(ZString const obj) const;

    unsigned int index(ZString const obj, unsigned int const start) const;

    unsigned int index(ZString const obj, unsigned int const start, unsigned int const end) const;

};

#endif
