#include <iostream>
using namespace std;

int main()
{
  int n;cin>>n;
  int a,b,c;cin>>a>>b>>c;
  int ans=0;

  for(int i=1;i<=n;i++){
    if(i%a!=0 && i%b!=0 && i%c!=0) ans++;
  }
  cout<<ans<<'\n';
  return 0;
}
