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