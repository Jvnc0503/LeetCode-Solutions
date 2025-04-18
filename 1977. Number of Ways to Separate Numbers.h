class Solution {
public:
    int numberOfCombinations(string num) {
        if (num[0] == '0') {
            return 0;
        }
        const int n = num.size();
        const int mod = 1e9+7;
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int j = 0; j < n; ++j) {
            dp[0][j] = 1;
        }

        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                continue;
            }
            for (int j = i; j < n; ++j) {
                int lenLast = j - i + 1;
                for (int k = 0; k < i; ++k) {
                    int lenPrev = i - k;
                    if (lenPrev < lenLast || (lenPrev == lenLast && memcmp(&num[k], &num[i], lenLast) <= 0)) {
                        dp[i][j] = (dp[i][j] + dp[k][i-1]) % mod;
                    }
                }
            }
        }
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum = (sum + dp[i][n-1]) % mod;
        }
        return sum;
    }
};