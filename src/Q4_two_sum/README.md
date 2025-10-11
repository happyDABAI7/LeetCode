方法一：暴力解法
时间复杂度：O（n2），其中n为 nums的长度。
空间复杂度：O(1）。


class Solution {
    public int[] twoSum(int[] nums, int target) {
        for (int i = 0; ; i++) { // 枚举 i
            for (int j = i + 1; j < nums.length; j++) { // 枚举 i 右边的 j
                if (nums[i] + nums[j] == target) { // 满足要求
                    return new int[]{i, j}; // 返回两个数的下标
                }
            }
        }
        // 题目保证有解，循环中一定会 return
        // 所以这里无需 return，毕竟代码不会执行到这里
    }
}


还是下面的代码更严谨。

class Solution {
    public int[] twoSum(int[] nums, int target) {
        for(int i=0; i<nums.length; i++){
            for(int j=i+1; j<nums.length; j++){
                if(nums[i]+nums[j]==target){
                    return new int[]{i, j}; 
                }
            }
        }
        return new int[0];
    }
}

补充：
1.两者相同，但上面的代码可以只有if语句里面有return？

因为上面的代码的外层循环是 for (int i = 0; ; i++)，这是一个无限循环（没有终止条件，i会一直递增，永远不会退出循环）。编译器会认为：

这个循环永远不会结束，因此循环内部的return语句一定会被执行（只要程序能运行到符合条件的情况）。

由于循环不会退出，方法永远不会执行到循环外面的代码，因此不需要在循环外添加 return 语句，也不会违反 “所有路径必须返回值” 的规则。

但要注意，这是在“// 题目保证有解，循环中一定会 return，所以这里无需 return，毕竟代码不会执行到这里”的条件下才成立。







方法二：哈希表法

class Solution {

    public int[] twoSum(int[] nums, int target) {

        Map<Integer, Integer> idx = new HashMap<>(); // 创建一个空哈希表

        for (int j = 0;j<nums.length ; j++) { // 枚举 j

            int x = nums[j];

            // 在左边找 nums[i]，满足 nums[i]+x=target

            if (idx.containsKey(target - x)) { // 找到了

                return new int[]{idx.get(target - x), j}; // 返回两个数的下标

            }

            idx.put(x, j); // 保存 nums[j] 和 j

        }

     return new int[0]; 

    }

}


补充：idx.containsKey(target - x)判断哈希表内是否有对应元素

上面的代码中idx.containsKey(target - x)时间复杂度是什么，为什么程序最终时间复杂度只有O(n)? 

答：哈希表的核心特性是通过哈希函数将key映射到一个固定的位置（桶），因此查询时无需遍历整个表，而是直接定位到目标桶。所以该操作平均时间复杂度为O(1)，最坏情况O(n)。

时间复杂度：0（m），其中n为 nums 的长度。

空间复杂度：0（n）。哈希表需要O（n）的空间。



相比暴力做法，哈希表多消耗了内存空间，但减少了运行时间，这就是「空间换时间」。




补充：若数组有序，可以使用双指针法。

时间复杂度：O (n)，空间复杂度：O (1)

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



补充：return new int[]{-1, -1}; 是更合理的选择（符合约定、语义清晰、兼容调用方处理逻辑）。

为什么想到哈希表？

本质是 “针对性解决痛点”：

暴力解法的瓶颈是 “找 target - x” 要 O (n)，而哈希表的 O (1) 查找能直接突破这个瓶颈；

哈希表能同时存储 “元素值” 和 “原始索引”，完美匹配题目 “返回索引” 的需求；

无需依赖数组有序，适用场景更灵活，且实现简单（只需一次遍历 + 哈希表操作）。

简单说：当问题需要 “快速根据一个值找另一个关联值”（这里是 “根据 target - x 找索引”）时，哈希表往往是优先考虑的工具。