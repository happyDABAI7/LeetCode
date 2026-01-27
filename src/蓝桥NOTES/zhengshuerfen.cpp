#include <iostream>
using namespace std;
int main()
{
  int data[200];
  for(int i=0;i<200;i++) data[i]=4*i+6;

  int x; cin>>x;
  int mid,l=0,r=199;
  while(l+1!=r){
    mid = (l+r)/2;
    if(data[mid]>=x) r=mid;
    else l=mid; 
  }
  cout<<r<<'\n';

  return 0;
}

//int l = 0, r = 200;这样取值适应循环条件 (l < r)


//法二---lower_bound
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
  int data[200];
  for(int i=0;i<200;i++) data[i]=4*i+6;

  int x; cin>>x;

  // auto ans = lower_bound(data.begin(),data.end(),x);  //这个写法不对， '.begin(), .end()'是vector才有的，静态数组为下面的用法
  // 1. 调用lower_bound，用数组地址范围（兼容性更好）
  auto ans = lower_bound(data, data + 200, x);
  
  // 2. 安全判断：检查是否越界（没有找到≥x的元素）
  /*if (ans == data + 200) {
      cout << "没有找到大于等于" << x << "的元素" << endl;
  } else {
      // 3. 计算下标（指针减法）
      int idx = ans - data;
      // 4. 输出结果：下标 + 对应值
      cout << "找到的元素下标：" << idx << endl;
      cout << "找到的元素值：" << *ans << endl;
  }*/

  int idx = ans - data;
  cout << idx << '\n';

  return 0;
}

