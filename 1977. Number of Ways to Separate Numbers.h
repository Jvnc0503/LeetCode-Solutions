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

    bool compareFaster(string& num, int startPrev, int startLast, int len) {
        return memcmp(&num[startPrev], &num[startLast], len) <= 0;
    }

    int numberOfCombinations(string num) {
        int n = num.size();
        // dp[i][j] number of ways to split string with the last number ends at i and has length l
        //vector<vector<int>> dp(n, vector<int>(n+1, 0));
        // preSum[i][j] number of ways to split string with last number ending at i with length from 1 t
        vector<vector<int>> preSum(n, vector<int>(n+1, 0));
        for (int i = 0; i < n; ++i) {
            for (int l = 1; l <= i + 1; ++ l) {
                int j = i - l + 1;  // Position where last number starts
                int cur = 0;    // Save ways for current dp[i][j]

                // If last numbers starts with 0 it is not valid
                if (num[j] == '0') {
                    //dp[i][l] = 0;
                    cur = 0;
                } else if (j == 0) {
                    //dp[i][l] = 1;   // Base case, last numbers start at position 0
                    cur = 1;
                } else {
                    // Max length the second last number can have so it can be less or equal to last number
                    int maxl2 = 0;
                    // If last number starts at a position with value lower than l, the previous number is always smaller
                    if (j < l) {
                        maxl2 = j;
                    } else if (compareFaster(num, j-l, j, l)) {
                        maxl2 = l; // If prev number is less or equal than last, we consider max length as l
                    } else {
                        maxl2 = l - 1;  // If prev is more than last, we onsidera max length as l - 1
                    }
                    /*for (int l2 = 0; l2 <= maxl2; ++l2) {
                        // We add the ways to split the string with the last number ending at j-1 with length l2
                        dp[i][l] = (dp[i][l] + dp[j-1][l2]) % mod;
                    }*/
                    //dp[i][l] = preSum[j-1][maxl2];
                    cur = preSum[j-1][maxl2];
                }
                //preSum[i][l] = (preSum[i][l-1] + dp[i][l]) % mod;
                preSum[i][l] = (preSum[i][l-1] + cur) % mod;
            }
        }
        // Return the sum of ways to split string with last number ending at n-1 with size[1,n]
        return preSum[n-1][n] % mod;
    }
};