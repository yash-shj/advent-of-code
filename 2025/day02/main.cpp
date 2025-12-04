#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Input {
    vector<pair<ll, ll>> ranges;
};

Input parse_input(istream& in) {
    Input data;
    
    string s;
    getline(in, s);

    stringstream ss(s);
    string temp;
    
    while (getline(ss, temp, ',')) {
        int dash = temp.find('-');

        ll start = stoll(temp.substr(0, dash));
        ll end = stoll(temp.substr(dash + 1));
        data.ranges.push_back({start, end});
    }

    return data;
}

bool is_invalid_part1(const ll& x) {
    const string t = to_string(x);
    if (t.size() & 1) return false;

    const int half = t.size() / 2;
    for (int j = 0; j < half; j++) {
        if (t[j] != t[half + j]) return false;
    }

    return true;
}

string solve_part1(const Input& data) {
    ll res = 0;

    for (const auto& [start, end] : data.ranges) {
        for (ll x = start; x <= end; x++) {
            if (is_invalid_part1(x)) 
                res += x;
        }
    }

    return to_string(res);
}

bool is_invalid_part2(const ll& x) {
    const string t = to_string(x);

    const int n = t.size();
    for (int len = 1; len <= n / 2; len++) {
        if (n % len != 0) continue;

        bool match = true;
        for (int j = len; j < n; j++) {
            if (t[j] != t[j % len]) {
                match = false;
                break;
            }
        }

        if (match) return true;
    }

    return false;
}

string solve_part2(const Input& data) {
    ll res = 0;

    for (const auto& [start, end] : data.ranges) {
        for (ll x = start; x <= end; x++) {
            if (is_invalid_part2(x)) 
                res += x;
        }
    }

    return to_string(res);
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
