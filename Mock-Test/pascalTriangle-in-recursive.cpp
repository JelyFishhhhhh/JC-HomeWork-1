#include <iostream>
#include <string>
using namespace std;

int factor(int a){

    if (a==0){
        
        return 1;
    }
    else{
        
        return a*factor(a-1);
    }
}

// calculate kCn= k!/ n!* (k- n)!
int combine(int n, int k){

    if(k== 0|| k== n){

        return 1;
    }
    else if(1< k && k< n){

        return combine(n- 1, k- 1)+ combine(n- 1, k); 
    }
    else{

        return factor(k)/ (factor(n)* factor(k- n));
    }
 
}

int main(){
    
    int n;
    cin >> n;
    for(int ix= 0; ix<= n; ix++){
        cout<< "Line"<< ix<< ": "; 
        
        for(int iy= 0; iy<= ix; iy++){
            
            cout<< combine(iy, ix)<<" ";
        }

        cout<<"\n";
    }
    
}