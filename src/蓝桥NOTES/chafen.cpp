#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 3;
int a[N],d[N];

void solve(int n,int m){
    for (int i = 1; i <= n; i++){
        cin>>a[i];
        d[i]=a[i]-a[i-1];
    }
    for(int i=0;i<m;i++){
        int x,y,z;
        cin>>x>>y>>z;
        d[x]+=z;
        d[y+1]-=z;
    }
    
    for (int i = 1; i <= n; i++){
        a[i]=a[i-1]+d[i];
    }
    for (int i = 1; i <= n; i++){
        cout<<a[i]<<' ';
    }
    cout<<'\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,m;
    while(cin>>n>>m) solve(n,m);

    return 0;
}