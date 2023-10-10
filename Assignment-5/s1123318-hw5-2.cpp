#include<bits/stdc++.h>
using namespace std;
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

// prints the binary representation of number,
// for example, if number is 10, then prints 1010
void displayBinary( int number ){
   
   if(number/ 2){

      displayBinary(number/ 2);
   }
   cout<< number% 2;
   number/= 2;
}

// returns the sum of all bits of the binary representation of number,
// or equivalently the number of 1s in the binary representation of number,
// for example, if number is 10, then returns 2
int sumBits( int number ){

   if(number){

      return number% 2+ sumBits(number/ 2);
   }
   return number% 2;
}

int main(){
   fastio;
   int number;
   while( cin>> number && number ){
      cout << "The parity of ";
      displayBinary( number );

      cout << " is " << sumBits( number ) << " (mod 2).\n";

   }

}
