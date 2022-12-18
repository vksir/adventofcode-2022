#ifndef ADVENTOFCODE_2022_UTIL_H
#define ADVENTOFCODE_2022_UTIL_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <sstream>
#include <queue>
#include <regex>
#include <cassert>
#include <climits>
#include <fmt/core.h>
#include <fmt/ranges.h>

const std::string ROOT = R"(D:\Code\CCode\adventofcode-2022\)";

namespace util {
    struct PairHash {
        template<class T1, class T2>
        size_t operator()(const std::pair<T1, T2> &p) const {
            auto h1 = std::hash<T1>{}(p.first);
            auto h2 = std::hash<T2>{}(p.second);
            return h1 == h2 ? h1 : h1 ^ h2;
        }
    };

    std::vector<std::string> split(std::string s, char sep = ' ') {
        std::vector<std::string> v;
        if (s.empty()) { return v; }

        int a = 0, b = 0;
        for (; b < s.size(); ++b) {
            if (s[b] == sep) {
                v.push_back(s.substr(a, b - a));
                a = b + 1;
            }
        }
        v.push_back(s.substr(a, b - a));

        if (sep == ' ') {
            for (auto it = v.begin(); it != v.end(); ++it) {
                if (it->empty()) { v.erase(it--); }
            }
        }
        return v;
    }

    int get_part(int argc, char *argv[], int default_part) {
        if (argc <= 1) { return default_part; }
        return std::stoi(argv[1]);
    }

    const std::array<std::pair<int, int>, 4> DIRECTION = {{{0, -1}, {0, 1}, {-1, 0}, {1, 0}}};
}


#endif //ADVENTOFCODE_2022_UTIL_H
