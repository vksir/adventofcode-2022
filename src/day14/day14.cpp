#include "util.h"

using namespace std;

enum TYPE {
    AIR, ROCK, SAND
};
const pair<int, int> ORIGIN{500, 0};

class Context {
public:
    vector<vector<pair<int, int>>> data;
    int min_x{ORIGIN.first}, min_y{ORIGIN.second};
    int max_x{ORIGIN.first}, max_y{ORIGIN.second};

    explicit Context(const string &path) {
        ifstream ifs(path);
        if (!ifs.good()) { throw logic_error("File not exist: " + path); }

        regex pattern(R"((\d+),(\d+))");
        string line;
        while (!ifs.eof()) {
            getline(ifs, line);
            data.emplace_back();
            for (sregex_iterator it(line.begin(), line.end(), pattern); it != sregex_iterator(); ++it) {
                int x = stoi((*it)[1]), y = stoi((*it)[2]);
                data[data.size() - 1].emplace_back(x, y);
                assert(x > -1 && y > -1);
                min_x = min(min_x, x), min_y = min(min_y, y);
                max_x = max(max_x, x), max_y = max(max_y, y);
            }
        }
    }
};

class Solution1 {
public:
    explicit Solution1(const Context &ctx) : ctx(ctx), width(ctx.max_x + 2), height(ctx.max_y + 1) {
        assert(ctx.min_x >= 1);
    }

    virtual int run() {
        init_g();
        int count{0};
        while (drop(ORIGIN)) { ++count; }
        return count;
    }

protected:
    Context ctx;
    vector<vector<int>> g;
    int width, height;

    bool drop(pair<int, int> p) {
        while (true) {
            if (!valid(p.first, p.second + 1)) { return false; }
            if (g[p.second + 1][p.first] == AIR) {
                ++p.second;
                continue;
            }
            if (!valid(p.first - 1, p.second + 1)) { return false; }
            if (g[p.second + 1][p.first - 1] == AIR) {
                --p.first, ++p.second;
                continue;
            }
            if (!valid(p.first + 1, p.second + 1)) { return false; }
            if (g[p.second + 1][p.first + 1] == AIR) {
                ++p.first, ++p.second;
                continue;
            }
            if (g[p.second][p.first] == SAND) { return false; }
            g[p.second][p.first] = SAND;
            return true;
        }
    }

    virtual void init_g() {
        g.resize(height, vector<int>(width));
        for (const auto &line: ctx.data) {
            for (auto p1 = line.begin(), p2 = p1 + 1; p2 != line.end(); ++p1, ++p2) {
                if (p1->first == p2->first) {
                    for (int y = min(p1->second, p2->second); y < max(p1->second, p2->second) + 1; ++y) {
                        g[y][p1->first] = ROCK;
                    }
                } else if (p1->second == p2->second) {
                    for (int x = min(p1->first, p2->first); x < max(p1->first, p2->first) + 1; ++x) {
                        g[p1->second][x] = ROCK;
                    }
                } else {
                    throw logic_error(fmt::format("Beyond Expectation: {}, {}", *p1, *p2));
                }
            }
        }
    }

    bool valid(int x, int y) const {
        assert(x >= 0 && x < width && y >= 0);
        return y < height;
    }
};

class Solution2 : public Solution1 {
public:
    explicit Solution2(const Context &ctx) : Solution1(ctx), floor_y(ctx.max_y + 2) {
        assert(ORIGIN.first - (floor_y - ORIGIN.second) >= 1);
        width = max(ctx.max_x, ORIGIN.first + (floor_y - ORIGIN.second)) + 2;
        height = floor_y + 1;
    }

protected:
    int floor_y;

    void init_g() override {
        Solution1::init_g();
        for (auto &i: g[floor_y]) { i = ROCK; }
    }
};

int main() {
    Context ctx(util::get_input_path(__FILE__, "input.txt"));
    fmt::print("Part1: {}\n", Solution1(ctx).run());
    fmt::print("Part2: {}\n", Solution2(ctx).run());
}