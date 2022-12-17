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
#include <fmt/core.h>
#include <fmt/ranges.h>

const std::string ROOT = R"(D:\Code\CCode\adventofcode-2022\)";

struct pair_hash {
    template<class T1, class T2>
    size_t operator()(const std::pair<T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 == h2 ? h1 : h1 ^ h2;
    }
};

#endif //ADVENTOFCODE_2022_UTIL_H
