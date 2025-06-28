class Solution {
public:
    int maxCoins(vector<int>& nums) {
        vector<int> arr;
        arr.reserve(nums.size() + 1);
        arr.push_back(1);
        arr.insert(arr.end(), nums.begin(), nums.end());
        arr.push_back(1);

        const int n = arr.size();
        vector<vector<int>> dp;
        dp.assign(n, vector<int>(n, 0));

        for (int dist = 2; dist < n; dist++) {
            for (int left = 0; left + dist < n; left++) {
                const int right = left + dist;
                for (int i = left + 1; i < right; i++) {
                    dp[left][right] = max(dp[left][right],
                        dp[left][i] + dp[i][right] + arr[left] * arr[i] * arr[right]
                    );
                }
            }
        }

        return dp[0][n - 1];
    }
};