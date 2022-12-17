#include "util.h"

using namespace std;

const array<int, 6> ROUND = {20, 60, 100, 140, 180, 220};

int main() {
    ifstream ifs(ROOT + R"(src\day10\input1.txt)");
    if (!ifs.good()) { throw runtime_error("File not exist"); }

    int x = 1;
    string tag, line;
    int add_x;
    int round = 0;
    int val = 0;
    vector<pair<int, int>> v;
    while (!ifs.eof() || !v.empty()) {
        round++;
        auto r_it = std::find(ROUND.begin(), ROUND.end(), round);
        if (r_it != ROUND.end()) {
            val += *r_it * x;
            fmt::print("{} x {}\n", *r_it, x);
        }

        if (v.empty()) {
            getline(ifs, line);
            if (line.find(' ') != string::npos) {
                stringstream line_s(line);
                line_s >> tag >> add_x;
                v.emplace_back(2, add_x);
            } else {
                v.emplace_back(1, 0);
            }
        }
        assert(!v.empty() && v[0].first > 0);
        v[0].first--;
        if (v[0].first == 0) {
            x += v[0].second;
            v.clear();
        }

    }

    fmt::print("Result: {}\n", val);
}