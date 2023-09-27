// 11332 - Summing Digits

#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

#define M 2000000000

signed main(){

    fastio;

    string number;
    ll sum;
    while(cin>> number&& number!= "0"){
        if(number.size()== 1){
            
            sum= number[0]- '0';
        }
        while(number.size()!=1){
            sum= 0;
            for(ll i= 0; i< number.size(); i++){
                sum+= (number[i]- '0');
            }
            number= to_string(sum);
        }
        cout<< sum<<"\n";
    }
}
