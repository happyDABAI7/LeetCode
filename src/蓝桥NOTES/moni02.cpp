#include <iostream>
using namespace std;

const int N=105;
int a[N][N],b[N][N];

int main()
{
  int n,m; cin>>n>>m;
  int t; cin>>t;
  for(int i=1;i<=t;i++){
    int x,y; cin>>x>>y;
    a[x][y]=1;
  }
  int k; cin>>k;

  while(k--){
    for(int i=1;i<=n;i++){
      for(int j=1;j<=m;j++){
        if(a[i][j]) b[i][j]=b[i-1][j]=b[i][j-1]=b[i+1][j]=b[i][j+1]=1;  //成立原因：b足够大，且从1开始，不用担心越界
      }
    }
    for(int i=1;i<=n;i++){
      for(int j=1;j<=m;j++){
        a[i][j]=b[i][j];
      }
    }
  }

  int ans=0;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      if(a[i][j]) ans++;
    }
  }
  cout<<ans<<'\n';

  return 0;
}

