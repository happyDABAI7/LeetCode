#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e5 + 9;
int a[N];
vector<int> L;  //离散化数组

int getindex(int x) {
    return lower_bound(L.begin(), L.end(), x) - L.begin();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        L.push_back(a[i]);
    }

    //排序去重
    sort(L.begin(), L.end());
    L.erase(unique(L.begin(), L.end()), L.end());
    
    cout<<"lisan: "<<'\n';
    for(const auto &x:L){
        cout<<x<<' ';
    }
    cout<<'\n';

    int index;
    cin>>index;
    cout<<index<<"'s location is: "<<getindex(index)<<'\n';

    return 0;
}