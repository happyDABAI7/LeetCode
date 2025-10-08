方法一：快速排序
每次保证 j 左边及j≤哨兵，j右边≥哨兵；
看j与k的大小比较，决定下一次比较的是右子数组还是左子数组，减少无意义的排序；
寻找第k个最大值，就是找第n-k个最小值；
寻找k不需要完整的排序。


S1_1：递归法
时间复杂度：平均 O (n)[这个时间复杂度只有在 随机数据 下才成立]，最坏 O (n²)；
空间复杂度：平均 O (log n)，最坏 O (n)

class Solution {
    int quickselect(int[] nums, int l, int r, int k) {
        if (l == r) return nums[k];   //双指针
        int x = nums[l], i = l - 1, j = r + 1;
        while (i < j) {
            do i++; while (nums[i] < x);
            do j--; while (nums[j] > x);
            if (i < j){
                int tmp = nums[i];
                nums[i] = nums[j];
                nums[j] = tmp;
            }
        }
        if (k <= j) return quickselect(nums, l, j, k);
        else return quickselect(nums, j + 1, r, k);
    }
    public int findKthLargest(int[] _nums, int k) {
        int n = _nums.length;
        return quickselect(_nums, 0, n - 1, n - k);
    }
}


S1_2：迭代法
时间复杂度：平均 O (n)[这个时间复杂度只有在 随机数据 下才成立]，最坏 O (n²) ->实际运行会比递归法效率高，因为避免了递归调用的额外开销；
空间复杂度：平均 O (1)

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


补充：
为什么不把＝x的都放左边或都放右边？这样的话当nums[i]和nums[j]都＝x时交换不是很浪费吗？
1. 避免分区极端不平衡：如果强制将所有等于x的元素都放在左边（或右边），当数组中存在大量等于x的元素时，会导致分区后左右区间的大小极度不平衡。
eg. 
do i++; while (nums[i] <＝ x);
do j--; while (nums[j] > x);
假设数组全是相同元素（如[5,5,5,5,5]），若将等于x的元素全放左边，分区后右边区间可能依然很大（几乎等于原数组长度）。
此时递归会不断处理大区间，导致时间复杂度从平均O(n)退化为最坏O(n²)。
原方法会让分区后的左右区间大小更均衡，提高效率。
2. 防止死循环
若修改逻辑为 “等于x的元素不交换”，可能导致i或j在某个位置停滞，无法继续移动，最终引发死循环。
eg. 
do i++; while (nums[i] <＝ x);
do j--; while (nums[j] >＝ x);
当nums[i] = x且nums[j] = x时，若不交换且不移动指针，i和j会一直停在原地，导致死循环。
3. 交换 “等于 x 的元素” 的代价很小



方法二：堆排序法
大根堆法，必须先有一次从非叶子节点往上到根节点的排序(buildMaxHeap)，得到第一次完整的大根堆；
接着，每次拿走第0个结点(也就是根节点，最大的数)，将最后一个结点代替被取走的根节点后，就只需要更新结点的方法(maxHeapify)就可以了；
maxHeapify是从根节点往下更新，所以需要整个堆的状态是"基本符合大根堆"的状态(因为该方法只有左右结点有大于根节点时猜更新，才会检查下一层是否还需要更新；若左右结点都小于根节点，就直接结束了，对于下面几层需要更新的结点不会关注)；
第k次形成大根堆->第k次时的nums[0]就是第k大的数。


S2_1：递归法
时间复杂度为 O(n + k log n)=O(nlog n)；
空间复杂度为 O(log n)

class Solution {
    public int findKthLargest(int[] nums, int k) {
        int heapSize = nums.length;
        buildMaxHeap(nums, heapSize);
        for (int i = nums.length - 1; i >= nums.length - k + 1; --i) {
            swap(nums, 0, i);
            --heapSize;
            maxHeapify(nums, 0, heapSize);
        }
        return nums[0];
    }

    public void buildMaxHeap(int[] a, int heapSize) {
        for (int i = heapSize / 2 - 1; i >= 0; --i) {
            maxHeapify(a, i, heapSize);
        } 
    }

    public void maxHeapify(int[] a, int i, int heapSize) {
        int l = i * 2 + 1, r = i * 2 + 2, largest = i;
        if (l < heapSize && a[l] > a[largest]) {
            largest = l;
        } 
        if (r < heapSize && a[r] > a[largest]) {
            largest = r;
        }
        if (largest != i) {
            swap(a, i, largest);
            maxHeapify(a, largest, heapSize);
        }
    }

    public void swap(int[] a, int i, int j) {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}



S2_2：迭代法
时间复杂度为 O(n + k log n)=O(nlog n)；稍快于递归法
空间复杂度为 O(1)

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



方法三：桶排序法
该方法的核心是利用数值范围有限的特点([-10000, 10000]），通过桶数组统计每个数值的出现次数，再从大到小“数”出第k 个元素。时间复杂度为0(n+m)(n是数组长度，m是数值范围大小20001)，效率极高，适合数值范围已知且较小的场景。
时间复杂度为0(n+m)
空间复杂度为O(1)

class Solution {
    public int findKthLargest(int[] nums, int k) {
        int[] buckets = new int[20001];
        for (int i = 0; i < nums.length; i++) {   
            buckets[nums[i] + 10000]++;    //----
        }
        for (int i = 20000; i >= 0; i--) {
            k = k - buckets[i];
            if (k <= 0) {
                return i - 10000;
            }
        }
        return 0;
    }
}

补充：
对于数组中的每个元素nums[i]，通过nums[i] + 10000 计算其对应的桶索引，然后将该桶的计数加1。
例如：若 nums[i] = 5，则索引为 5+ 10000 = 10005, buckets[10005] 加1（表示数值5出现了1次）；若nums[i] = -3，索引为(-3)+10000= 9997，buckets[9997] 加1。



方法四：（不推荐面试时用）调用库函数方法
Java 中 Arrays.sort() 对 基本类型数组（如 int[]） 采用 双轴快速排序（Dual-Pivot QuickSort） 算法。
这种算法的平均时间复杂度为 O(n log n)，且经过优化后（如对有序数组的特殊处理），最坏情况下的时间复杂度也稳定在 O(n log n)（避免了传统快速排序在极端情况下退化到 O(n²) 的问题）。
时间复杂度：O(n log n)（由双轴快速排序的效率决定）；
空间复杂度：O(log n)（主要来自递归调用栈）。


import java.util.Arrays;

class Solution {
    public int findKthLargest(int[] nums, int k) {
        // 1. 对数组进行升序排序
        Arrays.sort(nums);
        // 2. 第k大元素在排序后数组中的索引为：nums.length - k
        return nums[nums.length - k];
    }
}



