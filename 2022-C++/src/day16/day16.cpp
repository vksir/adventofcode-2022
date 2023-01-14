#include "util.h"

using namespace std;

class Context {
public:
    unordered_map<string, pair<int, vector<string>>> data;

    explicit Context(const string &path) {
        ifstream ifs(path);
        if (!ifs.good()) { throw logic_error("File not exist: " + path); }

        smatch res;
        regex pattern(R"(Valve (.+) has.*?(-?\d+).*valves? (.+))");

        string line;
        while (!ifs.eof()) {
            getline(ifs, line);
            if (!regex_search(line, res, pattern)) { throw logic_error("Regex failed"); }
            data[res[1]] = {stoi(res[2]), util::split(res[3], ", ")};
        }
    }
};

struct Record {
    string cur_pos;
    int visited{0};
    int pressure{0};
};


class BaseSolution {
public:
    explicit BaseSolution(Context ctx) : ctx(std::move(ctx)) {
        for (const auto &[enter, p]: this->ctx.data) {
            if (p.first > 0) {
                flows[enter] = p.first;
                bitmasks[enter] = 1 << int(bitmasks.size());
            }
            positions.insert(enter);
            for (const auto &exit: p.second) { positions.insert(exit); }
        }
        assert(bitmasks.size() < 32);
    }

protected:
    Context ctx;
    unordered_set<string> positions;
    unordered_map<string, int> flows;
    unordered_map<string, int> bitmasks;
    unordered_map<pair<string, string>, int, util::PairHash> distances;

    void floyd() {
        distances.reserve(size_t(pow(positions.size(), 2)));
        for (const auto &enter: positions) {
            for (const auto &exit: positions) {
                if (enter == exit) {
                    distances[{enter, exit}] = 0;
                } else {
                    distances[{enter, exit}] = INT_MAX;
                }
            }
        }
        for (const auto &[enter, p]: ctx.data) {
            for (const auto &exit: p.second) { distances[{enter, exit}] = 1; }
        }

        for (const auto &k: positions) {
            for (const auto &enter: positions) {
                for (const auto &exit: positions) {
                    if (distances[{enter, k}] != INT_MAX && distances[{k, exit}] != INT_MAX) {
                        distances[{enter, exit}] = min(
                                distances[{enter, exit}],
                                distances[{enter, k}] + distances[{k, exit}]
                        );
                    }
                }
            }
        }
    }

protected:
    void dfs(Record &r, int left_time, unordered_map<int, int> &ways) {
        if (ways.find(r.visited) != ways.end()) {
            ways[r.visited] = max(ways[r.visited], r.pressure);
        } else {
            ways[r.visited] = r.pressure;
        }
        for (auto &[next_pos, rate]: flows) {
            int dis = distances[{r.cur_pos, next_pos}];
            if (dis != INT_MAX && (r.visited & bitmasks[next_pos]) == 0) {
                int next_left_time = left_time - dis - 1;
                if (next_left_time >= 0) {
                    Record next_r{
                            next_pos,
                            r.visited | bitmasks[next_pos],
                            r.pressure + rate * next_left_time,
                    };
                    dfs(next_r, next_left_time, ways);
                }
            }
        }
    }
};

class Solution1 : BaseSolution {
public:
    explicit Solution1(Context ctx) : BaseSolution(std::move(ctx)) {}

    int run() {
        floyd();
        Record record{"AA"};
        unordered_map<int, int> ways;
        dfs(record, 30, ways);
        int max_pressure{INT_MIN};
        for (const auto &[_, pressure]: ways) {
            max_pressure = max(max_pressure, pressure);
        }
        return max_pressure;
    }
};

class Solution2 : BaseSolution {
public:
    explicit Solution2(Context ctx) : BaseSolution(std::move(ctx)) {}

    int run() {
        floyd();
        Record record{"AA"};
        unordered_map<int, int> ways;
        dfs(record, 26, ways);
        int max_pressure{INT_MIN};
        for (const auto &[v1, p1]: ways) {
            for (const auto &[v2, p2]: ways) {
                if ((v1 & v2) == 0) {
                    max_pressure = max(max_pressure, p1 + p2);
                }
            }
        }
        return max_pressure;
    }
};

int main() {
    Context ctx(util::get_input_path(__FILE__, "input.txt"));
    util::timeit<1>([ctx]() {
        fmt::print("Part1: {}\n", Solution1(ctx).run());
        fmt::print("Part2: {}\n", Solution2(ctx).run());
    });
}