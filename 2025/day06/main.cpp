#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Input {
    vector<string> lines;
    vector<pair<int, int>> groups;
};

Input parse_input(istream& in) {
    Input data;

    vector<string> lines;
    string line;
    while (getline(in, line)) 
        data.lines.push_back(line);
        
    int R = data.lines.size();
    int C = data.lines[0].size();

    vector<bool> used(C, false);
    for (int c = 0; c < C; c++) {
        for (int r = 0; r < R; r++) {
            char ch = data.lines[r][c];
            if (isdigit(ch) || ch == '+' || ch == '*') {
                used[c] = true;
                break;
            }
        }
    }

    int i = 0;
    while (i < C) {
        if (!used[i]) {
            i++;
            continue;
        }

        int start = i;
        while (i < C && used[i]) i++;
        
        int end = i - 1;
        data.groups.push_back({start, end});
    }

    return data;
}

string solve_part1(const Input& data) {
    ll total = 0;

    for (const auto& [start, end] : data.groups) {
        vector<ll> nums;
        for (int r = 0; r < data.lines.size() - 1; r++) {
            string t;
            for (int c = start; c <= end; c++) {
                char ch = data.lines[r][c];
                if (isdigit(ch)) t += ch;
            }
            nums.push_back(stoll(t));
        }

        int rows = data.lines.size();
        char op = data.lines[rows - 1][start];
        if (op == '+') {
            ll sum = 0;
            for (const ll& num : nums)
                sum += num;
            total += sum;
        } else if (op == '*') {
            ll prod = 1;
            for (const ll& num : nums)
                prod *= num;
            total += prod;
        }
    }

    return to_string(total);
}

string solve_part2(const Input& data) {
    ll total = 0;

    for (auto& [start, end] : data.groups) {
        vector<ll> nums;
        for (int c = end; c >= start; c--) {
            string t;
            for (int r = 0; r < data.lines.size() - 1; r++) {
                char ch = data.lines[r][c];
                if (isdigit(ch)) t += ch;
            }
            nums.push_back(stoll(t));
        }

        int rows = data.lines.size();
        char op = data.lines[rows - 1][start];
        if (op == '+') {
            ll sum = 0;
            for (const ll& num : nums)
                sum += num;
            total += sum;
        } else if (op == '*') {
            ll prod = 1;
            for (const ll& num : nums)
                prod *= num;
            total += prod;
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
