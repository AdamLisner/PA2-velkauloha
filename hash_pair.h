#include <utility>
#include <cstdlib>
#include <functional>

/*
 * Quelle: https://www.geeksforgeeks.org/how-to-create-an-unordered_map-of-pairs-in-c/
 *
 * */
struct hash_pair {
    size_t operator()(const std::pair<size_t, size_t> &p) const {
        auto hash1 = std::hash<size_t>{}(p.first);
        auto hash2 = std::hash<size_t>{}(p.second);

        if (hash1 != hash2) {
            return hash1 ^ hash2;
        }

        return hash1;
    }
};