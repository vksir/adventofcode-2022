#include "../util.h"

using namespace std;

const int MAX_SIZE = 100000;

enum type { T_FILE, T_DIR };

struct node {
    type type;
    string name;
    int size;
    node* father;
    unordered_map<string, node*> sons;
};

void calc_size(node* n, int& total_size) {
    int size = 0;
    for (const auto &p : n->sons) {
        if (p.second->type == T_FILE) {
            size += p.second->size;
        } else {
            calc_size(p.second, total_size);
            assert(p.second->size != -1);
            size += p.second->size;
        }
    }
    n->size = size;
    if (size <= MAX_SIZE) total_size += size;
    cout << "Finish calc: " << n->name << ", " << size << endl;
}


int main() {
    ifstream ifs(ROOT + R"(src\day7\input1.txt)");
    if (!ifs.good()) { throw runtime_error("File not exist"); }

    regex cd_pattern(R"(\$ cd (.+))");
    regex ls_pattern(R"(\$ ls)");
    regex dir_pattern(R"(dir (.+))");
    regex file_pattern(R"((\d+) (.+))");

    string line;
    smatch res;
    bool read = true;
    node root{T_DIR, "/", 0, nullptr, unordered_map<string, node*>()};
    node* cur_node = &root;
    while (!ifs.eof()) {
        if (read) {
            getline(ifs, line);
            cout << "Read: " << line << endl;
        } else {
            read = true;
        }

        if (regex_match(line, res, cd_pattern)) {
            if (res[1] == "/") {
                cur_node = &root;
            } else if (res[1] == "..") {
                cur_node = cur_node->father;
            } else {
                if (cur_node->sons.find(res[1]) != cur_node->sons.end()) {
                    cur_node = cur_node->sons[res[1]];
                } else {
                    node* son_p = new node{T_DIR, res[1], -1, cur_node, unordered_map<string, node*>()};
                    cur_node->sons[res[1]] = son_p;
                    cur_node = son_p;
                }
            }
        } else if (regex_match(line, res, ls_pattern)) {
            while (!ifs.eof()) {
                getline(ifs, line);
                cout << "Read: " << line << endl;
                if (regex_match(line, res, dir_pattern)) {
                    string name = res[1];
                    if (cur_node->sons.find(name) == cur_node->sons.end()) {
                        node* son_p = new node{T_DIR, name, -1, cur_node, unordered_map<string, node*>()};
                        cur_node->sons[name] = son_p;
                    }
                } else if (regex_match(line, res, file_pattern)) {
                    string name = res[2];
                    int size = stoi(res[1]);
                    if (cur_node->sons.find(name) == cur_node->sons.end()) {
                        node* son_p = new node{T_FILE, name, size, cur_node, unordered_map<string, node*>()};
                        cur_node->sons[name] = son_p;
                    }
                } else {
                    read = false;
                    break;
                }
            }
        } else {
            throw logic_error("Regex failed");
        }
    }

    int total_size = 0;
    calc_size(&root, total_size);
    cout << "Result: " << total_size << endl;
}