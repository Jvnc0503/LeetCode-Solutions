class Solution {
    vector<int> arr;
    vector<vector<int>> dp;

    // Time O(n^3)
    // Space O(n^2)
    int burst(const int &left, const int &right) {
        // There are no balloons between
        if (left + 1 == right) return 0;

        // Check if result already present in memory
        if (dp[left][right] != -1) return dp[left][right];

        int maxCoins = 0;
        for (int i = left + 1; i < right; i++) {
            maxCoins = max(maxCoins, 
            burst(left, i) + burst(i, right) + arr[left] * arr[i] * arr[right]
            );
        }
        dp[left][right] = maxCoins;
        return maxCoins;
    }

public:
    int maxCoins(vector<int>& nums) {
        arr.reserve(nums.size() + 1);
        arr.push_back(1);
        arr.insert(arr.end(), nums.begin(), nums.end());
        arr.push_back(1);
        dp.assign(arr.size(), vector<int>(arr.size(), -1));

        return burst(0, arr.size() - 1);
    }
};