#include <iostream>
using namespace std;

using ll = long long;
const ll N = 1e5+3;
const ll M = 1e9+7;
ll a[6][N],p[6][N];  //k较小，所以直接都求出来

int main()
{
  ll n,m;
  cin>>n>>m;
  for(ll i=1;i<=n;i++) cin>>a[1][i];
  for(int i=2;i<=5;i++){
    for(ll j=1;j<=n;j++){
      a[i][j]=a[i-1][j]*a[1][j]%M;  //模运算的规范写法是「每步计算都取模」，避免中间值溢出
    }
  }

  for(int i=1;i<=5;i++){
    for(ll j=1;j<=n;j++){
      p[i][j]=(p[i][j-1]+a[i][j])%M;
    }
  }

  for(ll i=0;i<m;i++){
    ll l,r,k;
    cin>>l>>r>>k;
    cout<<(p[k][r]-p[k][l-1]+M)%M<<"\n";  //注意加M防止负数
  }
  return 0;
}


//模运算对加法和乘法满足分配律：
// (a + b) % M = [(a % M) + (b % M)] % M
// (a × b) % M = [(a % M) × (b % M)] % M
