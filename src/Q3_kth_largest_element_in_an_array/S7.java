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
