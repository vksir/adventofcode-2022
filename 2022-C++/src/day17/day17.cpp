#include "util.h"

using namespace std;

const vector<vector<pair<int64_t, int64_t>>> SHAPE{
        {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
        {{1, 0}, {0, 1}, {1, 1}, {2, 1}, {1, 2}},
        {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}},
        {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
        {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
};
const unordered_map<char, pair<int64_t, int64_t>> DIRECTION{
        {'<', {-1, 0}},
        {'>', {1,  0}},
};
const pair<int64_t, int64_t> DROP{0, -1};

class Context {
public:
    string data;

    explicit Context(const string &path) {
        ifstream ifs(path);
        if (!ifs.good()) { throw logic_error("File not exist: " + path); }
        getline(ifs, data);
    }
};

class BaseSolution {
public:
    explicit BaseSolution(Context ctx) : ctx(std::move(ctx)) {}

protected:
    Context ctx;
    unordered_set<pair<int64_t, int64_t>, util::PairHash> m;

    static vector<pair<int64_t, int64_t>> get_new_shape(int64_t rocks, int64_t highest) {
        int64_t x = 3, y = highest + 4;
        vector<pair<int64_t, int64_t>> shape;
        for (const auto &p: SHAPE.at(rocks % SHAPE.size())) { shape.emplace_back(x + p.first, y + p.second); }
        return shape;
    }

    pair<int64_t, int64_t> get_direction(int64_t round) const {
        return DIRECTION.at(ctx.data[round % ctx.data.size()]);
    }

    bool hit(const vector<pair<int64_t, int64_t>> &shape, const pair<int64_t, int64_t> &d) {
        return any_of(shape.begin(), shape.end(), [&](const auto &p) {
            return !valid(p.first + d.first, p.second + d.second);
        });
    }

    bool valid(int64_t x, int64_t y) {
        return x > 0 && x < 8 && y > 0 && m.find({x, y}) == m.end();
    }

    static void direct_shape(vector<pair<int64_t, int64_t>> &shape, const pair<int64_t, int64_t> &d) {
        for (auto &p: shape) {
            p.first += d.first;
            p.second += d.second;
        }
    }

    void fix_shape(const vector<pair<int64_t, int64_t>> &shape, int64_t &highest) {
        for (const auto &p: shape) {
            m.insert(p);
            highest = max(highest, p.second);
        }
    }
};

struct Record {
    array<int64_t, 6> top_shape;
    int64_t highest;
    int64_t cur_rocks;
};

class Solution : BaseSolution {
public:
    explicit Solution(Context ctx) : BaseSolution(std::move(ctx)) {}

    int64_t run(int64_t rocks) {
        int64_t loop_rocks{5 * int64_t(ctx.data.size())};
        int64_t cur_rocks{0}, highest{0}, round{0};

        vector<Record> records;
        int64_t fold_high{0};
        bool has_fold{false};
        while (cur_rocks < rocks) {
            auto shape = get_new_shape(cur_rocks, highest);

            while (true) {
                auto direction = get_direction(round);
                round++;
                if (!hit(shape, direction)) {
                    direct_shape(shape, direction);
                }

                if (!hit(shape, DROP)) {
                    direct_shape(shape, DROP);
                } else {
                    fix_shape(shape, highest);
                    break;
                }
            }

            cur_rocks++;
            if (cur_rocks % loop_rocks == 0) {
                array<int64_t, 6> cur_top_shape{};
                cur_top_shape.fill(highest);
                for (int i = 0; i < cur_top_shape.size(); ++i) {
                    while (valid(i + 1, cur_top_shape[i])) { cur_top_shape[i]--; }
                    cur_top_shape[i] = highest - cur_top_shape[i];
                }

                if (!has_fold) {
                    for (const auto &r: records) {
                        if (cur_top_shape == r.top_shape) {
                            has_fold = true;
                            fmt::print("Record: {}, cur_rocks={}, highest={}\n",
                                       r.top_shape, r.cur_rocks, r.highest);
                            fmt::print("Fold: {}, cur_rocks={}, highest={}\n",
                                       cur_top_shape, cur_rocks, highest);
                            int64_t fold_times{(rocks - cur_rocks) / (cur_rocks - r.cur_rocks)};
                            fold_high = fold_times * (highest - r.highest);
                            rocks -= fold_times * (cur_rocks - r.cur_rocks);
                            fmt::print("After fold: fold_times={}, fold_high={}, rocks={}\n",
                                       fold_times, fold_high, rocks);
                        }
                    }
                    if (!has_fold) {
                        records.push_back({cur_top_shape, highest, cur_rocks});
                    }
                }
            }
        }
        return highest + fold_high;
    }
};

int main() {
    Context ctx(util::get_input_path(__FILE__, "input.txt"));
    util::timeit<1>([ctx]() {
        fmt::print("Part1: {}\n", Solution(ctx).run(2022));

        // TOTO: Not work on input.txt
        fmt::print("Part2: {}\n", Solution(ctx).run(1000000000000));
    });
}