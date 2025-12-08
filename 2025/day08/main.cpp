#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Position {
    int x, y, z;
};

struct Edge {
    int u, v;
    ll weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

struct Input {
    vector<Position> boxes;
};

Input parse_input(istream& in) {
    Input data;
    string line;

    while (getline(in, line)) {
        for (char& ch : line)
            if (ch == ',') ch = ' ';

        istringstream iss(line);
        int x, y, z;
        iss >> x >> y >> z;

        data.boxes.push_back({x, y, z});
    }

    return data;
}

struct DSU {
    vector<int> parent;
    vector<int> comp_size;
    int comps;

    DSU(int n) : parent(n), comp_size(n, 1), comps(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) {
        if (parent[v] == v) return v;
        return parent[v] = find(parent[v]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        
        if (a != b) {
            if (comp_size[a] < comp_size[b])
                swap(a, b);
            
            parent[b] = a;
            comp_size[a] += comp_size[b];
            comps--;
        }
    }
};

vector<Edge> build_edges(const vector<Position>& boxes) {
    const int n = boxes.size();
    vector<Edge> edges;

    for (int i = 0; i < n; i++) {
        const auto& a = boxes[i];
        
        for (int j = i + 1; j < n; j++) {
            const auto& b = boxes[j];
            
            ll dx = a.x - b.x;
            ll dy = a.y - b.y;
            ll dz = a.z - b.z;
            ll dist2 = dx * dx + dy * dy + dz * dz;
            
            edges.push_back({i, j, dist2});
        }
    }

    sort(edges.begin(), edges.end());
    return edges;
}

string solve_part1(const Input& data, int k = 1000) {
    const auto& boxes = data.boxes;
    const int n = boxes.size();

    vector<Edge> edges = build_edges(boxes);
    DSU dsu(n);

    int steps = min(k, (int)edges.size());
    for (int i = 0; i < steps; i++)
        dsu.unite(edges[i].u, edges[i].v);

    vector<ll> sizes;
    for (int i = 0; i < n; i++) {
        if (dsu.find(i) == i)
            sizes.push_back(dsu.comp_size[i]);
    }

    sort(sizes.rbegin(), sizes.rend());

    ll result = 1;
    int take = min(3, (int)sizes.size());
    for (int i = 0; i < take; i++)
        result *= sizes[i];

    return to_string(result);
}

string solve_part2(const Input& data) {
    const auto& boxes = data.boxes;
    const int n = (int)boxes.size();

    vector<Edge> edges = build_edges(boxes);
    DSU dsu(n);

    Edge last = edges[0];
    for (const auto& edge : edges) {
        dsu.unite(edge.u, edge.v);
        if (dsu.comps == 1) {
            last = edge;
            break;
        }
    }

    ll result = 1LL * boxes[last.u].x * boxes[last.v].x;
    return to_string(result);
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int part = 1;
    if (argc >= 2) {
        part = stoi(argv[1]);
    }

    const Input data = parse_input(cin);

    if (part == 1) {
        // use for example.txt
        // cout << solve_part1(data, 10) << '\n';

        // use for input.txt
        cout << solve_part1(data) << '\n';
    } else if (part == 2) {
        cout << solve_part2(data) << '\n';
    } else {
        cerr << "Part must be 1 or 2\n";
        return 1;
    }

    return 0;
}
