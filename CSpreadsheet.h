#pragma once

#include "CPos.h"
#include "AST/AST.h"
#include "AST/ASTBuilder.h"
#include "AST/ASTNodeValue.h"


constexpr unsigned SPREADSHEET_CYCLIC_DEPS = 0x01;
constexpr unsigned SPREADSHEET_FUNCTIONS = 0x02;
constexpr unsigned SPREADSHEET_FILE_IO = 0x04;
constexpr unsigned SPREADSHEET_SPEED = 0x08;
constexpr unsigned SPREADSHEET_PARSER = 0x10;


/**
 * @brief Represents a spreadsheet.
 */
class CSpreadsheet {
public:

    static unsigned capabilities() {
        return SPREADSHEET_CYCLIC_DEPS | SPREADSHEET_FILE_IO | SPREADSHEET_SPEED;
    }

    /**
     * @brief Loads the spreadsheet from the input stream.
     * @param is The input stream.
     * @return True if the load operation succeeds, otherwise false.
    */
    bool load(std::istream &is);

    /**
     * @brief Saves the spreadsheet into a specified output stream.
     * @param os The output stream.
     * @return True if the load operation succeeds, otherwise false.
    */
    bool save(std::ostream &os) const;

    /**
     * @brief Sets the contents of a cell in the spreadsheet.
     * @param pos The position of the cell.
     * @param contents The contents of the cell.
     * @return True if the cell is set successfully, otherwise false.
    */
    bool setCell(CPos pos,
                 std::string contents);

    /**
     * @brief Gets the value of a cell in the spreadsheet.
     * @param pos The position of the cell.
     * @return The value of the cell.
     */
    CValue getValue(CPos pos) const;

    /**
     * @brief Checks if a cell in the spreadsheet is part of a cyclic dependency.
     * @param pos The position of the cell.
     * @return True if the cell is part of a cyclic dependency, otherwise false.
     */
    bool isCyclic(CPos pos) const;

    /**
     * @brief Copies a rectangular area of cells in the spreadsheet.
     * @param dst The top-left position of the destination rectangle.
     * @param src The top-left position of the source rectangle.
     * @param w The width of the rectangle.
     * @param h The height of the rectangle.
     */
    void copyRect(CPos dst,
                  CPos src,
                  int w = 1,
                  int h = 1);

    /**
     * @brief Overloaded stream insertion operator to output the spreadsheet.
     * @param os The output stream.
     * @param sheet The CSpreadsheet object to output.
     * @return The output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const CSpreadsheet &sheet) {
        for (const auto &key: sheet.m_Sheet) {
            std::string str = key.second->toString();
            os << "{" << key.first.first << "," << key.first.second << "," << str.length() << ",=" << str << "}";
        }
        return os;
    }

private:
    ASTBuilder builder;
    std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> m_Sheet;
};


