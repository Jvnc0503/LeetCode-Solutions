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
class Solution {
public:
    enum Coverage {NOT_COVERED, CAMERA, COVERED};
    int cameras = 0;

    Coverage dfs(TreeNode* root) {
        if (root == nullptr) {
            // If current node doesn't exist, we consider it as covered
            return COVERED;
        }
        // Get the coverage of children
        Coverage left = dfs(root->left);
        Coverage right = dfs(root->right);

        if (left == NOT_COVERED || right == NOT_COVERED) {
            // If any of the children is not covered, we create a new camera on the current node
            ++cameras;
            return CAMERA;
        }
        if (left == CAMERA || right == CAMERA){
            // If any of the children has a camera, then the current node is already covered
            return COVERED;
        }
        // Node is no covered by any camera
        return NOT_COVERED;
    }

    int minCameraCover(TreeNode* root) {
        // If root has not been corvered we add a final camera
        if (dfs(root) == NOT_COVERED) {
            ++cameras;
        }
        return cameras;
    }
};