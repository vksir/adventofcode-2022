#include "../util.h"

using namespace std;

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


int main() {
    ifstream ifs(ROOT + R"(src\day2\input1.txt)");
    if (!ifs.good()) throw runtime_error("File not exist");
    string opponent, me;
    int total_score = 0;
    while (!ifs.eof()) {
        ifs >> opponent >> me;
        total_score += SHAPE_SCORE_MAP.at(me);
        opponent += " " + me;
        total_score += ME_SHAPE_MAP.at(opponent);
    }
    cout << "Result: " << total_score << endl;
}