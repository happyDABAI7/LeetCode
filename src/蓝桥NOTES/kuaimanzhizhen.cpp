#include <iostream>
#include <algorithm>
using namespace std;

const int N=1e5+10;
int a[N];

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n,s;
  cin>>n>>s;
  for(int i=1;i<=n;i++) cin>>a[i];

  int ans=n+1;
  
  for(int i=1,j=0,sum=0;i<=n;i++){
    while(i>j||(j+1<=n&&sum<s)) sum+=a[++j];
    if(sum>=s) ans=min(ans,j-i+1);
    sum-=a[i];
  }

  cout<<(ans>n?0:ans)<<'\n';

  return 0;
}

