给你二叉树的根结点 root ，请你将它展开为一个单链表：

展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。

展开后的单链表应该与二叉树 先序遍历 顺序相同。



注意：题目意思是将二叉树改成右斜树，所以节点类型还是TreeNode；

        且右斜树顺序和二叉树先序遍历顺序相同。



方法一：前序遍历

先前序遍历二叉树，将节点存入可变数组List<TreeNode> list = new ArrayList<TreeNode>();

            再依次放入右斜树中，实现“单链表”。

Tn=O(n)

Sn=O(n)



//递归法



/\*\*

\* Definition for a binary tree node.

\* public class TreeNode {

\*     int val;

\*     TreeNode left;

\*     TreeNode right;

\*     TreeNode() {}

\*     TreeNode(int val) { this.val = val; }

\*     TreeNode(int val, TreeNode left, TreeNode right) {

\*         this.val = val;

\*         this.left = left;

\*         this.right = right;

\*     }

\* }

\*/

class Solution {

   public void flatten(TreeNode root) {

       List<TreeNode> list=new ArrayList<>();  //前序遍历存储

       bianli(root,list); 

       for(int i=1;i<list.size();i++){  //构造右斜树

           TreeNode prev =list.get(i-1),curr=list.get(i);

           prev.left=null;

           prev.right=curr;

       }

       

   }



   public void bianli(TreeNode root,List<TreeNode> list){

       if(root!=null){   //鲁棒性

           list.add(root);     //根

           bianli(root.left,list);    //左

           bianli(root.right,list);   //右

       }

   }

}






//迭代法


class Solution {

   public void flatten(TreeNode root) {

       List<TreeNode> list = new ArrayList<TreeNode>();

       Deque<TreeNode> stack = new LinkedList<TreeNode>();

       TreeNode node = root;

       while (node != null || !stack.isEmpty()) {

           while (node != null) {

               list.add(node);

               stack.push(node);

               node = node.left;

           }

           node = stack.pop();

           node = node.right;

       }

       int size = list.size();

       for (int i = 1; i < size; i++) {

           TreeNode prev = list.get(i - 1), curr = list.get(i);

           prev.left = null;

           prev.right = curr;

       }

   }

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

   public void flatten(TreeNode root) {

       if (root == null) {

           return;

       }

       Deque<TreeNode> stack = new LinkedList<TreeNode>();

       stack.push(root);

       TreeNode prev = null;

       while (!stack.isEmpty()) {

           TreeNode curr = stack.pop();

           if (prev != null) {  	 //展开为单链表

               prev.left = null;

               prev.right = curr;  

           }

           TreeNode left = curr.left, right = curr.right;    //先序遍历

           if (right != null) {

               stack.push(right);

           }

           if (left != null) {

               stack.push(left);

           }

           prev = curr; 

       }

   }

}







方法三：寻找前驱节点

找前驱节点，将自己及其后的结点接到前驱节点的右节点上，并与根节点断连，前驱节点连到根节点右边。

具体做法：对于当前节点，如果其左子节点不为空，则在其左子树中找到最右边的节点，作为前驱节点，将当前节点的右子节点赋给前驱节点的右子节点，然后将当前节点的左子节点赋给当前节点的右子节点，并将当前节点的左子节点设为空。对当前节点处理结束后，继续处理链表中的下一个节点，直到所有节点都处理结束。

Tn=O(n)

Sn=O(1)





class Solution {

   public void flatten(TreeNode root) {

       TreeNode curr = root;

       while (curr != null) {

           if (curr.left != null) {

               TreeNode next = curr.left;

               TreeNode predecessor = next;

               while (predecessor.right != null) {

                   predecessor = predecessor.right;

               }

               predecessor.right = curr.right;

               curr.left = null;

               curr.right = next;

           }

           curr = curr.right;

       }

   }

}


