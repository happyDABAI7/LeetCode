#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n, m, k;

ll check(ll mid)
{
    ll ans = 0;
    for (ll i = 1; i <= n; i++)
        ans += min(m, mid / i);
    return ans;
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    cin >> n >> m >> k;

    ll ans, l = 0, r = 1e14;
    while (l <= r)
    {
        ll mid = (l + r) / 2;
        if (check(mid) >= k)
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    cout << ans << '\n';

    return 0;
}
