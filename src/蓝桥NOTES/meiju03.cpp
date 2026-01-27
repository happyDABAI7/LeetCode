#include <iostream>
#include <map>
using namespace std;

map<int,int> a;

int main()
{
  int n,m;cin>>n>>m;
  for(int i=1;i<=n*m;i++){
    int x;
    cin>>x;
    a[x]++;
  }

  for(const auto&[x,y]:a){
    if(2*y>n*m) cout<<x<<'\n';
  }

  return 0;
}