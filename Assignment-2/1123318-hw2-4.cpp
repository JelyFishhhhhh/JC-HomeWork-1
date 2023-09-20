// 11934 - Magic Formula

#include<bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

signed main(){
    fastio;
    ll a, b, c, d, L, x;
    while(cin>>a>>b>>c>>d>>L){
        if(!a && !b  && !c && !d && !L){
            return 0;
        }
        ll count = 0;
        for(x= 0;x <= L; x++){
            if(!((a*x*x+b*x+c)%d)){
                count++;
            }
        }
        cout<<count<<'\n';
    }
}