#include "../util.h"

using namespace std;

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


int main() {
    ifstream ifs(ROOT + R"(src\day2\input1.txt)");
    if (!ifs.good()) throw runtime_error("File not exist");
    string opponent, outcome, me;
    int total_score = 0;
    while (!ifs.eof()) {
        ifs >> opponent >> outcome;
        opponent += " " + outcome;
        me = ME_SHAPE_MAP.at(opponent);
        total_score += SHAPE_SCORE_MAP.at(me);
        total_score += OUTCOME_SCORE_MAP.at(outcome);
    }
    cout << "Result: " << total_score << endl;
}