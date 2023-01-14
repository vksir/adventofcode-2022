#include "util.h"

using namespace std;

namespace part1 {
    const unordered_map<char, pair<int, int>> DIRECTION = {
            {'U', {0,  -1}},
            {'D', {0,  1}},
            {'L', {-1, 0}},
            {'R', {1,  0}},
    };

    int solution(const string &path) {
        ifstream ifs(path);
        if (!ifs.good()) { throw runtime_error("File not exist"); }

        unordered_set<pair<int, int>, util::PairHash> visited;
        pair<int, int> head = {0, 0};
        pair<int, int> tail = {0, 0};
        visited.insert(tail);

        char direct;
        int step;
        while (!ifs.eof()) {
            ifs >> direct >> step;
//            fmt::print("{} {}\n", direct, step);
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
        return int(visited.size());
    }
}

namespace part2 {
    const unordered_map<char, pair<int, int>> DIRECTION = {
            {'U', {0,  1}},
            {'D', {0,  -1}},
            {'L', {-1, 0}},
            {'R', {1,  0}},
    };
    const int KNOT_NUM = 10;

    int solution(const string &path) {
        ifstream ifs(path);
        if (!ifs.good()) { throw runtime_error("File not exist"); }

        unordered_set<pair<int, int>, util::PairHash> visited;
        visited.emplace(0, 0);
        array<pair<int, int>, KNOT_NUM> knots;
        for (auto & knot : knots) {
            knot = make_pair(0, 0);
        }

        char direct;
        int step;
        while (!ifs.eof()) {
            ifs >> direct >> step;
//            fmt::print("{} {}\n", direct, step);
            auto direct_p = DIRECTION.at(direct);
            for (int i = 0; i < step; ++i) {
//                pair<int, int> tmp;
                knots[0].first += direct_p.first;
                knots[0].second += direct_p.second;
                for (int j = 0; j < knots.size() - 1; ++j) {
                    if (abs(knots[j + 1].first - knots[j].first) > 1 ||
                        abs(knots[j + 1].second - knots[j].second) > 1) {
//                        tmp = knots[j + 1];
                        if (knots[j].first == knots[j + 1].first) {
                            int dis = knots[j].second - knots[j + 1].second;
                            knots[j + 1].second += dis / abs(dis);
                        } else if (knots[j].second == knots[j + 1].second) {
                            int dis = knots[j].first - knots[j + 1].first;
                            knots[j + 1].first += dis / abs(dis);
                        } else {
                            int dis_y = knots[j].second - knots[j + 1].second;
                            knots[j + 1].second += dis_y / abs(dis_y);
                            int dis_x = knots[j].first - knots[j + 1].first;
                            knots[j + 1].first += dis_x / abs(dis_x);
                        }
//                        fmt::print("Knot_{} from {} to {}\n", j + 1, tmp, knots[j + 1]);
                        if (j + 1 == knots.size() - 1) {
                            visited.insert(knots[j + 1]);
                        }

                    }
                }
//                fmt::print("Knots: {}\n", knots);
            }
        }
        return int(visited.size());
    }
}

int main() {
    string path{util::get_input_path(__FILE__, "input.txt")};
    fmt::print("Part1: {}\n", part1::solution(path));
    fmt::print("Part2: {}\n", part2::solution(path));
}