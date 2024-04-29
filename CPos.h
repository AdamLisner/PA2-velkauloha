#pragma once

#include <utility>
#include <cstdio>
#include <stdexcept>
#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <climits>
#include <cfloat>
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <array>
#include <utility>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <variant>
#include <optional>
#include <compare>
#include <charconv>
#include <span>
#include <utility>
#include "expression.h"


class CPos {
public:

    static std::pair<size_t, size_t> strToPair(const std::string &str);

    CPos(const std::string &pos) : m_Pos(strToPair(pos)) {};

    CPos(size_t col, size_t row) : m_Pos(std::make_pair(col, row)) {};

    std::pair<size_t, size_t> getPos() const {
        return m_Pos;
    }

    static std::string intToPos(size_t i) {
        std::string result;
        while (i > 0) {
            size_t remainder = i % 26;
            char letter = 'A' - 1 + remainder;
            result = letter + result;
            i = (i - remainder) / 26;
        }
        return result;
    }

private:
    std::pair<size_t, size_t> m_Pos;
};