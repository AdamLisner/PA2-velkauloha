#pragma once

#include "cstdlib"
#include "utility"

struct hash_pair {
    std::size_t operator()(const std::pair<size_t, size_t> &p) const {
        return (p.first + 0x9e3779b9 + (p.first >> 6) + (p.first << 8)) ^
               (p.second + 0x9e3779b9 + (p.second << 7) + (p.second >> 3));
    }
};
