#include "util.h"

using namespace std;

const array<int, 4> X_OFFSET = {-1, 1, 0, 0};
const array<int, 4> Y_OFFSET = {0, 0, -1, 1};
int length;

bool valid(int x, int y) { return x >= 0 && x < length && y >= 0 && y < length; }

int main() {
    ifstream ifs(ROOT + R"(src\day8\input1.txt)");
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
            for (auto v : val) { tree *= v; }
            max_tree = max(max_tree, tree);
        }
    }

    fmt::print("Result: {}\n", max_tree);
}