#include "util.h"

using namespace std;

namespace part1 {
    const unordered_map<string, int> ME_SHAPE_MAP = {
            {"A X", 3},
            {"A Y", 6},
            {"A Z", 0},
            {"B X", 0},
            {"B Y", 3},
            {"B Z", 6},
            {"C X", 6},
            {"C Y", 0},
            {"C Z", 3},
    };
    const unordered_map<string, int> SHAPE_SCORE_MAP = {
            {"A", 1},
            {"B", 2},
            {"C", 3},
            {"X", 1},
            {"Y", 2},
            {"Z", 3},
    };


    int solution(const string &path) {
        ifstream ifs(path);
        if (!ifs.good()) { throw runtime_error("File not exist"); }
        string opponent, me;
        int total_score = 0;
        while (!ifs.eof()) {
            ifs >> opponent >> me;
            total_score += SHAPE_SCORE_MAP.at(me);
            opponent += " " + me;
            total_score += ME_SHAPE_MAP.at(opponent);
        }
        return total_score;
    }
}

namespace part2 {
    const unordered_map<string, string> ME_SHAPE_MAP = {
            {"A X", "C"},
            {"A Y", "A"},
            {"A Z", "B"},
            {"B X", "A"},
            {"B Y", "B"},
            {"B Z", "C"},
            {"C X", "B"},
            {"C Y", "C"},
            {"C Z", "A"},
    };
    const unordered_map<string, int> OUTCOME_SCORE_MAP = {
            {"X", 0},
            {"Y", 3},
            {"Z", 6},
    };
    const unordered_map<string, int> SHAPE_SCORE_MAP = {
            {"A", 1},
            {"B", 2},
            {"C", 3},
    };


    int solution(const string &path) {
        ifstream ifs(path);
        if (!ifs.good()) { throw runtime_error("File not exist"); }
        string opponent, outcome, me;
        int total_score = 0;
        while (!ifs.eof()) {
            ifs >> opponent >> outcome;
            opponent += " " + outcome;
            me = ME_SHAPE_MAP.at(opponent);
            total_score += SHAPE_SCORE_MAP.at(me);
            total_score += OUTCOME_SCORE_MAP.at(outcome);
        }
        return total_score;
    }
}

int main() {
    string path{util::get_input_path(__FILE__, "input.txt")};
    fmt::print("Part1: {}\n", part1::solution(path));
    fmt::print("Part2: {}\n", part2::solution(path));
}