//This solution passes 21/55 tests cases
// Gets TLE on the rest

class Solution {
public:
    int aux(const vector<int>& nums, int next, int index) {
        if (index < 0) {
            return 0;
        }
        // There are two posibilities, including or exclduing current number
        // Depending if the context i maybe result in a shorter or larger subsequence
        int exclude = aux(nums, next, index - 1);
        int include = 0;
        // We must verify if current numbers is lower than the expected next number
        if (nums[index] < next) {
            include = 1 + aux(nums, nums[index], index - 1);
        }
        return max(exclude, include);
    }

    int lengthOfLIS(const vector<int>& nums) {
        return aux(nums, INT_MAX, nums.size() - 1);
    }
};