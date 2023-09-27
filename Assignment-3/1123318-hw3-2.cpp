#include <iostream>
#include <cstring>
using namespace std;

#define ll long long
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define M 10005

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
   for(ll i= (size1- 1); i>= 0; i--){
      if(hugeInt1[i]< hugeInt2[i]){

         return true;
      }
      if(hugeInt1[i]> hugeInt2[i]){

         return false;
      }
   }
   return false;
}

// difference = minuend - subtrahend provided that minuend > subtrahend
void subtraction( int minuend[], int subtrahend[], int difference[],
                  int minuendSize, int subtrahendSize, int &differenceSize ){
   
   /* Minus & Borrow */
   for(ll i= 0; i< minuendSize; i++){
      
      while(i> (subtrahendSize- 1)&& i< minuendSize){

         difference[i]+= minuend[i];
         if(difference[i]< 0){

            difference[(i+ 1)]--;
            difference[i]+= 10; 
         }
         i++;
      }

      /* Minuend- Subtrahend */
      difference[i]+= (minuend[i]- subtrahend[i]);
      
      /* Borrow */
      if(difference[i]< 0){

         difference[(i+ 1)]--;
         difference[i]+= 10;
      }
   }

   /* Refresh Difference Size */
   while(differenceSize> 1&& !difference[differenceSize-1]){
      
      differenceSize--;
   }
   return;
}


int main(){
   fastio;
   int n;
   cin >> n;
   
   char strA[ M ], strB[ M ];
   int numA[ M ], numB[ M ], numC[ M ];
   /* init array */
   memset(strA, '\0', M);
   memset(strB, '\0', M);
   memset(numA, 0, M);
   memset(numB, 0, M);
   memset(numC, 0, M);

   for( int k = 0; k < n; ++k ){       // cin number of case
      
      cin >> strA >> strB;
      
      /* Minuend: str-> int & reversee it */
      
      int sizeA = strlen( strA );
      for( int i = 0; i < sizeA; ++i ){
         numA[ i ] = (strA[ sizeA - 1 - i ] - '0');
      }
      
      /* Subtrahend: str-> int & reverse it */
      
      int sizeB = strlen( strB );
      for( int i = 0; i < sizeB; ++i ){
         numB[ i ] = (strB[ sizeB - 1 - i ] - '0');
      }
      
      /* Difference init */
      
      int sizeC = max(sizeA, sizeB);
      
      /* Calculate */
      
      if( isNegative( numA, numB, sizeA, sizeB ) ){      // numB> numA
         
         cout << "-";
         subtraction( numB, numA, numC, sizeB, sizeA, sizeC );
      }
      else if( isNegative( numB, numA, sizeB, sizeA ) ){ // numA> numB
         
         subtraction( numA, numB, numC, sizeA, sizeB, sizeC );
      }
      else{                                              // numA== numB
         
         sizeC = 1;
         numC[ 0 ] = 0;
      }
      
      /* Output Result */
      
      for( int i = (sizeC - 1); i >= 0; i-- ){
         
         cout << numC[ i ];
      }
      cout << '\n';

      /* Reset strA, strB, numA, numB, numC */
      
      memset(strA, '\0', M);
      memset(strB, '\0', M);
      memset(numA, 0, M);
      memset(numB, 0, M);
      memset(numC, 0, M);
   }

   return 0;
}
