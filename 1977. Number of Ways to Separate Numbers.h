#include <algorithm>
constexpr int mod = 1e9+7;

class Solution {
public:
    bool compare(string& num, int startPrev, int startLast, int len) {
        char prev, last;
        for (int i = 0; i < len; ++i) {
            prev = num[startPrev + i];
            last = num[startLast + i];
            if (prev < last) {
                return true;
            }
            if (prev > last) {
                return false;
            }
        }
        return true;
    }

    int numberOfCombinations(string num) {
        int n = num.size();
        vector<vector<int>> dp(n, vector<int>(n+1, 0));
        // dp[i][j] number of ways to split string with the last number ends at i and has length l
        for (int i = 0; i < n; ++i) {
            for (int l = 1; l <= i + 1; ++ l) {
                int j = i - l + 1;  // Position where last number starts

                // If last numbers starts with 0 it is not valid
                if (num[j] == '0') {
                    dp[i][l] = 0;
                } else if (j == 0) {
                    dp[i][l] = 1;   // Base case, last numbers start at position 0
                } else {
                    // Max length the second last number can have so it can be less or equal to last number
                    int maxl2 = 0;
                    // If last number starts at a position with value lower than l, the previous number is always smaller
                    if (j < l) {
                        maxl2 = j;
                    } else if (compare(num, j-l, j, l)) {
                        maxl2 = l; // If prev number is less or equal than last, we consider max length as l
                    } else {
                        maxl2 = l - 1;  // If prev is more than last, we onsidera max length as l - 1
                    }
                    for (int l2 = 0; l2 <= maxl2; ++l2) {
                        // We add the ways to split the string with the last number ending at j-1 with length l2
                        dp[i][l] = (dp[i][l] + dp[j-1][l2]) % mod;
                    }
                }
            }
        }
        // Return the sum of ways to split string with last number ending at n-1 with size[1,n]
        return accumulate(dp[n-1].begin(), dp[n-1].end(), 0);
    }
};