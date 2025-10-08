class Solution {
    // 迭代版快速选择
    int quickselect(int[] nums, int targetK) {
        int l = 0, r = nums.length - 1;
        while (l < r) { // 循环代替递归，直到区间缩小为单个元素
            int x = nums[l];
            int i = l - 1, j = r + 1;
            // 划分过程与原代码完全一致
            while (i < j) {
                do i++; while (nums[i] < x);
                do j--; while (nums[j] > x);
                if (i < j) {
                    int tmp = nums[i];
                    nums[i] = nums[j];
                    nums[j] = tmp;
                }
            }
            // 根据目标位置更新区间 [l, r]
            if (targetK <= j) {
                r = j; // 目标在左区间，缩小右边界
            } else {
                l = j + 1; // 目标在右区间，缩小左边界
            }
        }
        return nums[l]; // l == r 时，即为目标元素
    }

    public int findKthLargest(int[] nums, int k) {
        int n = nums.length;
        int targetK = n - k; // 第k大元素在升序中的索引
        return quickselect(nums, targetK);
    }
}