#include <bits/stdc++.h>
using namespace std;
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define M 1000
#define M2 2000

const int twoHundred = 200;
const int hundred = 100;

// returns true if and only if the specified huge integer is zero
bool isZero( int hugeInt[], int size ){
   
   for( int i = 0; i < size; i++ ){

      if( hugeInt[ i ]){

         return false;
      }
   }
   return true;
}

// returns true if and only if hugeInt1 < hugeInt2
bool isNegative( int hugeInt1[], int hugeInt2[], int size1, int size2 ){
   
   // Subtrahend >> Minuend
   if(size1< size2){

      return true;
   }
   // Subtrahend << Minuend
   if(size1> size2){

      return false;
   }
   // Size1== Size2
   for(int i= (size1- 1); i>= 0; i--){
      if(hugeInt1[i]< hugeInt2[i]){

         return true;
      }
      if(hugeInt1[i]> hugeInt2[i]){

         return false;
      }
   }
   return false;
}

// --hugeInt
void decrement( int hugeInt[], int &size ){

   hugeInt[0]--;
   // borrow
   for(int i= 0; i< size; i++){

      if(hugeInt[i]< 0){

         hugeInt[i+1]--;
         hugeInt[i]+= 10;
      }
   }
   while(size> 0&& !hugeInt[size- 1]){
      
      size--;
   }
}

// minuend -= subtrahend provided that minuend > subtrahend
void subtraction( int minuend[], int subtrahend[], int &minuendSize, int subtrahendSize ){

   /* Minus & Borrow */
   for(int i= 0; i< minuendSize; i++){
      
      /* Minuend- Subtrahend */
      minuend[i]-= subtrahend[i];
      
      /* Borrow */
      if(minuend[i]< 0){

         minuend[i]+= 10;
         minuend[(i+ 1)]--;
      }
   }

   /* Refresh Difference Size */
   while(minuendSize> 0&& !minuend[minuendSize-1]){
      
      minuendSize--;
   }

}


// multiplicand *= multiplier
void multiplication( int multiplicand[], int multiplier[], int &multiplicandSize, int multiplierSize ){

   /* Multiple & Carry */
   int product[M2]= {0};
   int productSize= multiplicandSize+ multiplierSize;
   for(int ix= 0; ix< multiplicandSize; ix++){

      for(int iy= 0; iy< multiplierSize; iy++){
   
         product[(ix+ iy)]+= (multiplicand[ix]* multiplier[iy]);     // Multiple
         product[(ix+ iy+ 1)]+= (product[(ix+ iy)]/ 10);             // Carry
         product[(ix+ iy)]%= 10;
      }

   }

   /* Refresh Product Size */
   
   while(productSize> 0&& !product[productSize- 1]){
      
      productSize--;
   }
   /* Reset Multiplicand */
   memset(multiplicand, 0, productSize);
   /* Return product 2 multiplicand */
   for(int i= 0; i< productSize; i++){
   
      multiplicand[i]= product[i];
   }
   /* Return productSize 2 multiplicandSize */
   multiplicandSize= productSize;
}

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( int hugeInt[], int &size ){
   if( size == 1 ){

      hugeInt[ 0 ] = 0;
   }
   else{
      for( int i = 1; i < size; i++ ){

         hugeInt[ i - 1 ] = hugeInt[ i ];
      }

      hugeInt[ --size ] = 0;
   }
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int dividend[], int divisor[], int quotient[], int remainder[],
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize ){
   
   /* Assign divendend 2 remainder */
   for(int i= 0; i< dividendSize; i++){
      
      remainder[i]= dividend[i];
   }
   remainderSize= dividendSize;

   quotientSize= dividendSize- divisorSize;
   int buffer[M2]= {};
   int bufferSize= divisorSize+ quotientSize;

   for(int i= 0; i< bufferSize; i++){
      if(i< quotientSize){
         
         buffer[i]= 0;
         continue;
      }
      
      buffer[i]= divisor[i- quotientSize];
   }
   
   if(isNegative(remainder, buffer, remainderSize, bufferSize)){

      divideBy10(buffer, bufferSize);
   }
   else{
      
      quotientSize++;
   }
   
   memset(quotient, 0, quotientSize);
   for(int i= quotientSize-1; i>= 0; i--){
      
      while(!isNegative(remainder, buffer, remainderSize, bufferSize)){
         
         subtraction(remainder, buffer, remainderSize, bufferSize);
         quotient[i]++;   
         if(isZero(remainder, remainderSize)){
         
            return;
         }
      }
      
      divideBy10(buffer, bufferSize);
   }
   
}

signed main(){
   fastio;
   int t, a, b;
   // cin.ignore();
   while( cin >> t >> a >> b ){

      cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";
      if( t == 1 ){

         cout << "is not an integer with less than 100 digits.\n";
         continue;
      }
      if( a == b ){

         cout << "1\n";
         continue;
      }
      if( a < b ){

         cout << "is not an integer with less than 100 digits.\n";
         continue;
      }
      int dividend[ M2 ] = {};
      int divisor[ M ] = {};
      int quotient[ M ] = {};
      int remainder[ M ] = {};

      int dividendSize = 1;
      int divisorSize = 1;
      int quotientSize = 1;
      int remainderSize = 1;

      // put all digits of t into base
      int base[ M2 ] = {};
      int baseSize = 0;
      for( int i = t; i > 0; i /= 10 ){

         base[ baseSize++ ] = i % 10;
      }

      // dividend = pow( t, a )
      dividend[ 0 ] = 1;
      for( int i = 0; i < a; ++i ){
         multiplication( dividend, base, dividendSize, baseSize );
         if( dividendSize > twoHundred - baseSize ){

            break;
         }
      }

      if( dividendSize > twoHundred - baseSize ){

         cout << "is not an integer with less than 100 digits.\n";
      }
      else{
         // divisor = pow( t, b )
         divisor[ 0 ] = 1;
         for( int i = 0; i < b; ++i ){

            multiplication( divisor, base, divisorSize, baseSize );
            if( divisorSize > hundred - baseSize ){

               break;
            }
         }

         if( divisorSize > hundred - baseSize ){

            cout << "is not an integer with less than 100 digits.\n";
         }
         else{
            decrement( dividend, dividendSize ); // --dividend
            decrement( divisor, divisorSize );   // --divisor

            division( dividend, divisor, quotient, remainder,
                        dividendSize, divisorSize, quotientSize, remainderSize );

            // quotient is an integer with isNegative than hundred digits
            if( quotientSize < hundred && isZero( remainder, remainderSize ) ){

               for( int i = quotientSize - 1; i >= 0; i-- ){

                  cout << quotient[ i ];
               }
            }
            else{

               cout << "is not an integer with less than 100 digits.\n";
               continue;
            }
            cout << '\n';
         }
      }
   }
   return 0;
}
