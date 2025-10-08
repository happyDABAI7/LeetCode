class Solution {
    // 入口方法：寻找第k大元素
    public int findKthLargest(int[] nums, int k) {
        int heapSize = nums.length;
        // 1. 构建大顶堆（迭代版maxHeapify支撑）
        buildMaxHeap(nums, heapSize);
        // 2. 提取k-1次最大值，剩余堆顶即为第k大元素
        for (int i = nums.length - 1; i >= nums.length - k + 1; --i) {
            swap(nums, 0, i);   // 堆顶（最大值）移到数组末尾
            --heapSize;         // 缩小堆范围，排除已提取的最大值
            maxHeapify(nums, 0, heapSize); // 迭代调整堆，维护大顶堆性质
        }
        return nums[0]; // 剩余堆顶是第k大元素
    }

    // 构建大顶堆：从最后一个非叶子节点向前调整
    public void buildMaxHeap(int[] a, int heapSize) {
        // 最后一个非叶子节点索引：heapSize/2 - 1
        for (int i = heapSize / 2 - 1; i >= 0; --i) {
            maxHeapify(a, i, heapSize); // 调用迭代版maxHeapify
        }
    }

    // 迭代版maxHeapify：维护以i为根的子树的大顶堆性质
    public void maxHeapify(int[] a, int i, int heapSize) {
        while (true) {
            int l = i * 2 + 1; // 左子节点索引
            int r = i * 2 + 2; // 右子节点索引
            int largest = i;   // 初始化最大值索引为当前节点

            // 1. 比较左子节点，更新最大值索引
            if (l < heapSize && a[l] > a[largest]) {
                largest = l;
            }
            // 2. 比较右子节点，更新最大值索引
            if (r < heapSize && a[r] > a[largest]) {
                largest = r;
            }

            // 3. 若当前节点已是最大值，无需继续调整，退出循环
            if (largest == i) {
                break;
            }

            // 4. 交换当前节点与最大值节点，让最大值上浮到当前位置
            swap(a, i, largest);
            // 5. 更新当前节点索引为交换后的位置，继续向下调整子树
            i = largest;
        }
    }

    // 辅助方法：交换数组中两个位置的元素
    public void swap(int[] a, int i, int j) {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}