#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Input {
    // add fields here
};

Input parse_input(istream& in) {
    Input data;
    // parse input into data
    return data;
}

string solve_part1(const Input& data) {
    // code for part 1
    return "";
}

string solve_part2(const Input& data) {
    // code for part 2
    return "";
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
