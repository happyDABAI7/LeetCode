#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int a[N], n, M;

int check(int mid)
{
    int ans = 1, pri = 1;
    for (int i = 2; i <= n; i++)
    {
        if ((a[i] - a[pri]) >= mid)
        {
            ans++;
            pri = i;
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    cin >> n >> M;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + n + 1); // [a+1,a+n+1)
    // 题目没有明确说输入的数组元素是有序的，所以要排序

    int ans, l = 0, r = 1e9 + 5;
    // int ans, l = 1, r = a[n] - a[1]; // 优化右边界

    while (l <= r)
    {
        int mid = (l + r) / 2;
        // int mid = l + (r - l) / 2; // 防止溢出

        if (check(mid) >= M) // 如果能种>=M棵树，说明当前mid可行，尝试更大的距离
        {
            ans = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    cout << ans << '\n';

    return 0;
}
