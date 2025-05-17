--Naive Aproach with Recursion

class Solution {
public:
    vector<int> A;

    int aux(int i) {
        int maxLen = 0;
        for (int j = 0; j < i; j++) {
            if (A[j] < A[i]) {
                maxLen = max(maxLen, aux(j));
            }
        }
        return 1 + maxLen;
    }

    int lengthOfLIS(const vector<int>& nums) {
        int n = nums.size();
        A = nums;
        int maxLen = 0;
        for (int i = 0; i < n; i++) {
            maxLen = max(maxLen, aux(i));
        }
        return maxLen;
    }
};