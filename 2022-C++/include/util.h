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
#include <filesystem>
#include <fmt/core.h>
#include <fmt/ranges.h>

namespace util {
    struct PairHash {
        template<class T1, class T2>
        size_t operator()(const std::pair<T1, T2> &p) const {
            auto h1 = std::hash<T1>{}(p.first);
            auto h2 = std::hash<T2>{}(p.second);
            return h1 == h2 ? h1 : h1 ^ h2;
        }
    };

    std::vector<std::string> split(const std::string& s, const std::string& sep = " ") {
        std::vector<std::string> v;
        size_t begin = 0, end = 0;
        while ((end = s.find(sep, begin)) != std::string::npos) {
            v.push_back(s.substr(begin, end - begin));
            begin = end + sep.size();
        }
        v.push_back(s.substr(begin));

        if (sep == " ") {
            for (auto it = v.begin(); it != v.end(); ++it) {
                if (it->empty()) { v.erase(it--); }
            }
        }
        return v;
    }

    const std::array<std::pair<int, int>, 4> DIRECTION = {{{0, -1}, {0, 1}, {-1, 0}, {1, 0}}};

    std::vector<int> parse_int(const std::string &s) {
        std::vector<int> v;
        std::regex pattern(R"((-?\d+))");
        for (std::sregex_iterator it(s.begin(), s.end(), pattern); it != std::sregex_iterator(); ++it) {
            v.push_back(std::stoi((*it)[1]));
        }
        return v;
    }

    std::string get_input_path(const std::string &src_path, const std::string &filename) {
        return std::filesystem::path(src_path).parent_path().append(filename).string();
    }

    template<int T>
    void timeit(const std::function<void()> &f) {
        auto t1 = std::chrono::system_clock::now();
        for (int i = 0; i < T; ++i) { f(); }
        auto t2 = std::chrono::system_clock::now();
        fmt::print("Cost: {}ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count());
    }
}


#endif //ADVENTOFCODE_2022_UTIL_H
