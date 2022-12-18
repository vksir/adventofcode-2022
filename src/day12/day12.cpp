#include "util.h"

using namespace std;

class Context {
public:
    vector<string> m;
    pair<int, int> start, end;

    Context() {
        ifstream ifs("../src/day12/input1.txt");
        if (!ifs.good()) { throw runtime_error("File not exist"); }
        string line;
        while (!ifs.eof()) {
            ifs >> line;
            m.push_back(line);
        }
        if (m.empty()) { throw logic_error("Invalid data"); }
        for (int y = 0; y < m.size(); ++y) {
            for (int x = 0; x < m[0].size(); ++x) {
                if (m[y][x] == 'S') { start = {x, y}; }
                if (m[y][x] == 'E') { end = {x, y}; }
            }
        }
        m[start.second][start.first] = 'a';
        m[end.second][end.first] = 'z';
        width = int(m[0].size());
        height = int(m.size());
        ifs.close();
    }

    bool valid(int x, int y) const { return x >= 0 && x < width && y >= 0 && y < height; }

private:
    int width, height;
};

class Solution {
public:
    int static run(const Context &ctx, pair<int, int> start, pair<int, int> end) {
        bool visited[ctx.m.size()][ctx.m[0].size()];
        for (auto &r: visited) {
            for (auto &i: r) { i = false; }
        }
        visited[start.second][start.first] = true;
        vector<pair<int, int>> heads{start}, next_heads;
        int cur_step{0};

        while (!heads.empty()) {
//            fmt::print("{}\n", heads);
            for (const auto &p: heads) {
                if (p == end) { return cur_step; }
            }
            for (const auto &p: heads) {
                for (const auto &d: util::DIRECTION) {
                    int next_x = p.first + d.first, next_y = p.second + d.second;
                    if (ctx.valid(next_x, next_y) && !visited[next_y][next_x] &&
                        ctx.m[next_y][next_x] - ctx.m[p.second][p.first] <= 1) {
                        visited[next_y][next_x] = true;
                        next_heads.emplace_back(next_x, next_y);
                    }
                }
            }
            cur_step++;
            heads = next_heads;
            next_heads.clear();
        }
        return INT_MAX;
    }
};

int main(int argc, char *argv[]) {
    Context ctx;

    switch (util::get_part(argc, argv, 1)) {
        case 1: {
            fmt::print("Result: {}\n", Solution::run(ctx, ctx.start, ctx.end));
            break;
        }
        case 2: {
            int min_step = INT_MAX;
            for (int y = 0; y < ctx.m.size(); ++y) {
                for (int x = 0; x < ctx.m[0].size(); ++x) {
                    if (ctx.m[y][x] == 'a') {
                        auto step = Solution::run(ctx, {x, y}, ctx.end);
                        min_step = min(min_step, step);
                    }
                }
            }
            fmt::print("Result: {}\n", min_step);
            break;
        }
    }
}