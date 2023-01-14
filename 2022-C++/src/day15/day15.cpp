#include "util.h"

using namespace std;

const array<pair<int, int>, 4> OFFSET = {{{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}};

class Context {
public:
    vector<vector<int>> data;

    explicit Context(const string &path) {
        ifstream ifs(path);
        if (!ifs.good()) { throw logic_error("File not exist: " + path); }

        string line;
        while (!ifs.eof()) {
            getline(ifs, line);
            auto v = util::parse_int(line);
            assert(v.size() == 4);
            data.push_back(v);
        }
    }
};

struct Square {
    pair<int, int> sensor, beacon;
    int distance;

    explicit Square(const pair<int, int> &sensor, const pair<int, int> &beacon)
            : sensor(sensor), beacon(beacon),
              distance(get_distance(beacon.first, beacon.second)) {}

    int get_distance(int x, int y) const { return abs(x - sensor.first) + abs(y - sensor.second); }
};

class BaseSolution {
public:
    explicit BaseSolution(Context ctx) : ctx(std::move(ctx)) {}

protected:
    Context ctx;
    vector<Square> squares;

    void init_squares() {
        for (const auto &v: ctx.data) {
            squares.push_back(Square({v[0], v[1]}, {v[2], v[3]}));
        }
    }
};

class Solution1 : BaseSolution {
public:
    explicit Solution1(Context ctx, int target_y) : BaseSolution(std::move(ctx)), target_y(target_y) {}

    int run() {
        init_squares();
        int left{INT_MAX}, right{INT_MIN};
        for (const auto &squ: squares) {
            left = min(left, squ.sensor.first - squ.distance);
            right = max(right, squ.sensor.first + squ.distance);
        }
        int count{0};
        for (int x = left; x < right + 1; ++x) {
            for (const auto &squ: squares) {
                if (squ.get_distance(x, target_y) <= squ.distance &&
                    (x != squ.beacon.first || target_y != squ.beacon.second)) {
                    ++count;
                    break;
                }
            }
        }
        return count;
    }
protected:
    int target_y;
};

class Solution2 : BaseSolution {
public:
    explicit Solution2(Context ctx, int max_xy) : BaseSolution(std::move(ctx)), max_xy(max_xy) {}

    int64_t run(int k = 1) {
        init_squares();
        for (const auto &squ: squares) {
            for (int abs_x = 0, abs_y = squ.distance + k; abs_x < squ.distance + k + 1; ++abs_x, --abs_y) {
                for (const auto &off: OFFSET) {
                    int x = squ.sensor.first + off.first * abs_x;
                    int y = squ.sensor.second + off.second * abs_y;
                    if (valid(x, y) && !contain(x, y)) {
                        return int64_t(x) * 4000000 + y;
                    }
                }
            }
        }
        throw logic_error("Beyond expectation");
    }

protected:
    int max_xy;

    bool valid(int x, int y) const { return x >= 0 && x <= max_xy && y >= 0 && y <= max_xy; }

    bool contain(int x, int y) {
        return any_of(squares.begin(), squares.end(), [x, y](const auto &squ) {
            return squ.get_distance(x, y) <= squ.distance;
        });
    }
};

int main() {
    Context ctx(util::get_input_path(__FILE__, "input.txt"));
    fmt::print("Part1: {}\n", Solution1(ctx, 2000000).run());
    fmt::print("Part2: {}\n", Solution2(ctx, 4000000).run());
}