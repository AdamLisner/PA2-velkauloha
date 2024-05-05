#include "CPos.h"

std::pair<size_t, size_t> CPos::strToPair(const std::string &str) {

    size_t col = 0;
    size_t row = 0;
    size_t i = 0;

    int mul = 26;

    for (; !isdigit(str[i]); i++) {
        char c = (toupper)(str[i]);
        if (c < 'A' || c > 'Z') {
            throw std::invalid_argument("invalid argument passed");
        }
        col *= mul;
        col += c - 'A' + 1;
    }

    for (; i < str.length(); i++) {
        if (str[i] < '0' || str[i] > '9') {
            throw std::invalid_argument("invalid argument passed");
        }
        row *= 10;
        row += str[i] - '0';
    }

    return std::make_pair(col, row);
}
