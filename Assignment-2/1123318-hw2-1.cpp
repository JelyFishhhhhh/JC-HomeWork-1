// 10783 - Odd Sum

#include <bits/stdc++.h>
#define ll long long
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

signed main(){

    fastio;

    ll a, b, times;

    cin>>times;
    for(ll idx= 0; idx< times; idx++){
        cin>> a>> b;
        a+=!(a%2);
        b-=!(b%2);
        cout<<"Case "<<idx+1<<": "<<(a+b)*(b-a+2)/4<<"\n";
    }
}