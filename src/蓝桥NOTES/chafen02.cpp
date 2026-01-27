#include <iostream>
using namespace std;

#define ll long long

const ll N = 5*1e5 + 3;
ll a[N],d[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n,q;
    cin>>n>>q;
    for(ll i=1;i<=n;i++) {
        cin>>a[i];
        d[i]=a[i]-a[i-1];
    }

    for(ll i=0;i<q;i++){
        ll l,r,x;
        cin>>l>>r>>x;
        d[l]+=x;
        d[r+1]-=x;
    }
    for(ll i=1;i<=n;i++){
        a[i]=a[i-1]+d[i];
    }

    for(ll i=1;i<=n;i++) cout<<max(a[i],0LL)<<' ';
    cout<<'\n';

    return 0;
}