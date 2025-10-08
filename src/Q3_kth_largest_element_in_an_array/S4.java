import java.util.Arrays;

class Solution {
    public int findKthLargest(int[] nums, int k) {
        // 1. 对数组进行升序排序
        Arrays.sort(nums);
        // 2. 第k大元素在排序后数组中的索引为：nums.length - k
        return nums[nums.length - k];
    }
}