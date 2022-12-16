#include "util.h"

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
    if (!ifs.good()) { throw runtime_error("File not exist"); }
    int sum = 0;
    array<string, 3> g;

    while (!ifs.eof()) {
        for (int i = 0; i < 3; i++) ifs >> g[i];
        for (const auto c : g[0]) {
            if (g[1].find(c) != string::npos && g[2].find(c) != string::npos) {
                sum += get_score(c);
                break;
            }
        }
    }
    cout << "Result: " << sum << endl;
}