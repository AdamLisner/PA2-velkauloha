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

    /**
 * @brief Converts a string representation of a cell position to a pair of column and row indices.
 *
 * This function takes a string representation of a cell position in the format "A1" and converts it
 * to a pair of column and row indices. The column index is calculated based on the alphabetical
 * characters in the string (e.g., "A" corresponds to 1, "B" corresponds to 2, etc.), and the row
 * index is calculated based on the numeric characters in the string.
 *
 * @param str The string representation of the cell position (e.g., "A1").
 * @return A pair containing the column and row indices.
 * @throw std::invalid_argument if the input string is not in the correct format.
 */
    static std::pair<size_t, size_t> strToPair(const std::string &str);

    CPos(const std::string &pos) : m_Pos(strToPair(pos)) {};

    CPos(size_t col, size_t row) : m_Pos(std::make_pair(col, row)) {};

    std::pair<size_t, size_t> getPos() const {
        return m_Pos;
    }
/**
 * @brief Converts an integer index to a string representation of a cell column.
 *
 * This function takes an integer index and converts it to a string representation
 * of a cell column. The string representation follows the Excel column naming convention,
 * where the column index 1 corresponds to the letter "A", index 2 to "B", and so on.
 *
 * @param i The integer index.
 * @return A string representing the cell position.
 */
    static std::string intToCol(size_t i) {
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