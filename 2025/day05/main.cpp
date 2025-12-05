#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
#define ff first
#define ss second

struct Input {
    vector<pll> ranges;
    vector<ll> ids;
};

Input parse_input(istream& in) {
    Input data;
    
    string line;
    while (getline(in, line)) {
        if (line.empty()) break;
        
        int dash = line.find('-');
        ll start = stoll(line.substr(0, dash));
        ll end = stoll(line.substr(dash + 1));
        data.ranges.emplace_back(start, end);
    }

    sort(data.ranges.begin(), data.ranges.end());
    
    vector<pll> merged;
    for (const auto& r : data.ranges) {
        if (merged.empty() || merged.back().ss < r.ff)
            merged.push_back(r);
        else 
            merged.back().ss = max(merged.back().ss, r.ss);
    }
    data.ranges = merged;

    while (getline(in, line)) {
        if (line.empty()) continue;
        data.ids.push_back(stoll(line));
    }

    return data;
}

string solve_part1(const Input& data) {
    const auto& ranges = data.ranges;   
    ll cnt = 0;

    for (ll id : data.ids) {
        auto it = upper_bound(
            ranges.begin(), 
            ranges.end(), 
            pll{id, LLONG_MAX}
        );
        
        if (it == ranges.begin()) continue;
        it--;

        ll start = it->ff;
        ll end = it->ss;
        if (start <= id && id <= end) cnt++;
    }

    return to_string(cnt);
}

string solve_part2(const Input& data) {
    ll cnt = 0;

    for (const auto& [l, r] : data.ranges) 
        cnt += (r - l + 1);
    
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
