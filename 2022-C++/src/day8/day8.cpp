#include "util.h"

using namespace std;

namespace part1 {
    int length;

    int solution(const string &path) {
        ifstream ifs(path);
        if (!ifs.good()) { throw runtime_error("File not exist"); }

        string line;
        ifs >> line;
        length = int(line.size());
        vector<vector<int>> m(length);
        for (auto &r: m) { r.resize(length); }
        int r_num = 0;
        while (!ifs.eof()) {
            if (r_num > 0) { ifs >> line; }
            for (int i = 0; i < line.size(); i++) { m[r_num][i] = line[i] - '0'; }
            r_num++;
        }

        vector<vector<bool>> record(length);
        for (auto &r: record) { r.resize(length); }

        int count = 0;
        for (int y = 0; y < length; y++) {
            int height = INT_MIN;
            for (int x = 0; x < length; x++) {
                if (m[y][x] > height) {
                    height = m[y][x];
                    if (!record[y][x]) {
                        record[y][x] = true;
                        count++;
                    }
                }
            }
        }
        for (int y = 0; y < length; y++) {
            int high = INT_MIN;
            for (int x = length - 1; x >= 0; x--) {
                if (m[y][x] > high) {
                    high = m[y][x];
                    if (!record[y][x]) {
                        record[y][x] = true;
                        count++;
                    }
                }
            }
        }
        for (int x = 0; x < length; x++) {
            int high = INT_MIN;
            for (int y = 0; y < length; y++) {
                if (m[y][x] > high) {
                    high = m[y][x];
                    if (!record[y][x]) {
                        record[y][x] = true;
                        count++;
                    }
                }
            }
        }
        for (int x = 0; x < length; x++) {
            int high = INT_MIN;
            for (int y = length - 1; y >= 0; y--) {
                if (m[y][x] > high) {
                    high = m[y][x];
                    if (!record[y][x]) {
                        record[y][x] = true;
                        count++;
                    }
                }
            }
        }

        return count;
    }
}

namespace part2 {
    const array<int, 4> X_OFFSET = {-1, 1, 0, 0};
    const array<int, 4> Y_OFFSET = {0, 0, -1, 1};
    int length;

    bool valid(int x, int y) { return x >= 0 && x < length && y >= 0 && y < length; }

    int solution(const string &path) {
        ifstream ifs(path);
        if (!ifs.good()) { throw runtime_error("File not exist"); }

        string line;
        ifs >> line;
        length = int(line.size());
        vector<vector<int>> m(length);
        for (auto &r: m) { r.resize(length); }
        int r_num = 0;
        while (!ifs.eof()) {
            if (r_num > 0) { ifs >> line; }
            for (int i = 0; i < line.size(); i++) { m[r_num][i] = line[i] - '0'; }
            r_num++;
        }

        int max_tree = INT_MIN;
        for (int y = 1; y < length - 1; y++) {
            for (int x = 1; x < length - 1; x++) {
                const int height = m[y][x];

                array<int, 4> val{};
                int cur_x, cur_y;
                for (int k = 0; k < 4; ++k) {
                    for (int i = 1;; ++i) {
                        cur_x = x + X_OFFSET[k] * i;
                        cur_y = y + Y_OFFSET[k] * i;
                        if (!valid(cur_x, cur_y)) {
                            val[k] = i - 1;
                            break;
                        } else if (m[cur_y][cur_x] >= height) {
                            val[k] = i;
                            break;
                        }
                    }
                }
                int tree = 1;
                for (auto v: val) { tree *= v; }
                max_tree = max(max_tree, tree);
            }
        }

        return max_tree;
    }
}

int main() {
    string path{util::get_input_path(__FILE__, "input.txt")};
    fmt::print("Part1: {}\n", part1::solution(path));
    fmt::print("Part2: {}\n", part2::solution(path));
}