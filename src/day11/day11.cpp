#include "util.h"

using namespace std;

enum Operator {
    ADD, MULTIPLY
};

struct Operation {
    Operator op;
    int64_t val_b;

    int64_t operate(int64_t val_a, const function<int64_t(int64_t)> &optimizer) const {
        auto real_val_b = val_b == -1 ? val_a : val_b;
        if (op == MULTIPLY) {
            return optimizer(val_a * real_val_b);
        } else if (op == ADD) {
            return optimizer(val_a + real_val_b);
        } else {
            throw logic_error("Invalid op");
        }
    }
};

struct Monkey {
    int id{};
    vector<int64_t> items;
    Operation operation{};
    int divisor{};
    int target_true{};
    int target_false{};
    int64_t inspection{0};

    string to_string() const {
        return fmt::format("Monkey_{}({}, count={})", id, items, inspection);
    }

    bool operator<(const Monkey &other) const {
        return this->inspection < other.inspection;
    }
};


vector<Monkey> read() {
    vector<Monkey> monkeys;
    ifstream ifs("../src/day11/input1.txt");
    if (!ifs.good()) { throw runtime_error("File not exist"); }

    array<regex, 6> patterns = {
            regex(R"(Monkey (.+):)"),
            regex(R"(  Starting items: (.+))"),
            regex(R"(  Operation: new = old (.+) (.+))"),
            regex(R"(  Test: divisible by (.+))"),
            regex((R"(    If true: throw to Monkey (.+))")),
            regex((R"(    If false: throw to Monkey (.+))")),
    };
    string line;
    smatch res;
    while (!ifs.eof()) {
        Monkey m;
        for (int i = 0; i < patterns.size(); ++i) {
            getline(ifs, line);
            if (!regex_match(line, res, patterns[i])) {
                throw logic_error(fmt::format("Regex failed: i={}, line={}", i, line));
            }
            switch (i) {
                case 0:
                    m.id = stoi(res[1]);
                    break;
                case 1:
                    for (const auto &item: util::split(res[1])) {
                        m.items.push_back(stoi(item));
                    }
                    break;
                case 2:
                    switch (string(res[1])[0]) {
                        case '+':
                            m.operation.op = ADD;
                            break;
                        case '*':
                            m.operation.op = MULTIPLY;
                            break;
                        default:
                            throw logic_error("Invalid operator");
                    }
                    if (res[2] == "old") {
                        m.operation.val_b = -1;
                    } else {
                        m.operation.val_b = stoi(res[2]);
                        if (m.operation.val_b == -1) {
                            throw logic_error("Operation value conflict");
                        }
                    }
                    break;
                case 3:
                    m.divisor = stoi(res[1]);
                    break;
                case 4:
                    m.target_true = stoi(res[1]);
                    break;
                case 5:
                    m.target_false = stoi(res[1]);
                    break;
                default:
                    throw logic_error("Invalid index");
            }
        }
        monkeys.push_back(m);
        if (!ifs.eof()) { getline(ifs, line); }
    }

    ifs.close();
    return monkeys;
}

class Solution {
public:
    explicit Solution(int round, const function<int64_t(int64_t)> &optimizer) : round(round), optimizer(optimizer) {}

    int64_t run(vector<Monkey> &monkeys) const {
        for (int i = 0; i < round; ++i) {
            for (auto &m: monkeys) {
                for (auto val: m.items) {
                    auto new_val = m.operation.operate(val, optimizer);
                    auto target = new_val % m.divisor == 0 ? m.target_true : m.target_false;
                    monkeys[target].items.push_back(new_val);
                }
                m.inspection += int64_t(m.items.size());
                m.items.clear();
            }
//            for (const auto &m: monkeys) {
//                fmt::print("Round_{}: {}\n", i + 1, m.to_string());
//            }
        }
        sort(monkeys.begin(), monkeys.end());
        return monkeys[monkeys.size() - 1].inspection * monkeys[monkeys.size() - 2].inspection;
    }

private:
    int round;
    function<int64_t(int64_t)> optimizer;
};

int main(int argc, char *argv[]) {
    auto monkeys = read();
    switch (util::get_part(argc, argv, 1)) {
        case 1: {
            Solution s(20, [](int64_t val) -> int64_t {
                return val / 3;
            });
            fmt::print("Result: {}\n", s.run(monkeys));
            break;
        }
        case 2: {
            int64_t k = 1;
            for (const auto &m: monkeys) { k *= m.divisor; }
            Solution s(10000, [k](int64_t val) -> int64_t {
                return val % k;
            });
            fmt::print("Result: {}\n", s.run(monkeys));
            break;
        }
    }
}