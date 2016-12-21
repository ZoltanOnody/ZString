bool is_lower_letter(char const c) {
    return 'a' <= c && c <= 'z';
}

bool is_upper_letter(char const c) {
    return 'A' <= c && c <= 'Z';
}

char to_lower_letter(char const c) {
    if(is_upper_letter(c)){
        return (char) (c + 32);
    }
    return c;
}
char to_upper_letter(char const c) {
    if(is_lower_letter(c)){
        return (char) (c - 32);
    }
    return c;
}
