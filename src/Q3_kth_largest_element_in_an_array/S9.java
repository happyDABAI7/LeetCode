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