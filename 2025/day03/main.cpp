#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Input {
    vector<string> banks;
};

Input parse_input(istream& in) {
    Input data;
    
    string line;
    while (getline(in, line)) 
        data.banks.push_back(line);

    return data;
}

string solve_part1(const Input& data) {
    ll total = 0;
    
    for (const auto& bank : data.banks) {
        ll best = 0;
        
        for (int i = 0; i < bank.size(); i++) {
            for (int j = i + 1; j < bank.size(); j++) {

                ll a = bank[i] - '0';
                ll b = bank[j] - '0';
                ll val = a * 10 + b;
                
                best = max(best, val);
            }
        }

        total += best;
    }

    return to_string(total);
}

string solve_part2(const Input& data) {
    const ll digits = 12;
    ll total = 0;

    for (const auto& bank : data.banks) {
        string s;

        for (int i = 0; i < bank.size(); i++) {
            while (!s.empty() && s.back() < bank[i] && s.size() + (bank.size() - i) > digits) 
                s.pop_back();
            s.push_back(bank[i]);
        }

        total += stoll(s.substr(0, digits));
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
