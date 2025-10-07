给你二叉树的根结点 root ，请你将它展开为一个单链表：

展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。

展开后的单链表应该与二叉树 先序遍历 顺序相同。



注意：题目意思是将二叉树改成右斜树，所以节点类型还是TreeNode；

&nbsp;        且右斜树顺序和二叉树先序遍历顺序相同。



方法一：前序遍历

先前序遍历二叉树，将节点存入可变数组List<TreeNode> list = new ArrayList<TreeNode>();

&nbsp;            再依次放入右斜树中，实现“单链表”。

Tn=O(n)

Sn=O(n)



//递归法



/\*\*

&nbsp;\* Definition for a binary tree node.

&nbsp;\* public class TreeNode {

&nbsp;\*     int val;

&nbsp;\*     TreeNode left;

&nbsp;\*     TreeNode right;

&nbsp;\*     TreeNode() {}

&nbsp;\*     TreeNode(int val) { this.val = val; }

&nbsp;\*     TreeNode(int val, TreeNode left, TreeNode right) {

&nbsp;\*         this.val = val;

&nbsp;\*         this.left = left;

&nbsp;\*         this.right = right;

&nbsp;\*     }

&nbsp;\* }

&nbsp;\*/

class Solution {

&nbsp;   public void flatten(TreeNode root) {

&nbsp;       List<TreeNode> list=new ArrayList<>();  //前序遍历存储

&nbsp;       bianli(root,list); 

&nbsp;       for(int i=1;i<list.size();i++){  //构造右斜树

&nbsp;           TreeNode prev =list.get(i-1),curr=list.get(i);

&nbsp;           prev.left=null;

&nbsp;           prev.right=curr;

&nbsp;       }

&nbsp;       

&nbsp;   }



&nbsp;   public void bianli(TreeNode root,List<TreeNode> list){

&nbsp;       if(root!=null){   //鲁棒性

&nbsp;           list.add(root);     //根

&nbsp;           bianli(root.left,list);    //左

&nbsp;           bianli(root.right,list);   //右

&nbsp;       }

&nbsp;   }

}













//迭代法

class Solution {

&nbsp;   public void flatten(TreeNode root) {

&nbsp;       List<TreeNode> list = new ArrayList<TreeNode>();

&nbsp;       Deque<TreeNode> stack = new LinkedList<TreeNode>();

&nbsp;       TreeNode node = root;

&nbsp;       while (node != null || !stack.isEmpty()) {

&nbsp;           while (node != null) {

&nbsp;               list.add(node);

&nbsp;               stack.push(node);

&nbsp;               node = node.left;

&nbsp;           }

&nbsp;           node = stack.pop();

&nbsp;           node = node.right;

&nbsp;       }

&nbsp;       int size = list.size();

&nbsp;       for (int i = 1; i < size; i++) {

&nbsp;           TreeNode prev = list.get(i - 1), curr = list.get(i);

&nbsp;           prev.left = null;

&nbsp;           prev.right = curr;

&nbsp;       }

&nbsp;   }

}



补充知识：

1.Deque是 Java 集合框架中的一个接口（全称为Double Ended Queue，双端队列），继承自Queue接口，允许在队列的两端（头部和尾部）进行元素的插入、删除和访问操作。

Deque的核心能力是 “双端操作”，既可以作为队列（FIFO，先进先出）使用，也可以作为栈（LIFO，后进先出）使用，比传统的Queue和Stack（Java 遗留类）更灵活。

方法：入栈	push(e)，出栈pop()，查看栈顶peek()

2.LinkedList 是 List 接口的实现类，同时它也是 Deque 接口的实现类 —— 这是 Java 中 “类可以实现多个接口” 的特性，让 LinkedList 同时具备了 List 的有序集合能力 和 Deque 的双端操作能力。









方法二：前序遍历和展开同步进行

首先前序遍历：每次从栈内弹出一个节点作为当前访问的节点，获得该节点的子节点，如果子节点不为空，则依次将右子节点和左子节点压入栈内（注意入栈顺序-->因为栈先进后出）。

同时展开为单链表：维护上一个访问的节点 prev，每次访问一个节点时，令当前访问的节点为 curr，将 prev 的左子节点设为 null 以及将 prev 的右子节点设为 curr，然后将 curr 赋值给 prev，进入下一个节点的访问，直到遍历结束。

Tn=O(n)

Sn=O(n)





class Solution {

&nbsp;   public void flatten(TreeNode root) {

&nbsp;       if (root == null) {

&nbsp;           return;

&nbsp;       }

&nbsp;       Deque<TreeNode> stack = new LinkedList<TreeNode>();

&nbsp;       stack.push(root);

&nbsp;       TreeNode prev = null;

&nbsp;       while (!stack.isEmpty()) {

&nbsp;           TreeNode curr = stack.pop();

&nbsp;           if (prev != null) {  	 //展开为单链表

&nbsp;               prev.left = null;

&nbsp;               prev.right = curr;  

&nbsp;           }

&nbsp;           TreeNode left = curr.left, right = curr.right;    //先序遍历

&nbsp;           if (right != null) {

&nbsp;               stack.push(right);

&nbsp;           }

&nbsp;           if (left != null) {

&nbsp;               stack.push(left);

&nbsp;           }

&nbsp;           prev = curr; 

&nbsp;       }

&nbsp;   }

}







方法三：寻找前驱节点

找前驱节点，将自己及其后的结点接到前驱节点的右节点上，并与根节点断连，前驱节点连到根节点右边。

具体做法：对于当前节点，如果其左子节点不为空，则在其左子树中找到最右边的节点，作为前驱节点，将当前节点的右子节点赋给前驱节点的右子节点，然后将当前节点的左子节点赋给当前节点的右子节点，并将当前节点的左子节点设为空。对当前节点处理结束后，继续处理链表中的下一个节点，直到所有节点都处理结束。

Tn=O(n)

Sn=O(1)





class Solution {

&nbsp;   public void flatten(TreeNode root) {

&nbsp;       TreeNode curr = root;

&nbsp;       while (curr != null) {

&nbsp;           if (curr.left != null) {

&nbsp;               TreeNode next = curr.left;

&nbsp;               TreeNode predecessor = next;

&nbsp;               while (predecessor.right != null) {

&nbsp;                   predecessor = predecessor.right;

&nbsp;               }

&nbsp;               predecessor.right = curr.right;

&nbsp;               curr.left = null;

&nbsp;               curr.right = next;

&nbsp;           }

&nbsp;           curr = curr.right;

&nbsp;       }

&nbsp;   }

}













