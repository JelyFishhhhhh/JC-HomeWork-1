// 11364 - Parking

#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long

using namespace std;

signed main(){

    fastio;

    vector<ll> seq;

    ll times, n;

    cin>> times;

    for(ll i= 0; i< times; i++){

        cin>> n;
        seq.assign(n, 0);

        while(n--){
            
            cin>> seq[n];
        }
        sort(seq.begin(), seq.end());
        cout<< (seq.back()- seq.front())*2<<"\n";
    }
}