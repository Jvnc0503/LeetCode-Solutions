class Solution {
public:
    vector<int> A;
    vector<int> mem;

    int aux(int i) {
        if (mem[i] != -1) {
            return mem[i];
        }
        int maxLen = 0;
        for (int j = 0; j < i; j++) {
            if (A[j] < A[i]) {
                maxLen = max(maxLen, aux(j));
            }
        }
        return mem[i] = 1 + maxLen;
    }

    int lengthOfLIS(const vector<int>& nums) {
        int n = nums.size();
        A = nums;
        mem = vector<int>(n, -1);
        int result = 0;
        for (int i = 0; i < n; i++) {
            result = max(result, aux(i));
        }
        return result;
    }
};