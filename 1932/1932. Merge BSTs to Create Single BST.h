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

#include <unordered_map>

class Solution {
public:
    int getMax(TreeNode* root) {
        while (root->right) root = root->right;
        return root->val;
    }

    int getMin(TreeNode* root) {
        while (root->left) root = root->left;
        return root->val;
    }

    bool merge(TreeNode* son, TreeNode* father) {
        if (son->val < father->val) {
            if (getMax(son) < father->val) {
                delete father->left;
                father->left = son;
                return true;
            }
            return false;
        } else {
            if (getMin(son) > father->val) {
                delete father->right;
                father->right = son;
                return true;
            }
            return false;
        }
    }

    bool isValid(TreeNode* root, int min, int max) {
        if (!root) return true;
        if (root->val <= min || root->val >= max) return false;
        return isValid(root->left, min, root->val) && isValid(root->right, root->val, max);
    }

    TreeNode* canMerge(vector<TreeNode*>& trees) {
        std::unordered_map<int, TreeNode*> m;
        for (const auto& tree: trees) {
            if (tree->left) {
                m[tree->left->val] = tree;
            }
            if (tree->right) {
                m[tree->right->val] = tree;
            }
        }
        for (auto& tree: trees) {
            if (m.contains(tree->val)) {
                if (merge(tree, m[tree->val])) {
                    tree = nullptr;
                } else {
                    return nullptr;
                }
            }
        }
        TreeNode* result;
        int i = 0;
        for (const auto& tree: trees) {
            if (tree != nullptr) {
                result = tree;
                ++i;
            }
        }
        if (i == 1) {
            if (isValid(result, INT_MIN, INT_MAX)) {
                return result;
            }
        }
        return nullptr;
    }
};