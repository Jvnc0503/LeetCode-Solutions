/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include <vector>

class Solution {
public:
    vector<size_t> f(TreeNode* node) {
        // Index 0: Case where all the nodes below are covered, but not the current one
        // Index 1: Case where all the nodes in the subtree are covered including the current one
        // Index 2: Case where all the nodes in the subtree are covered and the current one has a camera

        if (node == nullptr) {
            // If node doesn't exist, it is considered as covered so no need for cameras
            // Index 3 is set to +INF because you can't put a camera on a non existent node
            return {0, 0, INT_MAX};
        }

        vector<size_t> left = f(node->left), right = f(node->right), current(3);

        // For case 0 we need both left and right subtrees to be completely covered
        current[0] = left[1] + right[1];

        // For case 1 we get the minimum of all the permutation that allow covering the current node with minimum cameras

        // left[1] + right[2]:  left subtree covered and right child has camera that covers current node
        // left[2] + right[2]:  right child has camera that covers current node and left subtree is covered
        // left[2] + right[2]:  both children have camera that cover current node

        current[1] = min({
            left[1] + right[2],
            left[2] + right[1],
            left[2] + right[2]
        });

        // For case 2 we add a new camera that can cover both children(subtrees' roots)
        // We use the permutation that uses less cameras
        current[2] = 1 +
            *min_element(left.begin(), left.end()) +
            *min_element(right.begin(), right.end());

        return current;
    }

    int minCameraCover(TreeNode* root) {
        vector<size_t> dp = f(root);
        return min({dp[1], dp[2]});
    }
};