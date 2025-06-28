class Solution {
    vector<int> arr;

    int burst(const int &left, const int &right) {
        // There are no balloons between
        if (left + 1 == right) return 0;

        int maxCoins = 0;
        for (int i = left + 1; i < right; i++) {
            maxCoins = max(maxCoins, 
            burst(left, i) + burst(i, right) + arr[left] * arr[i] * arr[right]
            );
        }
        return maxCoins;
    }

public:
    int maxCoins(vector<int>& nums) {
        arr.reserve(nums.size() + 1);
        arr.push_back(1);
        arr.insert(arr.end(), nums.begin(), nums.end());
        arr.push_back(1);

        return burst(0, arr.size() - 1);
    }
};