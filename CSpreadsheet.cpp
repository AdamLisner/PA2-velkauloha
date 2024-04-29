#include "CSpreadsheet.h"
#include <utility>


bool CSpreadsheet::setCell(CPos pos, std::string contents) {
    try {
        parseExpression(std::move(contents), builder);
    } catch (const std::invalid_argument &ex) {
        return false;
    }
    m_Sheet[pos.getPos()] = builder.stack().top();
    builder.stack().pop();
    return true;
}

CValue CSpreadsheet::getValue(CPos pos) {
    std::shared_ptr<ASTNode> c;
    try {
        c = m_Sheet.at(pos.getPos());
    } catch (const std::out_of_range &o) {
        return std::monostate();
    }
    if (isCyclic(pos))
        return {};
    return c->evaluate(m_Sheet);
}

bool CSpreadsheet::load(std::istream &is) {
    this->m_Sheet.clear();
    while (true) {
        size_t col, row, length;
        char open, delim, end;
        if (is.eof()) {
            return true;
        }
        if (!(is >> open && open == '{')) {
            return false;
        }
        if (is.eof()) return false;
        if (!(is >> col >> delim && delim == ',')) {
            return false;
        }
        if (is.eof()) return false;
        if (!(is >> row >> delim && delim == ',')) {
            return false;
        }
        if (is.eof()) return false;

        if (!(is >> length >> delim && delim == ',')) {
            return false;
        }
        if (is.eof()) return false;
        std::string data;
        for (size_t i = 0; i <= length; ++i) {
            char c;
            if (!(is >> std::noskipws >> c) || is.eof()) {
                return false;
            }
            data += c;
        }
        if (is.eof()) return false;
        if (!(is >> end && end == '}')) {
            return false;
        }
        if (!setCell({col, row}, data))
            return false;
        is.peek();
    }
}

bool CSpreadsheet::save(std::ostream &os) const {
    if (!os.good()) {
        std::cerr << "Error: Invalid output stream." << std::endl;
        return false;
    }
    os << *this;
    if (os.good()) {
        std::cout << "Spreadsheet saved successfully." << std::endl;
        return true;
    } else {
        std::cerr << "Error: Failed to save spreadsheet." << std::endl;
        return false;
    }
}

void CSpreadsheet::copyRect(CPos dst, CPos src, int w, int h) {
    auto dstPos = dst.getPos();
    auto srcPos = src.getPos();
    if (dstPos == srcPos) return;
    auto offset = std::make_pair(dstPos.first - srcPos.first, dstPos.second - srcPos.second);
    std::deque<std::shared_ptr<ASTNode>> treesToCopy;
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            std::shared_ptr<ASTNode> a;

            if (m_Sheet.contains({srcPos.first + i, srcPos.second + j})) {
                treesToCopy.push_back(m_Sheet[{srcPos.first + i, srcPos.second + j}]->clone());
            } else {
                treesToCopy.push_back(std::make_shared<ASTNodeValue>(CValue()));
            }
        }
    }
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            treesToCopy.front()->moveRelative(offset);
            m_Sheet[{dstPos.first + i, dstPos.second + j}] = treesToCopy.front();
            treesToCopy.pop_front();
        }
    }
}

bool CSpreadsheet::isCyclic(CPos pos) {
    std::unordered_set<std::pair<size_t, size_t>, hash_pair> openNodes;
    auto from = m_Sheet.at(pos.getPos());
    return from->checkCycle(openNodes, m_Sheet);
}
