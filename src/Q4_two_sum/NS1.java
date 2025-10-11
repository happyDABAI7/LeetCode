class Solution {

    // 假设 nums 是升序排列的有序数组

    public int[] twoSum(int[] nums, int target) {

        int left = 0;                  // 左指针：起点

        int right = nums.length - 1;   // 右指针：终点

        

        while (left < right) {         // 避免指针交叉（同一元素不能重复使用）

            int sum = nums[left] + nums[right];

            if (sum == target) {

                // 找到目标，返回索引（注意：题目可能要求原数组索引，此处假设返回当前有序数组的索引）

                return new int[]{left, right};

            } else if (sum > target) {

                // 和太大，右指针左移（减小总和）

                right--;

            } else {

                // 和太小，左指针右移（增大总和）

                left++;

            }

        }

        // 题目保证有解，此处仅为满足语法

        return new int[]{-1, -1};

    }

}