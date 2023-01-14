#include "util.h"

using namespace std;

namespace part1 {
    int get_score(char c) {
        if (int(c) >= int('a') && int(c) <= int('z')) {
            return int(c) - int('a') + 1;
        } else {
            return int(c) - int('A') + 27;
        }
    }

    int solution(const string &path) {
        ifstream ifs(path);
        if (!ifs.good()) { throw runtime_error("File not exist"); }
        int sum = 0;
        string line;

        while (!ifs.eof()) {
            ifs >> line;
            if (line.size() % 2 != 0) throw logic_error("Line size error");
            int mid_after = int(line.size()) / 2;
            for (const auto c: line) {
                if (line.find(c, mid_after) != string::npos) {
                    sum += get_score(c);
                    break;
                }
            }
        }
        return sum;
    }
}

namespace part2 {
    int get_score(char c) {
        if (int(c) >= int('a') && int(c) <= int('z')) {
            return int(c) - int('a') + 1;
        } else {
            return int(c) - int('A') + 27;
        }
    }

    int solution(const string &path) {
        ifstream ifs(path);
        if (!ifs.good()) { throw runtime_error("File not exist"); }
        int sum = 0;
        array<string, 3> g;

        while (!ifs.eof()) {
            for (int i = 0; i < 3; i++) ifs >> g[i];
            for (const auto c: g[0]) {
                if (g[1].find(c) != string::npos && g[2].find(c) != string::npos) {
                    sum += get_score(c);
                    break;
                }
            }
        }
        return sum;
    }
}

int main() {
    string path{util::get_input_path(__FILE__, "input.txt")};
    fmt::print("Part1: {}\n", part1::solution(path));
    fmt::print("Part2: {}\n", part2::solution(path));
}