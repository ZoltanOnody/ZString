#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_

class ZString {
    size_t len = 0;
    char *data = nullptr;

public:
    ZString() : ZString("") {};
    ZString(const char *data);

    size_t length();
	char *value();
};

#endif
