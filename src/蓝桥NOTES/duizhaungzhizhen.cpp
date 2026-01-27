#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e6 + 9;
char s[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>s+1;
    int n=strlen(s+1);
    int l=1, r=n;
    bool flag=true;
    while(l<r){
        if(s[l]!=s[r]){
            flag=false;
            break;
        }
        l++;
        r--;
    }
    cout<<(flag ? "Y" : "N")<<'\n';
    return 0;
}