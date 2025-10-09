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



方法三：桶排序法（其中的特殊方法--计数排序）
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




方法五：三路划分
每轮将数组划分为三个部分：小于、等于和大于基准数的所有元素。这样当发现第 k 大数字处在“等于基准数”的子数组中时，便可以直接返回该元素；否则和快速排序一样，进入子数组重复，减少不必要操作。
关键改进点：使用随机数来选择基准点，使得基准点尽量靠近数组中间，提高效率。后面很多方法都是使用的随机数来取基准点。

平均时间复杂度：O (n)
最坏时间复杂度：O (n²)
空间复杂度：O (log n)


public class Solution {
    private int quickSelect(List<Integer> nums, int k) {
        // 随机选择基准数
        Random rand = new Random();
        int pivot = nums.get(rand.nextInt(nums.size()));
        // 将大于、小于、等于 pivot 的元素划分至 big, small, equal 中
        List<Integer> big = new ArrayList<>();
        List<Integer> equal = new ArrayList<>();
        List<Integer> small = new ArrayList<>();
        for (int num : nums) {
            if (num > pivot)
                big.add(num);
            else if (num < pivot)
                small.add(num);
            else
                equal.add(num);
        }
        // 第 k 大元素在 big 中，递归划分
        if (k <= big.size())
            return quickSelect(big, k);
        // 第 k 大元素在 small 中，递归划分
        if (nums.size() - small.size() < k)
            return quickSelect(small, k - nums.size() + small.size());
        // 第 k 大元素在 equal 中，直接返回 pivot
        return pivot;
    }
    
    public int findKthLargest(int[] nums, int k) {
        List<Integer> numList = new ArrayList<>();
        for (int num : nums) {
            numList.add(num);
        }
        return quickSelect(numList, k);
    }
}




方法六：和方法五相同，实现方式不同

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




方法七：优先队列（本质是构造k个元素的小根堆）
PriorityQueue优先队列，会自动将队列中的元素按规则排序(例如这里，是自动将元素按小根堆排序)。
时间复杂度：O(nlogk)，每个元素最多进行一次堆操作；
空间复杂度：O(k)，「优先队列」的大小。

import java.util.Comparator;
import java.util.PriorityQueue;
class Solution {
    public int findKthLargest(int[] nums, int k) {
        PriorityQueue<Integer> q = new PriorityQueue<>((a,b)->a-b);
        for (int x : nums) {
            if (q.size() < k || q.peek() < x) q.add(x);
            if (q.size() > k) q.poll();
        }
        return q.peek();
    }
}
//其中的(a,b)->a-b是一个比较器（Comparator），用于定义元素的 “优先级规则”（即排序规则），这里是元素 从小到大 的顺序(当a < b时，a - b返回负数，此时认为a的优先级比b高)。
//同样作用：PriorityQueue<Integer> minHeap = new PriorityQueue<>(k, Comparator.comparingInt(a -> a));


方法八：对方法七优先队列进行优化-->当k是前2/n大的元素，使用小根堆，否则，使用大根堆
优化后空间复杂度降至 O(min(k, n - k))

public int findKthLargest(int[] nums, int k) {
    int n = nums.length;
    // 当k较大时，转为找第(n - k + 1)小元素，用大顶堆
    if (k > n - k) {
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        int m = n - k + 1; // 需要维护的元素数量
        for (int num : nums) {
            maxHeap.add(num);
            if (maxHeap.size() > m) {
                maxHeap.poll(); // 移除最大元素，保留前m小的元素
            }
        }
        return maxHeap.peek();
    } else {
        // 原逻辑：小顶堆维护前k大的元素
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        for (int num : nums) {
            minHeap.add(num);
            if (minHeap.size() > k) {
                minHeap.poll();
            }
        }
        return minHeap.peek();
    }
}


方法九：方法一稍微不同的解法

import java.util.Random;

public class Solution {

    private final static Random RANDOM = new Random(System.currentTimeMillis());

    public int findKthLargest(int[] nums, int k) {
        int n = nums.length;
        int left = 0;
        int right = n - 1;
        int target = n - k;
        while (true) {
            int j = partition(nums, left, right);
            if (j == target) {
                return nums[j];
            } else if (j < target) {
                left = j + 1;
            } else {
                right = j - 1;
            }
        }
    }

    private int partition(int[] nums, int left, int right) {
        int randomIndex = left + RANDOM.nextInt(right - left + 1);
        swap(nums, left, randomIndex);
        // nums[left + 1..le) <= pivot，nums(ge..right] >= pivot;
        int pivot = nums[left];
        int le = left + 1;
        int ge = right;
        while (true) {
            while (le <= ge && nums[le] < pivot) {
                le++;
            }
            while (le <= ge && nums[ge] > pivot) {
                ge--;
            }
            if (le >= ge) {
                break;
            }
            swap(nums, le, ge);
            le++;
            ge--;
        }
        swap(nums, left, ge);
        return ge;
    }

    private void swap(int[] nums, int index1, int index2) {
        int temp = nums[index1];
        nums[index1] = nums[index2];
        nums[index2] = temp;
    }

}




方法十：值域映射 + 树状数组 + 二分
时间复杂度：将所有数字放入树状数组复杂度为 O(nlogm)；二分出答案复杂度为 O(logm)，其中 m=(2×10)4为值域大小。整体复杂度为 O(nlogm)
空间复杂度：O(m)


class Solution {
    int M = 10010, N = 2 * M;
    int[] tr = new int[N];
    int lowbit(int x) {
        return x & -x;
    }
    int query(int x) {
        int ans = 0;
        for (int i = x; i > 0; i -= lowbit(i)) ans += tr[i];
        return ans;
    }
    void add(int x) {
        for (int i = x; i < N; i += lowbit(i)) tr[i]++;
    }
    public int findKthLargest(int[] nums, int k) {
        for (int x : nums) add(x + M);
        int l = 0, r = N - 1;
        while (l < r) {
            int mid = l + r + 1 >> 1;
            if (query(N - 1) - query(mid - 1) >= k) l = mid;
            else r = mid - 1;
        }
        return r - M;
    }
}


