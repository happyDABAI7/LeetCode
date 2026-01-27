#include <iostream>
#include <algorithm>
using namespace std;

const int N=2010;
int a[N];

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n,m,k;
  cin>>n>>m>>k;
  for(int i=1;i<=n;i++) cin>>a[i];

  long long cnt=0;
  for(int i=1,j=0,sum=0;i<=n;i++){
    while(i>j||(j+1<=n&&sum<k)) if(a[++j]>=m) sum++;
    if(sum>=k) cnt+=n-j+1;
    if(a[i]>=m) sum--;
  }

  cout<<cnt<<'\n';

  return 0;
}


//双指针思想：使用两个指针维护一个滑动窗口，动态调整窗口大小以满足特定条件，从而高效地计算符合条件的子数组数量。
//时间复杂度：O(n)，每个元素最多被访问两次（一次由左指针，一次由右指针）。
//空间复杂度：O(1)，只使用了常数级别的额外空间。
//关键点在于如何移动左右指针以确保窗口内满足至少有k个元素大于等于m，同时计算以左指针为起点的所有符合条件的子数组数量。
//注意事项：确保在移动右指针时正确更新计数器sum，以及在移动左指针时相应地减少sum的值，以保持窗口的正确状态.