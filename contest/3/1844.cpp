#include <cstdio>
#include <iostream>

using namespace std;

struct Position {
    int x, y, z;
    Position(int x_ = 0, int y_ = 0, int z_ = 0) {
        int sum = x_ + y_ + z_;
        x = min(x_, min(y_, z_));
        z = max(x_, max(y_, z_));
        y = sum - x - z;
    }
    bool operator==(const Position &other) { return x == other.x && y == other.y && z == other.z; }
};

pair<int, Position> step(Position org) {
    int dist = 0;
    int diff1 = org.y - org.x;
    int diff2 = org.z - org.y;
    Position nex;
    if (diff1 == diff2) {
        return {0, org};
    } else if (diff1 < diff2) { // right move, e.g. 2 4 9 -> 4 6 9 -> 6 8 9
        dist += (diff2 - 1) / diff1; // here -1 is for cases like 2 4 10 -> 4 6 10 -> 6 8 10
        nex.z = org.z;
        nex.y = nex.z - (diff2 - 1) % diff1 - 1;
        nex.x = nex.y - diff1;
    } else { // left move, e.g. 2 7 9 -> 2 5 7 -> 2 3 5
        dist += (diff1 - 1) / diff2;
        nex.x = org.x;
        nex.y = nex.x + (diff1 - 1) % diff2 + 1;
        nex.z = nex.y + diff2;
    }
    return {dist, nex};
}

pair<int, Position> root(Position org) {
    int dist = 0;
    while (true) {
        auto res = step(org);
        if (!res.first) {
            break;
        } else {
            dist += res.first;
            org = res.second;
        }
    }
    return make_pair(dist, org);
}

int main() {
    int a, b, c, x, y, z;
    cin >> a >> b >> c >> x >> y >> z;
    Position org(a, b, c);
    Position tar(x, y, z);
    auto u = root(org);
    auto v = root(tar);
    if (!(u.second == v.second)) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    if (u.first < v.first) {
        swap(u, v);
        swap(org, tar);
    }
    int dist = 0;
    while (true) {
        auto nex_org = step(org);
        auto nex_tar = step(tar);
        if (nex_org.second == nex_tar.second) {
            break;
        } else if (u.first - nex_org.first < v.first - nex_tar.first) {
            dist += nex_tar.first;
            v.first -= nex_tar.first;
            tar = nex_tar.second;
        } else {
            dist += nex_org.first;
            u.first -= nex_org.first;
            org = nex_org.second;
        }
    }
    if (org == tar) {
        cout << dist << endl;
    } else if ((org.y * 2 - org.x - org.z) * (tar.y * 2 - tar.x - tar.z) < 0) {
        cout << dist + u.first + v.first << endl;
    } else {
        cout << dist + abs(u.first - v.first) << endl;
    }
    return 0;
}