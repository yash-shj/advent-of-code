#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Input {
    vector<string> manifold;
    int start;
};

Input parse_input(istream& in) {
    Input data;
    
    string line;
    while (getline(in, line)) 
        data.manifold.push_back(line);

    for (int i = 0; i < data.manifold[0].size(); i++) {
        if (data.manifold[0][i] == 'S') {
            data.start = i;
            break;
        }
    }

    return data;
}

string solve_part1(const Input& data) {
    const auto& manifold = data.manifold;
    const int rows = manifold.size();
    const int cols = manifold[0].size();

    ll splits = 0;
    set<int> beams;
    beams.insert(data.start);

    for (int i = 1; i < rows; i++) {
        set<int> next_beams;
        
        for (const int& pos : beams) {
            const char& cell = manifold[i][pos];
            
            if (cell == '.') {
                next_beams.insert(pos);
            } else if (cell == '^') {
                splits++;
                if (pos > 0) next_beams.insert(pos - 1);
                if (pos < cols - 1) next_beams.insert(pos + 1);
            } 
        }

        beams = next_beams;
    }
    
    return to_string(splits);
}

string solve_part2(const Input& data) {
    const auto& manifold = data.manifold;
    const int rows = manifold.size();
    const int cols = manifold[0].size();

    // dp[i][j] = number of active timelines at manifold[i][j]
    // if manifold[i][j] == '.', dp[i + 1][j] += dp[i][j]
    // if manifold[i][j] == '^', dp[i + 1][j - 1] += dp[i][j] and dp[i + 1][j + 1] += dp[i][j]

    vector<vector<ll>> dp(rows, vector<ll>(cols, 0));
    dp[0][data.start] = 1;

    for (int i = 1; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (manifold[i - 1][j] == '.' || manifold[i - 1][j] == 'S') 
                dp[i][j] += dp[i - 1][j];
            
            if (j > 0 && manifold[i - 1][j - 1] == '^')
                dp[i][j] += dp[i - 1][j - 1];

            if (j < cols - 1 && manifold[i - 1][j + 1] == '^') 
                dp[i][j] += dp[i - 1][j + 1];
        }
    }

    ll timelines = 0;
    for (const ll& count : dp[rows - 1])
        timelines += count;
    
    return to_string(timelines);
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
