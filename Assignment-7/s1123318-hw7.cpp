// Compute the square root of a huge integer.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;
using std::setfill;

#include <cstring>
#include <cmath>

struct HugeInt
{
   size_t size = 0;
   long long int *integer = nullptr;
};

// put the square root of hugeInt into the array squareRoot
HugeInt compSquareRoot( HugeInt &hugeInt );

// put the square of hugeInt into the array square
HugeInt compSquare( HugeInt &hugeInt );

// if hugeInt1 == hugeInt2, return true; otherwise, return false
bool equal( HugeInt &hugeInt1, HugeInt &hugeInt2 );

// if hugeInt1 < hugeInt2, return true; otherwise, return false
bool less( HugeInt &hugeInt1, HugeInt &hugeInt2 );

int main(){
   std::ios::sync_with_stdio(0);
   cin.tie(0);
   cout.tie(0);
   int testCase;
   cin >> testCase;
   for( int i = 1; i <= testCase; i++ )
   {
      char str[ 1010 ] = {};
      cin >> str;

      size_t numDigits = strlen( str );
      if( numDigits < 10 )
         cout << sqrt( atoi( str ) ) << endl;
      else
      {
         int *digits = new int[ numDigits + 3 ]();
         for( size_t j = 0; j < numDigits; ++j )
            digits[ j ] = static_cast< int >( str[ numDigits - 1 - j ] ) - '0';

         size_t last = ( numDigits - 1 ) / 4;
         HugeInt hugeInt;
         hugeInt.size = last + 1;
         hugeInt.integer = new long long int[ hugeInt.size ](); // the square root of hugeInt
         for( size_t j = 0; j <= last; j++ )
            hugeInt.integer[ j ] = digits[ 4 * j ] +
                                  digits[ 4 * j + 1 ] * 10 +
                                  digits[ 4 * j + 2 ] * 100 +
                                  digits[ 4 * j + 3 ] * 1000;

         HugeInt squareRoot = compSquareRoot( hugeInt );

         cout << squareRoot.integer[ squareRoot.size - 1 ];
         for( int j = squareRoot.size - 2; j >= 0; j-- )
            cout << setw( 4 ) << setfill( '0' ) << squareRoot.integer[ j ];
         cout << endl;

         delete[] squareRoot.integer;
         delete[] hugeInt.integer;
         delete[] digits;
      }

      if( i < testCase )
         cout << endl;
   }
}

// put the square root of hugeInt into the array squareRoot
HugeInt compSquareRoot( HugeInt &hugeInt )
{
   HugeInt squareRoot;
   HugeInt square;
   square.size= hugeInt.size+ 1;
   square.integer= new long long int [square.size]();
   squareRoot.size= (hugeInt.size+ 1)/ 2;
   squareRoot.integer= new long long int [squareRoot.size]();
   for(int i= squareRoot.size- 1; i>= 0; i--){

      long long int low= 0;
      long long int high= 9999;
      long long int mid;
      while(low<= high){
         
         mid= (low+ high)/ 2;
         squareRoot.integer[i]= mid;
         square= compSquare(squareRoot);
         
         if(equal(square, hugeInt)){
            high= mid;
            break;
         }
         else if(less(square, hugeInt)){
            low= mid+ 1;
         }
         else{
            high= mid- 1;
         }
      }
      squareRoot.integer[i]= high;
   }

   return squareRoot;
}

// put the square of hugeInt into the array square
HugeInt compSquare( HugeInt &hugeInt )
{
   HugeInt square;
   square.size= hugeInt.size+ hugeInt.size;
   square.integer = new long long int[square.size]();
   for(int ix= 0; ix< hugeInt.size; ix++){
      for(int iy= 0; iy< hugeInt.size; iy++){
      
         square.integer[ix+ iy]+= hugeInt.integer[ix]* hugeInt.integer[iy];
      }
   }
   for(int i= 0; i< square.size; i++){
      
      square.integer[i+ 1]+= square.integer[i]/ 10000;
      square.integer[i]%= 10000;
   }
   while(square.size> 1 && square.integer[square.size- 1]== 0){

      square.size--;
   }

   return square;
}

// if hugeInt1 == hugeInt2, return true; otherwise, return false
bool equal( HugeInt &hugeInt1, HugeInt &hugeInt2 )
{

   if(hugeInt1.size!= hugeInt2.size){
      
      return false;
   }
   for(int i= hugeInt1.size- 1; i>= 0; i--){

      if(hugeInt1.integer[i]!= hugeInt2.integer[i]){

         return false;
      }
   }
   
   return true;
}

// if hugeInt1 < hugeInt2, retuen true; otherwise, return false
bool less( HugeInt &hugeInt1, HugeInt &hugeInt2 )
{

   if(hugeInt1.size< hugeInt2.size){
      return true;
   }
   else if(hugeInt1.size> hugeInt2.size){
      return false;
   }
   for(int i= hugeInt1.size- 1; i>= 0; i--){

      if(hugeInt1.integer[i]< hugeInt2.integer[i]){
         
         return true;
      }
      else if(hugeInt1.integer[i]> hugeInt2.integer[i]){
         
         return false;
      }
   }

   return false;
}