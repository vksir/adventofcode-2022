#include "util.h"

using namespace std;

int length;

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

    fmt::print("Result: {}\n", count);
}