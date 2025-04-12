class Solution {
public:
    string LCP(string a, string b) {
        size_t len = min(a.length(), b.length());
        size_t i = 0;
        while (i < len && a[i] == b[i]) {
            ++i;
        }
        return a.substr(0, i);
    }

    long long sumScores(string s) {
        long long sum = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            string si = s.substr(s.length() - 1 - i, i + 1);
            string p = LCP(si, s);
            cout << i << ": " << p.size() << '\n';
            sum += p.size();
        }
        return sum;
    }
};