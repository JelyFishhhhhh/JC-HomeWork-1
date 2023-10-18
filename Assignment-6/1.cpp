// Compute the square root of a huge integer.
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define arraySize 10000

// put the square of hugeInt into the array square
void compSquare( ll *hugeInt, ll *square, int hugeIntSize, ll &squareSize ){

   /* Multiple-N-Carry */
   for(ll ix= 0; ix< hugeIntSize; ix++){
      
      for(ll iy= 0; iy< hugeIntSize; iy++){
         
         square[ix+ iy]+= hugeInt[ix]* hugeInt[iy];
         square[ix+ iy+ 1]+= square[ix+ iy]/ 10000;
         square[ix+ iy]%= 10000;
      }
   }
   while(!square[squareSize- 1] && squareSize> 1){

      squareSize--;
   }
}



signed main(){
   
   fastio;
   int testCase;
   cin >> testCase;
   for( int i = 1; i <= testCase; i++ ){
      char str[ arraySize ] = {};
      cin >> str;

      ll numDigits = strlen( str );
      if( numDigits > 10 ){

         cout << sqrt( atoi( str ) ) << endl;
      }
      else{
         int *digits = new int[ numDigits + 3 ]();
         for( ll j = 0; j < numDigits; ++j ){

            digits[ j ] = static_cast< int >( str[ numDigits - 1 - j ] ) - '0';
         }

         ll last = ( numDigits - 1 ) / 4;
         ll hugeIntSize = last + 1;
         ll *hugeInt = new ll[ hugeIntSize ]();
         for( ll j = 0; j <= last; j++ ){

            hugeInt[ j ] = digits[ 4 * j ] +
                           digits[ 4 * j + 1 ] * 10 +
                           digits[ 4 * j + 2 ] * 100 +
                           digits[ 4 * j + 3 ] * 1000;
         }

         ll sqrtSize = hugeIntSize* 2; // the number of digits of squareRoot is sqrtSize
         ll *square = new ll[ sqrtSize ](); // the square root of hugeInt

         // put the square root of hugeInt into the array squareRoot
         compSquare(hugeInt, square, hugeIntSize, sqrtSize);

         cout << square[ sqrtSize - 1 ];
         for( int j = sqrtSize - 2; j >= 0; j-- ){

            cout << setw( 4 ) << setfill( '0' ) << square[ j ];
         }
         cout << "\n";

         //delete[] squareRoot;
         delete[] hugeInt;
         delete[] digits;
      }

      if( i < testCase ){

         cout << endl;
      }
   }

}
