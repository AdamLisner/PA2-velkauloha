#include <utility>
#include <cstdio>
#include <stdexcept>
#include <cctype>

class CPos {
public:

    static std::pair<size_t, size_t> strToPair(const std::string &str);

    CPos(const std::string &pos) : m_Pos(strToPair(pos)) {};

    std::pair<size_t, size_t> getPos() const {
        return m_Pos;
    }

    static std::string intToPos(size_t i) {
        std::string result;
        while (i > 0) {
            int remainder = (i) % 26; // Adjust to 0-indexed remainder
            char letter = 'A' - 1 + remainder;
            result = letter + result;
            i = (i - remainder) / 26;
        }
        return result;
    }

private:
    std::pair<size_t, size_t> m_Pos;
};
