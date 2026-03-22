/*Problem: BST Search

Implement the solution for this problem.

Input:
- Input specifications

Output:
- Output specifications*/

struct TreeNode* searchBST(struct TreeNode* root, int val) {
    if (!root || root->val == val)
        return root;

    if (val < root->val)
        return searchBST(root->left, val);
    else
        return searchBST(root->right, val);
}