class Solution {
public:
    //We know the merged array would habe n + m elements
    //So the median would be (n + m)/2 if odd or abv((m+n)/2, (m+n)/2 + 1)) if even
    //We dont need to iterate all elements, just ~(m+n)/2 elements
    //Complexity O(m+n)
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        size_t n = nums1.size(), m = nums2.size();
        size_t odd = (n + m) % 2;
        size_t mid = (n+m)/2 + 1;
        size_t p1 = 0, p2 = 0;
        int prev = 0, cur = 0;

        for (size_t i = 0; i < mid; ++i) {
            prev = cur;
            if (p1 < n && (p2 >= m || nums1[p1] < nums2[p2])) {
                cur = nums1[p1++];
            } else {
                cur = nums2[p2++];
            }
        }

        if (odd) {
            return cur;
        }
        return (prev + cur) / 2.0;
    }
};