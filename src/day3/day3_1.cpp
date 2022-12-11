#include "../util.h"

using namespace std;


int get_score(char c) {
    if (int(c) >= int('a') && int(c) <= int('z')) {
        return int(c) - int('a') + 1;
    } else {
        return int(c) - int('A') + 27;
    }
}


int main() {
    ifstream ifs(ROOT + R"(src\day3\input1.txt)");
    if (!ifs.good()) throw runtime_error("File not exist");
    int sum = 0;
    string line;

    while (!ifs.eof()) {
        ifs >> line;
        if (line.size() % 2 != 0) throw logic_error("Line size error");
        int mid_after = int(line.size()) / 2;
        for (const auto c : line) {
            if (line.find(c, mid_after) != string::npos) {
                sum += get_score(c);
                cout << c << ": " << get_score(c) << endl;
                break;
            }
        }
    }
    cout << "Result: " << sum << endl;
}