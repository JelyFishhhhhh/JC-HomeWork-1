// Compute the square root of a huge integer.
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define arraySize 1010

bool recursiveEqual( ll *hugeInt1, ll *hugeInt2, int last ){
   
   if(hugeInt1[last]!= hugeInt2[last]){

      return false;
   }
   if(last> 0){

      return recursiveEqual(hugeInt1, hugeInt2, last- 1);
   }
   return true;
}

// if hugeInt1 == hugeInt2, return true; otherwise, return false
bool isEqual( ll *hugeInt1, ll *hugeInt2, int size1, int size2 ){
   
   if( size1 != size2 ){

      return false;
   }

   return recursiveEqual( hugeInt1, hugeInt2, size1 - 1 );
}

bool recursiveLess( ll *hugeInt1, ll *hugeInt2, int last ){

   if(hugeInt1[last]< hugeInt2[last]){
      
      return true;
   }
   
   if(hugeInt1[last]> hugeInt2[last]){
   
      return false;
   }

   if(last> 0){

      return recursiveLess(hugeInt1, hugeInt2, last- 1);
   }
   return false;
}

// if hugeInt1 < hugeInt2, return true; otherwise, return false
bool isLess( ll *hugeInt1, ll *hugeInt2, int size1, int size2 ){
   
   if( size1 < size2 ){

      return true;
   }

   if( size1 > size2 ){

      return false;
   }

   return recursiveLess( hugeInt1, hugeInt2, size1 - 1 );
}

// put the square of hugeInt into the array square
void compSquare( ll *hugeInt, ll *square, int hugeIntSize, int &squareSize ){

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

// put the square root of hugeInt into the array squareRoot
void compSquareRoot( ll *hugeInt, ll *squareRoot, int hugeIntSize, int sqrtSize ){
   
   int squareSize = hugeIntSize;

   for(ll i= sqrtSize- 1; i>= 0; i--){
      
      ll low= 0, high= 9999;
      while(low<= high){
      
         ll *square = new ll[ squareSize ]();
         squareRoot[i]= (low+ high)/ 2;   
         compSquare(squareRoot, square, sqrtSize, squareSize);
         if(isEqual(hugeInt, square, hugeIntSize, squareSize)){
            
            delete[] square;
            return;
         }
         if(isLess(hugeInt, square, hugeIntSize, squareSize)){

            high= squareRoot[i]- 1;            
         }
         else{
            
            low= squareRoot[i]+ 1;
         } 
         delete[] square;
      }

   }
}

signed main(){
   
   fastio;
   int testCase;
   cin >> testCase;
   while(testCase--){

      char str[ arraySize ] = {};
      cin >> str;
      ll numDigits = strlen( str );
      if( numDigits < 10 ){

         cout << sqrt( atoi( str ) ) << '\n';
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
         ll sqrtSize = ( hugeIntSize + 1 ) / 2; // the number of digits of squareRoot is sqrtSize
         ll *squareRoot = new ll[ sqrtSize ](); // the square root of hugeInt

         // put the square root of hugeInt into the array squareRoot
         compSquareRoot( hugeInt, squareRoot, hugeIntSize, sqrtSize );
         cout << squareRoot[ sqrtSize - 1 ];
         for( int j = sqrtSize - 2; j >= 0; j-- ){

            cout << setw( 4 ) << setfill( '0' ) << squareRoot[ j ];
         }
         cout << '\n';

         delete[] squareRoot;
         delete[] hugeInt;
         delete[] digits;
      }
   }
   return 0;
}
