#include "util.h"

using namespace std;

struct Point {
    int x;
    int y;
    int z;

    string to_string() const { return fmt::format("({}, {}, {})", x, y, z); }
};

struct PointHash {
    size_t operator()(const Point &p) const {
        auto h1 = hash<int>{}(p.x);
        auto h2 = hash<int>{}(p.y);
        auto h3 = hash<int>{}(p.z);
        return h1 ^ h2 ^ h3;
    }
};

struct PointEqual {
    bool operator()(const Point &p1, const Point &p2) const {
        return p1.x == p2.x && p1.y == p2.y && p1.z == p2.z;
    }
};

const vector<Point> DIRECTION{
        {-1, 0, 0}, {1, 0, 0}, {0, -1, 0},
        {0, 1, 0}, {0, 0, -1}, {0, 0, 1},
};

class Context {
public:
    vector<Point> data;

    explicit Context(const string &path) {
        ifstream ifs(path);
        if (!ifs.good()) { throw logic_error("File not exist: " + path); }

        string line;
        while (!ifs.eof()) {
            getline(ifs, line);
            auto v = util::parse_int(line);
            assert(v.size() == 3);
            data.push_back({v[0], v[1], v[2]});
        }
    }
};

class BaseSolution {
public:
    explicit BaseSolution(Context ctx) : ctx(std::move(ctx)) {
        for (const auto &p: this->ctx.data) {
            points.insert(p);
        }
    }

protected:
    Context ctx;
    unordered_set<Point, PointHash, PointEqual> points;
};

class Solution1 : BaseSolution {
public:
    explicit Solution1(Context ctx) : BaseSolution(std::move(ctx)) {}

    int run() {
        int area{0};
        for (const auto &p: ctx.data) {
            for (const auto &d: DIRECTION) {
                if (points.find(Point{p.x + d.x, p.y + d.y, p.z + d.z}) == points.end()) { area++; }
            }
        }
        return area;
    }
};

class Solution2 : BaseSolution {
public:
    explicit Solution2(Context ctx) : BaseSolution(std::move(ctx)) {
        for (const auto &p: points) {
            min_x = min(min_x, p.x);
            max_x = max(max_x, p.x);
            min_y = min(min_y, p.y);
            max_y = max(max_y, p.y);
            min_z = min(min_z, p.z);
            max_z = max(max_z, p.z);
        }
    }

    int run() {
        int area{0};
        for (const auto &p: ctx.data) {
            for (const auto &d: DIRECTION) {
                if (bfs(Point{p.x + d.x, p.y + d.y, p.z + d.z})) { area++; }
            }
        }
        return area;
    }

protected:
    int min_x{INT_MAX}, max_x{INT_MIN}, min_y{INT_MAX}, max_y{INT_MIN}, min_z{INT_MAX}, max_z{INT_MIN};
    unordered_set<Point, PointHash, PointEqual> inside_points;
    unordered_set<Point, PointHash, PointEqual> outside_points;

    bool outside(int x, int y, int z) const {
        return x < min_x || x > max_x || y < min_y || y > max_y || z < min_z || z > max_z;
    }

    // Return true if search outside
    bool bfs(const Point &root) {
        if (points.find(root) != points.end()) { return false; }
        unordered_set<Point, PointHash, PointEqual> visited{root};
        vector<Point> cur_points{root};
        while (!cur_points.empty()) {
            vector<Point> next_points{};
            for (const auto &p: cur_points) {
                for (const auto &d: DIRECTION) {
                    Point next_point{p.x + d.x, p.y + d.y, p.z + d.z};
                    if (points.find(next_point) != points.end() || visited.find(next_point) != visited.end()) {
                        continue;
                    }
                    if (outside(next_point.x, next_point.y, next_point.z) ||
                        outside_points.find(next_point) != outside_points.end()) {
                        for (const auto &v: visited) { outside_points.insert(v); }
                        return true;
                    }
                    if (inside_points.find(next_point) != inside_points.end()) {
                        for (const auto &v: visited) { inside_points.insert(v); }
                        return false;
                    }
                    visited.insert(next_point);
                    next_points.push_back(next_point);
                }
            }
            cur_points = next_points;
        }
        for (const auto &v: visited) { inside_points.insert(v); }
        return false;
    }
};

int main() {
    Context ctx(util::get_input_path(__FILE__, "input.txt"));
    util::timeit<1>([ctx]() {
        fmt::print("Part1: {}\n", Solution1(ctx).run());
        fmt::print("Part2: {}\n", Solution2(ctx).run());
    });
}