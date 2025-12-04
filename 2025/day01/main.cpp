#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Instr {
    char dir;  
    int dist;  
};

struct Input {
    vector<Instr> moves;
};

Input parse_input(istream& in) {
    Input data;

    string line;
    while (getline(in, line)) {
        char dir = line[0];
        int dist = stoi(line.substr(1));
        data.moves.push_back(Instr{dir, dist});
    }

    return data;
}

const int START = 50;
const int MOD = 100;

string solve_part1(const Input& data) {
    int pos = START;
    int cnt = 0;

    for (const auto& [dir, dist] : data.moves) {
        if (dir == 'L') 
            pos = ((pos - dist) % MOD + MOD) % MOD;
        else if (dir == 'R') 
            pos = (pos + dist) % MOD;

        cnt += (pos == 0);
    }

    return to_string(cnt);
}

string solve_part2(const Input& data) {
    int pos = START;
    ll cnt = 0;

    for (const auto& [dir, dist] : data.moves) {
        int d = dist;  

        if (dir == 'L') {
            while (d--) {
                pos = (pos - 1 + MOD) % MOD;
                if (pos == 0) cnt++;
            }
        } else if (dir == 'R') {
            while (d--) {
                pos = (pos + 1) % MOD;
                if (pos == 0) cnt++;
            }
        }
    }

    return to_string(cnt);
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
