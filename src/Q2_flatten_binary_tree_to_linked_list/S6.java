class Solution {
    public void flatten(TreeNode root) {
        dfs(root);
    }

    private TreeNode dfs(TreeNode root) {
        if (root == null) {
            return null;
        }
        TreeNode leftTail = dfs(root.left);
        TreeNode rightTail = dfs(root.right);
        if (leftTail != null) {
            leftTail.right = root.right; // 左子树链表 -> 右子树链表
            root.right = root.left; // 当前节点 -> 左右子树合并后的链表
            root.left = null;
        }
        return rightTail != null ? rightTail : leftTail != null ? leftTail : root;
    }
}