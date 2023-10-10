#include<bits/stdc++.h>
using namespace std;
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define M 32
int bits[ M ];
int numBits;

// puts the binary representation of number into bits, and
// puts the the number of bits of the binary representation of number into numBits
// for example, if number is 10, then numBits == 4, and
// bits[ 3 ] = 1, bits[ 2 ] = 0, bits[ 1 ] = 1 and bits[ 0 ] = 0
void decimalToBinary( int number ){
   
   bits[numBits++]= number% 2;
   number/= 2;
   if(number> 0){
      decimalToBinary(number);
   }
}

// prints bits[ last ], bits[ last - 1 ], . . ., bits[ 0 ]
void displayBinary( int last ){

   cout<< bits[last--];
   if(last>= 0){
      displayBinary(last);
   }
}

// returns bits[ 0 ] + bits[ 1 ] + . . . + bits[ last ],
// or equivalently the number of 1s in the binary representation of number,
// for example, if number is 10, then returns 2
int sumBits( int last ){
   
   if(last){

      return bits[last]+ sumBits(last- 1);
   }
   return bits[last];
}


int main(){
   fastio;
   int number;
   
   while( cin>> number&& number){
      memset( bits, 0, sizeof( bits ) );
      numBits = 0;

      decimalToBinary( number );

      cout << "The parity of ";
      displayBinary( numBits - 1 );

      cout << " is " << sumBits( numBits - 1 ) << " (mod 2).\n";

      
   }

}
