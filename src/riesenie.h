#include <stdexcept>

#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_

class ZString {
    size_t len = 0;
    char *data = nullptr;

public:
    ZString() : ZString("") {};
    ZString(const char *data);

    char operator [] (int i) const {
        if(i >= len) {
            throw std::out_of_range("Index out of range!");
        }
        return data[i];
    }

    size_t length();
	char *value();
};

#endif
