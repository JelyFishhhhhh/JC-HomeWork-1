// Compute the square root of a huge integer.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;
using std::setfill;

#include <vector>
using std::vector;

#include <cstring>
#include <cmath>

// put the square root of hugeInt into the array squareRoot
vector< long long int > compSquareRoot( vector< long long int > &hugeInt );

// put the square of hugeInt into the array square
vector< long long int > compSquare( vector< long long int > &hugeInt );

bool equal( vector< long long int > &hugeInt1, vector< long long int > &hugeInt2 );

// if hugeInt1 < hugeInt2, retuen true; otherwise, return false
bool less( vector< long long int > &hugeInt1, vector< long long int > &hugeInt2 );

const int arraySize = 1010;

int main(){
   std::ios::sync_with_stdio(0);
   cin.tie(0);
   cout.tie(0);
   int testCase;
   cin >> testCase;
   for( int i = 1; i <= testCase; i++ ){
      char str[ arraySize ] = {};
      cin >> str;

      size_t numDigits = strlen( str );
      if( numDigits < 10 ){

         cout << sqrt( atoi( str ) ) << endl;
      }
      else{
         vector< long long int > digits( numDigits + 3 );
         for( size_t j = 0; j < numDigits; ++j ){

            digits[ j ] = static_cast< int >( str[ numDigits - 1 - j ] ) - '0';
         }

         size_t last = ( numDigits - 1 ) / 4;
         vector< long long int > hugeInt( last + 1 );
         for( size_t j = 0; j <= last; j++ ){

            hugeInt[ j ] = digits[ 4 * j ] +
                          digits[ 4 * j + 1 ] * 10 +
                          digits[ 4 * j + 2 ] * 100 +
                          digits[ 4 * j + 3 ] * 1000;
         }

         // put the square root of hugeInt into the array squareRoot
         vector< long long int > squareRoot = compSquareRoot( hugeInt );

         cout << squareRoot[ squareRoot.size() - 1 ];
         for( int j = squareRoot.size() - 2; j >= 0; j-- ){

            cout << setw( 4 ) << setfill( '0' ) << squareRoot[ j ];
         }
         cout << endl;
      }

      if( i < testCase ){

         cout << endl;
      }
   }

   system( "pause" );
}

// put the square root of hugeInt into the array squareRoot
vector<long long int> compSquareRoot(vector<long long int>& hugeInt) {
   int sqrtSize = (hugeInt.size() + 1) / 2;
   vector<long long int> squareRoot(sqrtSize);
   vector<long long int> square(hugeInt.size()+ 1);

   for (int i = sqrtSize - 1; i >= 0; i--) { // Use int for loop variable
      long long int low = 0;
      long long int high = 9999;
      long long int mid;

      while (low <= high) {
         mid= (low + high) / 2;
         squareRoot[i] = mid;
         square = compSquare(squareRoot);
         if (equal(square, hugeInt)) {
            
            high = mid;
            break;
         } 
         else if (less(square, hugeInt)) {
            
            low = mid + 1;
         } 
         else {
            
            high = mid - 1;
         }
      }
      
      squareRoot[i] = high;
   }

   return squareRoot;
}

// put the square of hugeInt into the array square
vector< long long int > compSquare( vector< long long int > &hugeInt )
{
   int squareSize = 2* hugeInt.size();
   vector<long long int> square(squareSize);

   for (long long int ix = 0; ix < hugeInt.size(); ix++){
      for (long long int iy = 0; iy < hugeInt.size(); iy++){
         square[ix + iy] += hugeInt[ix] * hugeInt[iy];
      }
   }

   for (int i = 0; i < squareSize; i++){
      square[i + 1] += square[i] / 10000;
      square[i] %= 10000;
   }

   // Remove leading zeros in the square
   while (square.size() > 1 && square.back() == 0){
      
      square.pop_back();
   }

   return square;
}

// if hugeInt1 < hugeInt2, retuen true; otherwise, return false
bool equal( vector< long long int > &hugeInt1, vector< long long int > &hugeInt2 )
{

   if(hugeInt1.size()!= hugeInt2.size()){

      return false;
   }
   for(int i= hugeInt1.size()- 1; i>= 0; i--){

      if(hugeInt1[i]!= hugeInt2[i]){

         return false;
      }
   }

   return true;
}

// if hugeInt1 < hugeInt2, retuen true; otherwise, return false
bool less( vector< long long int > &hugeInt1, vector< long long int > &hugeInt2 )
{

   if(hugeInt1.size()< hugeInt2.size()){

      return true;
   }
   else if(hugeInt1.size()> hugeInt2.size()){

      return false;
   }
   for(int i= hugeInt1.size()- 1; i>= 0; i--){

      if(hugeInt1[i]< hugeInt2[i]){

         return true;
      }
      else if(hugeInt1[i]> hugeInt2[i]){

         return false;
      }
   }

   return false;
}
