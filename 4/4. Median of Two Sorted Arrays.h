class Solution {
public:
    //This solution was based on editorial approach 3
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        auto& A = nums1.size() <= nums2.size() ? nums1 : nums2;
        auto& B = nums1.size() <= nums2.size() ? nums2 : nums1;
        size_t n = A.size(), m = B.size();
        size_t left = 0, right = n;
        while (left <= right) {
            size_t partitionA = (left + right)/2;
            size_t partitionB = (n + m + 1)/2 - partitionA;

            int maxLeftA = (partitionA != 0) ? A[partitionA - 1] : INT_MIN;
            int minRightA = (partitionA != n) ? A[partitionA] : INT_MAX;
            int maxLeftB = (partitionB != 0) ? B[partitionB - 1] : INT_MIN;
            int minRightB = (partitionB != m) ? B[partitionB] : INT_MAX;

            if (maxLeftA <= minRightB && maxLeftB <= minRightA) {
                return (n+m)%2 ? max(maxLeftA, maxLeftB) : (max(maxLeftA, maxLeftB) + min(minRightA, minRightB)) / 2.0;
            } else if (maxLeftA > minRightB) {
                right = partitionA - 1;
            } else {
                left = partitionA + 1;
            }
        }
        return 0.0;
    }
};