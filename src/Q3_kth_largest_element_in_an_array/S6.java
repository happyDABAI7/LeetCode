class Solution {
public:
    /**
     * 找到数组中第 k 大的元素
     * 
     * 算法：三路快速选择 (3-Way QuickSelect)
     * 时间复杂度：平均 O(n)，最坏 O(n²)
     * 空间复杂度：O(log n) 递归栈
     * 
     * 核心思想：
     * 1. 使用三路划分将数组分为：< pivot, == pivot, > pivot 三部分
     * 2. 根据 k 的位置决定在哪个区间继续查找
     * 3. 相比二路划分，三路划分对重复元素更高效
     */
    int findKthLargest(vector<int>& nums, int k) {
        // 转换问题：第 k 大 = 第 (n-k) 小（从0开始索引）
        // 例如：数组长度6，找第2大 -> 找索引为4的元素（第5小）
        k = nums.size() - k;

        /**
         * 三路快速选择递归函数
         * @param l 左边界（包含）
         * @param r 右边界（包含）
         * @return 第 k 小的元素值
         */
        function<int(int, int)> quickSelect = [&](int l, int r) -> int {
            // ==================== 步骤1: 选择并放置 pivot ====================
            
            // 随机选择一个索引作为 pivot（避免最坏情况）
            int rndIndex = l + rand() % (r - l + 1);
            
            // 将随机选中的元素交换到最左边
            swap(nums[rndIndex], nums[l]);
            int pivot = nums[l];  // pivot 现在在 nums[l]
            
            // ==================== 步骤2: 三路划分初始化 ====================
            
            // 三路划分的三个指针：
            // lt (less than): [l, lt) 表示小于 pivot 的区域
            // gt (greater than): (gt, r] 表示大于 pivot 的区域  
            // i: 当前处理位置，[lt, i) 表示等于 pivot 的区域
            int lt = l;   // 小于区域的右边界（不包含）
            int gt = r;   // 大于区域的左边界（不包含）
            int i = l;    // 当前扫描位置
            
            // ==================== 步骤3: 三路划分过程 ====================
            
            // 循环不变式：
            // [l, lt)     : 所有元素 < pivot
            // [lt, i)     : 所有元素 == pivot
            // [i, gt]     : 未处理的元素
            // (gt, r]     : 所有元素 > pivot
            
            while (i <= gt) {
                if (nums[i] < pivot) {
                    // 情况1: 当前元素小于 pivot
                    // 将其交换到小于区域，两个指针都前进
                    swap(nums[lt++], nums[i++]);
                    // lt++ : 扩展小于区域
                    // i++  : 因为从 lt 换过来的元素一定 == pivot（已处理过）
                    
                } else if (nums[i] > pivot) {
                    // 情况2: 当前元素大于 pivot
                    // 将其交换到大于区域，i 不动（因为换过来的元素未处理）
                    swap(nums[i], nums[gt--]);
                    // gt-- : 扩展大于区域
                    // i 不变: 需要重新检查换过来的 nums[i]
                    
                } else {
                    // 情况3: 当前元素等于 pivot
                    // 保持在等于区域，i 前进
                    i++;
                }
            }
            
            // ==================== 步骤4: 划分完成，决定递归方向 ====================
            
            // 循环结束后的状态：
            // [l, lt)   : 所有元素 < pivot
            // [lt, gt]  : 所有元素 == pivot  
            // (gt, r]   : 所有元素 > pivot
            
            if (k < lt) {
                // k 在小于区域，继续在左半部分查找
                return quickSelect(l, lt - 1);
                
            } else if (k > gt) {
                // k 在大于区域，继续在右半部分查找
                return quickSelect(gt + 1, r);
                
            } else {
                // lt <= k <= gt，k 在等于区域
                // 找到答案！所有等于 pivot 的元素都是答案
                return pivot;
            }
        };

        return quickSelect(0, nums.size() - 1);
    }
};
