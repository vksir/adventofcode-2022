#include "util.h"

using namespace std;

class Context {
public:
    vector<pair<string, string>> data;

    Context() {
        ifstream ifs("../src/day13/input1.txt");
        if (!ifs.good()) { throw runtime_error("File not exist"); }
        string s1, s2;
        while (!ifs.eof()) {
            ifs >> s1;
            ifs >> s2;
            data.emplace_back(s1, s2);
        }
        ifs.close();
    }
};

struct Packet {
    string s;
    vector<string> v;

    explicit Packet(string s) : s(std::move(s)) { init_v(); }

    void init_v() {
        string item;
        for (auto c: s) {
            if (c == '[' || c == ']') {
                if (!item.empty()) {
                    v.push_back(item);
                    item.clear();
                }
                v.emplace_back(1, c);
            } else if (c == ',') {
                if (!item.empty()) {
                    v.push_back(item);
                    item.clear();
                }
            } else {
                item += c;
            }
        }
    }

    static void convert_list(stack<string> &s) {
        string t = s.top();
        s.pop();
        s.emplace("]");
        s.push(t);
        s.emplace("[");
    }

    static void init_stack(const vector<string> &v, stack<string> &s) {
        for (int i = int(v.size()) - 1; i >= 0; --i) {
            s.push(v[i]);
        }
    }

    bool operator==(const Packet &other) const { return other.s == s; }

    bool operator<(const Packet &other) const {
//        fmt::print("Read:\n{}\n{}\n", v, other.v);
        stack<string> s1, s2;
        init_stack(v, s1);
        init_stack(other.v, s2);
        while (!s1.empty() && !s2.empty()) {
            if (s1.top() != s2.top()) {
                if (s1.top() != "[" && s1.top() != "]" && s2.top() != "[" && s2.top() != "]") {
                    int val1 = stoi(s1.top());
                    int val2 = stoi(s2.top());
                    if (val1 < val2) {
                        return true;
                    } else if (val1 > val2) {
                        return false;
                    }
                } else if (s1.top() == "]") {
                    return true;
                } else if (s2.top() == "]") {
                    return false;
                } else if (s1.top() == "[") {
                    assert(s2.top() != "]");
                    convert_list(s2);
                } else if (s2.top() == "[") {
                    assert(s1.top() != "]");
                    convert_list(s1);
                } else {
                    throw logic_error("Beyond expectation");
                }
            }
            s1.pop();
            s2.pop();
        }
        return s1.empty() && !s2.empty();
    }
};

class Solution1 {
public:
    int run(const Context &ctx) {
        for (int i = 0; i < ctx.data.size(); ++i) {
            if (Packet(ctx.data[i].first) < Packet(ctx.data[i].second)) {
//                fmt::print("Add: {}\n", i + 1);
                count += i + 1;
            }
        }
        return count;
    }

private:
    int count{0};
};

class Solution2 {
public:
    static int run(const Context &ctx) {
        vector<Packet> data;
        for (const auto &p: ctx.data) {
            data.emplace_back(p.first);
            data.emplace_back(p.second);
        }
        vector<Packet> targets;
        for (const auto &s: {"[[2]]", "[[6]]"}) {
            Packet packet(s);
            targets.push_back(packet);
            data.push_back(packet);
        }
        sort(data.begin(), data.end());
        int val = 1;
        for (const auto &t : targets) {
            val *= int(distance(data.begin(), find(data.begin(), data.end(), t))) + 1;
        }
        return val;
    }
};

int main(int argc, char *argv[]) {
    Context ctx;
    switch (util::get_part(argc, argv, 1)) {
        case 1: {
            fmt::print("Result1: {}\n", Solution1().run(ctx));
            break;
        }
        case 2: {
            fmt::print("Result2: {}\n", Solution2::run(ctx));
            break;
        }
    }
}