#include <iostream>
#include <cstring>
#include <algorithm> 
using namespace std;

const int N = 1010;
char s[N];

int prefix[N];

int main()
{
  cin>>s+1; // 输入从s[1]开始，适配前缀和的1-based索引
  int n=strlen(s+1);

  for(int i=1;i<=n;i++)
    prefix[i]=prefix[i-1]+(s[i]=='L'? 1:-1);

  int ans=0;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      if(prefix[j]-prefix[i-1]==0) ans=max(ans,j-i+1);
    }
  }
  
  cout<<ans<<'\n';

  return 0;
}

//前缀和思想：将问题转化为区间和问题，利用前缀和数组快速计算任意区间的和，从而提高效率。
//时间复杂度：O(n^2)，适用于n较小的情况。
//空间复杂度：O(n)，用于存储前缀和数组。

//前缀和数组prefix，其中prefix[i]表示字符串s从位置1到位置i的'L'和'R'的数量差（'L'计为+1，'R'计为-1）。
//通过计算prefix[j]-prefix[i-1]，可以快速得到区间[i, j]内'L'和'R'的数量差，从而判断该区间是否'L'和'R'数量相等。
//双重循环枚举所有可能的子串区间，计算并更新最长的'L'和'R'数量相等的子串长度。

//优化：
//可以使用哈希表来存储前缀和出现的位置，从而将时间复杂度优化到O(n)。
//具体做法是遍历前缀和数组，对于每个前缀和值，记录其第一次出现的位置。如果当前前缀和值已经存在于哈希表中，则计算当前索引与该前缀和第一次出现位置之间的距离，更新最长长度。
//这样可以避免双重循环，提高效率。
//示例代码如下：
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cstring>
using namespace std;

int main() {
    char s[1010];
    cin >> s + 1;
    int n = strlen(s + 1);
    
    unordered_map<int, int> pre_map;
    int pre = 0;   // 前缀和（L=1，R=-1）
    int ans = 0;   // 最长平衡子串长度
    
    pre_map[0] = 0;  // 必须初始化：前缀和0对应索引0
    
    for (int j = 1; j <= n; j++) {
        // 1. 计算当前前缀和（特征和）
        pre += (s[j] == 'L' ? 1 : -1);
        
        // 2. 直接判断pre是否在哈希表中（因为target=0，need=pre）
        if (pre_map.count(pre)) {
            ans = max(ans, j - pre_map[pre]);
        } else {
            // 3. 仅首次出现时存入哈希表（保证最长）
            pre_map[pre] = j;
        }
    }
    
    cout << ans << endl;
    return 0;
}
//该优化版本利用哈希表存储前缀和及其首次出现的位置，将时间复杂度降低到O(n)，适用于更大规模的数据输入。

// count(key) 的作用：判断哈希表中是否存在键为 key 的条目。
// 返回值：如果存在，返回 1；如果不存在，返回 0（因为 key 唯一，所以最多返回 1）。

// pre_map.count(pre) == true（pre 之前出现过）
// 含义：历史上存在一个索引 i = pre_map[pre]（i < j），使得「前 i 个字符的前缀和」=「前 j 个字符的前缀和」。
// 推论：子串 i+1 ~ j 的前缀和差值为 0 → 这个子串的 L 和 R 数量相等（平衡串）。
// 操作：计算这个子串的长度 j - i，用 max(ans, 长度) 更新答案（保留最长的长度）。


//模板：
#include <iostream>
#include <unordered_map>
#include <algorithm>  // max/min 函数需要
using namespace std;

// 通用模板：找满足 pre[j]-pre[i] = target 的最长子数组长度
int solve() {
    // 1. 输入处理（根据题目替换，比如数组/字符串）
    int n;  // 数组长度/字符串长度
    cin >> n;
    int a[n + 1];  // 1-based 数组（也可改用0-based，需统一索引）
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    // 2. 核心变量定义
    unordered_map<long long, int> pre_map;  // 哈希表：key=前缀和，value=首次出现的索引
    long long pre = 0;  // 前缀和（用long long避免溢出）
    int ans = 0;        // 最终答案（最长长度）
    int target = 0;     // 题目要求的目标差值（根据题目改，比如k、0等）
    
    // 3. 哈希表初始化：必须先存 pre=0 对应索引0（关键！）
    // 原因：前缀和为0的初始位置是0，否则会漏掉「从第一个元素开始的子数组」
    pre_map[0] = 0;
    
    // 4. 遍历计算前缀和 + 哈希表匹配
    for (int j = 1; j <= n; j++) {
        // 4.1 计算当前前缀和（核心：根据题目定义「特征和」）
        pre += a[j];  // 普通数组求和（若为字符串，需替换为字符的特征值，比如L=1, R=-1）
        
        // 4.2 查找是否存在 pre[j] - target
        long long need = pre - target;  //pre[i] = pre[j] - target
        if (pre_map.count(need)) {
            // 找到满足条件的i，计算子数组长度 j - pre_map[need]
            ans = max(ans, j - pre_map[need]);
        }
        
        // 4.3 仅记录首次出现的前缀和（保证子数组最长）
        if (!pre_map.count(pre)) {
            pre_map[pre] = j;
        }
    }
    
    return ans;
}

int main() {
    cout << solve() << endl;
    return 0;
}
//模板说明：
//1. 输入处理部分根据具体题目进行修改，适配不同的数据类型（数组/字符串等）。
//2. 目标差值 target 根据题目要求进行设置。
//3. 前缀和的计算方式根据题目定义的「特征和」进行调整。
//4. 哈希表 pre_map 用于存储前缀和及其首次出现的位置，确保计算最长子数组长度。
//保证i尽量小，从而使j-i尽可能大，得到最长子数组长度。
