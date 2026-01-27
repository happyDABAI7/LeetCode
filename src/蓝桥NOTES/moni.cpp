#include <iostream>
using namespace std;

const int N=105;
int a[N][N],b[N][N];

int main()
{
  int n,m;cin>>n>>m;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      cin>>a[i][j];
    }
  }

  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      if(a[i][j]==1) b[i][j]=9;
      else{
        for(int _i=max(1,i-1);_i<=min(n,i+1);_i++){  //------------
          for(int _j=max(1,j-1);_j<=min(n,j+1);_j++){  //------------
            if(a[_i][_j]) b[i][j]++;
          }
        }
      }
    }
  }

  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      cout<<b[i][j]<<' ';
    }
    cout<<"\n";
  }

  return 0;
}