//小变体
public void flatten(TreeNode root) {
    while (root != null) { 
        //左子树为 null，直接考虑下一个节点
        if (root.left == null) {   //不同点1：利用if语句稍微减少部分无意义操作
            root = root.right;
        } else {
            // 找左子树最右边的节点
            TreeNode pre = root.left;
            while (pre.right != null) {
                pre = pre.right;
            } 
            //将原来的右子树接到左子树的最右边节点
            pre.right = root.right;
            // 将左子树插入到右子树的地方
            root.right = root.left;
            root.left = null;
            // 考虑下一个节点
            root = root.right;  //
        }
    }
}



方法四：基于后序遍历的递归方法，原地展开二叉树为单链表
左右根的顺序自下而上将二叉树改成顺序正确的单链表（相较于前三种方法，关键在于“原地操作”，前三种方法都使用了新链表来接收数据）

时间复杂度：O(n)（线性时间，与节点总数成正比）；
空间复杂度：O(logn)（取决于树的高度，最坏为O(n)）。


class Solution {
    public void flatten(TreeNode root) {
        if(root == null){
            return ;
        }
        //将根节点的左子树变成链表
        flatten(root.left);
        //将根节点的右子树变成链表
        flatten(root.right);
        TreeNode temp = root.right;
        //把树的右边换成左边的链表
        root.right = root.left;
        //记得要将左边置空
        root.left = null;
        //找到树的最右边的节点
        while(root.right != null) root = root.right;
        //把右边的链表接到刚才树的最右边的节点
        root.right = temp;
    }
}



方法五：右子树 - 左子树 - 根的顺序 DFS 二叉树，并利用头插法构造单链表
也是一种自下而上的逐渐修正方法
时间复杂度：O(n)，其中 n 是二叉树的节点个数。
空间复杂度：O(n)。递归需要 O(n) 的栈空间，平均情况下O(logn)。

class Solution {
    private TreeNode head;  //head初始为NULL，类似c++的单链表指针

    public void flatten(TreeNode root) {
        if (root == null) {
            return;
        }
        flatten(root.right);
        flatten(root.left);
        root.left = null;
        root.right = head; // 头插法，相当于链表的 root.next = head
        head = root; // 现在链表头节点是 root
    }
}





方法六：分治法
不使用head指针，只在DFS中构造单链表
和方法四原理相同，但实现方法稍不一样，方法四更直观，更易理解，但较为繁复，有大量重复寻找“最右边结点”的步骤；
方法六则无该重复内容，但return语句的语法逻辑复杂，不易想到
时间复杂度：O(n)，其中 n 是二叉树的节点个数。
空间复杂度：O(n)。递归需要 O(n) 的栈空间，平均O(logn)。


class Solution {
    public void flatten(TreeNode root) {
        dfs(root);
    }

    private TreeNode dfs(TreeNode root) {
        if (root == null) {
            return null;
        }
        TreeNode leftTail = dfs(root.left);
        TreeNode rightTail = dfs(root.right);
        if (leftTail != null) {
            leftTail.right = root.right; // 左子树链表 -> 右子树链表
            root.right = root.left; // 当前节点 -> 左右子树合并后的链表
            root.left = null;
        }
        return rightTail != null ? rightTail : leftTail != null ? leftTail : root;
    }
}




方法七：显示利用栈进行类似递归的方法
和方法二一模一样，但方法二利用队列和可变数组模拟栈的使用，这里直接使用栈
更推荐方法二，因为Stack 存在设计缺陷，而 Deque 是更规范、更高效的栈实现方式


public void flatten(TreeNode root) { 
    if (root == null){
        return;
    }
    Stack<TreeNode> s = new Stack<TreeNode>();
    s.push(root);
    TreeNode pre = null;
    while (!s.isEmpty()) {
        TreeNode temp = s.pop(); 
        /***********修改的地方*************/
        if(pre!=null){
            pre.right = temp;
            pre.left = null;
        }
        /********************************/
        if (temp.right != null){
            s.push(temp.right);
        }
        if (temp.left != null){
            s.push(temp.left);
        } 
        /***********修改的地方*************/
        pre = temp;
        /********************************/
    }
}




