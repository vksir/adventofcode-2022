#include "util.h"

using namespace std;

const unordered_map<char, pair<int, int>> DIRECTION = {
        {'U', {0, -1}},
        {'D', {0, 1}},
        {'L', {-1, 0}},
        {'R', {1, 0}},
};

int main() {
    ifstream ifs(ROOT + R"(src\day9\input1.txt)");
    if (!ifs.good()) { throw runtime_error("File not exist"); }

    unordered_set<pair<int, int>, pair_hash> visited;
    pair<int, int> head = {0, 0};
    pair<int, int> tail = {0, 0};
    visited.insert(tail);

    char direct;
    int step;
    while (!ifs.eof()) {
        ifs >> direct >> step;
        fmt::print("{} {}\n", direct, step);
        auto direct_p = DIRECTION.at(direct);
        for (int i = 0; i < step; ++i) {
            pair<int, int> old_head = head;
            head.first += direct_p.first;
            head.second += direct_p.second;

            if (abs(tail.first - head.first) > 1 || abs(tail.second - head.second) > 1) {
                tail = old_head;
                visited.insert(tail);
            }
        }
    }

    fmt::print("Result: {}\n", visited.size());
}