#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 10;
int a[N], L, n, M;

int check(int mid)
{
    int ans = 0, pri = 0;
    for (int i = 1; i <= n; i++) // i从1开始，为了检测起点岩石与第一块岩石
    {
        if ((a[i] - a[pri]) < mid)
        {
            ans++;
            continue;
        }
        pri = i;
    }
    if ((L - a[pri]) < mid)
        ans++; // 注意终点和起点的岩石并不在数组a[]中，起点岩石为0，终点岩石为L，这些要考虑，所以这里单独检测终点
    return ans;
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    cin >> L >> n >> M;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    int ans, l = 0, r = 1e9 + 5;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (check(mid) <= M)
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

// 思路：
