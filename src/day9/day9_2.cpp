#include "util.h"

using namespace std;

const unordered_map<char, pair<int, int>> DIRECTION = {
        {'U', {0,  1}},
        {'D', {0,  -1}},
        {'L', {-1, 0}},
        {'R', {1,  0}},
};
const int KNOT_NUM = 10;

int main() {
    ifstream ifs(ROOT + R"(src\day9\input1.txt)");
    if (!ifs.good()) { throw runtime_error("File not exist"); }

    unordered_set<pair<int, int>, util::PairHash> visited;
    visited.emplace(0, 0);
    array<pair<int, int>, KNOT_NUM> knots;
    for (int i = 0; i < knots.size(); ++i) {
        knots[i] = make_pair(0, 0);
    }

    char direct;
    int step;
    while (!ifs.eof()) {
        ifs >> direct >> step;
        fmt::print("{} {}\n", direct, step);
        auto direct_p = DIRECTION.at(direct);
        for (int i = 0; i < step; ++i) {
            pair<int, int> tmp;
            knots[0].first += direct_p.first;
            knots[0].second += direct_p.second;
            for (int j = 0; j < knots.size() - 1; ++j) {
                if (abs(knots[j + 1].first - knots[j].first) > 1 || abs(knots[j + 1].second - knots[j].second) > 1) {
                    tmp = knots[j + 1];
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
                    fmt::print("Knot_{} from {} to {}\n", j + 1, tmp, knots[j + 1]);
                    if (j + 1 == knots.size() - 1) {
                        visited.insert(knots[j + 1]);
                    }

                }
            }
            fmt::print("Knots: {}\n", knots);
        }
    }

    fmt::print("Result: {}\n", visited.size());
}