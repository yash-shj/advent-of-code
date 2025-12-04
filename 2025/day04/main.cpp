#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

struct Input {
    vector<string> grid;
};

Input parse_input(istream& in) {
    Input data;

    string line;
    while (getline(in, line)) 
        data.grid.push_back(line);
    
    return data;
}

const vector<pii> dir = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1}, /*{0, 0},*/ {0, 1},
    {1, -1},  {1, 0},  {1, 1}
};

int count_adjacent(const vector<string>& grid, const int& r, const int& c) {
    int cnt = 0;
    
    for (const auto& [dx, dy] : dir) {
        int nr = r + dx;
        int nc = c + dy;
        
        if (nr >= 0 && nr < grid.size() && nc >= 0 && nc < grid[nr].size())
            cnt += (grid[nr][nc] == '@');
    }

    return cnt;
}

string solve_part1(const Input& data) {
    const auto& grid = data.grid;
    ll total = 0;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '@') 
                total += (count_adjacent(grid, i, j) < 4);
        }
    }

    return to_string(total);
}

string solve_part2(const Input& data) {
    auto grid = data.grid;
    const int rows = grid.size();
    const int cols = grid[0].size();

    vector<vector<int>> deg(rows, vector<int>(cols, 0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '@') 
                deg[i][j] = count_adjacent(grid, i, j);
        }
    }

    queue<pii> q;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '@' && deg[i][j] < 4)
                q.push({i, j});
        }
    }

    ll total = 0;
    while (!q.empty()) {
        auto [r, c] = q.front(); 
        q.pop();
        
        if (grid[r][c] != '@') continue;

        grid[r][c] = 'X';
        total++;

        for (const auto& [dx, dy] : dir) {
            int nr = r + dx;
            int nc = c + dy;

            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == '@') {
                deg[nr][nc]--;
                if (deg[nr][nc] == 3) q.push({nr, nc});
            }
        }
    }

    return to_string(total);
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int part = 1;
    if (argc >= 2) part = stoi(argv[1]);

    const Input data = parse_input(cin);

    if (part == 1) {
        cout << solve_part1(data) << '\n';
    } else if (part == 2) {
        cout << solve_part2(data) << '\n';
    } else {
        cerr << "Part must be 1 or 2\n";
        return 1;
    }

    return 0;
}
