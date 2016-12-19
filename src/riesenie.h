#include <stdexcept>
#include <vector>

#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_

class ZString {
    size_t len = 0;
    char *data = nullptr;

    bool is_subset(char const *container) const;

    bool empty_intersection(char const *container) const;

    bool check_substring(ZString const obj, unsigned int const i, unsigned const end) const {
        for (unsigned int j = 0; j < obj.length(); j++) {
            if (i + j >= end || (*this)[i + j] != obj[j]) {
                return false;
            }
        }
        return true;
    }

public:
    ZString() : ZString("") {};

    ZString(char const data);
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

    friend std::ostream& operator<< (std::ostream& stream, const ZString& s) {
        stream << s.value();
        return stream;
    }

    char *begin() const {return data;}
    char *end() const {return &data[length()];}

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

    bool startswith(ZString const obj, unsigned int const start = 0) const;

    bool startswith(ZString const obj, unsigned int const start, unsigned int const end) const;

    bool endswith(ZString const obj, unsigned int const start = 0) const;

    bool endswith(ZString const obj, unsigned int const start, unsigned int const end) const;

    void reverse();

    ZString lower() const;
    ZString upper() const;

    void replace(ZString const what, ZString const by, int count=-1);

    ZString zfill(int len) const;
    ZString swapcase() const;
    ZString center(int len, char fill=' ') const;
    ZString ljust(int len, char fill=' ') const;
    ZString title() const;
    ZString capitalize() const;

    ZString lstrip(char const c=' ') const {
        char data[] = {c};
        return this->lstrip(data);
    }
    ZString lstrip(char const data[]) const;

    ZString rstrip(char const c=' ') const{
        char data[] = {c};
        return this->rstrip(data);
    }
    ZString rstrip(char const data[]) const;
    ZString strip(char const c=' ') const {
        char data[] = {c};
        return this->strip(data);
    }
    ZString strip(char const data[]) const;

    std::vector <ZString> split() const {
        ZString s(" ");
        return this->split(s);
    }
    std::vector <ZString> split(ZString const delimiter, int const limit = -1) const;

    std::vector <ZString> rsplit() const {
        ZString s(" ");
        return this->rsplit(s);
    }
    std::vector <ZString> rsplit(ZString const delimiter, int const limit = -1) const;
};

#endif
