#include <iostream>
using namespace std;
int main()
{
  int sum=0;
  int n;cin>>n;
  for(int i=1;i<=n;i++){
    int m=i;
    while(i){
      int t=i%10;
      if(t==2||t==0||t==1||t==9) {
        sum+=m;
        break;
      }
      i/=10;
    }
  }
  cout<<sum<<'\n';
  return 0;
}
//上面的代码是错的，因为i在内外两层循环中不仅都存在，且都在变化，破环了循环状态！！！

#include <iostream>
using namespace std;
int main()
{
  int sum=0;
  int n;cin>>n;
  for(int i=1;i<=n;i++){
    int m=i;
    while(m){
      int t=m%10;
      if(t==2||t==0||t==1||t==9) {
        sum+=i;
        break;
      }
      m/=10;
    }
  }
  cout<<sum<<'\n';
  return 0;
}
//正确
