#include <iostream>
#include <cstring>
using namespace std;

#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), cin.ignore(0)
#define ll long long
#define M 250

// product = multiplicand * multiplier

void multiplication( int multiplicand[], int multiplier[], int product[],
                     int multiplicandSize, int multiplierSize, int &productSize ){
   
   /* Multiple & Carry */

   for(ll ix= 0; ix< multiplicandSize; ix++){

      for(ll iy= 0; iy< multiplierSize; iy++){
   
         product[(ix+ iy)]+= (multiplicand[ix]* multiplier[iy]);     // Multiple
         product[(ix+ iy+ 1)]+= (product[(ix+ iy)]/ 10);             // Carry
         product[(ix+ iy)]%= 10;
      }

   }

   /* Refresh Product Size */
   
   while(productSize> 1&& !product[productSize- 1]){
      
      productSize--;
   }
}

int main(){
   fastio;

   char strX[ M+ 1 ];   // multiplicand
   char strY[ M+ 1 ];   // multiplier
   
   /* Reset strX & strY */
   
   memset(strX, '\0', M+ 1);
   memset(strY, '\0', M+ 1);

   while( cin >> strX >> strY ){        // cin multiplicand, multiplier as string

      /* multiplicand: str-> int array & reverse it */
      
      int multiplicand[ M ];
      int multiplicandSize = strlen( strX );
      memset(multiplicand, 0, multiplicandSize* sizeof(int));

      for( int i = 0; i < multiplicandSize; i++ ){
         
         multiplicand[ multiplicandSize - i - 1 ] = int(strX[ i ] - '0');   
      }
      
      /* multiplier: str-> int array & reverse it */

      int multiplier[ M ];
      int multiplierSize = strlen( strY );
      memset(multiplier, 0, multiplierSize* sizeof(int));

      for( int i = 0; i < multiplierSize; i++ ){
         
         multiplier[ multiplierSize - i - 1 ] = int(strY[ i ] - '0');
      }

      /* init product */

      int product[2* M+ 2];
      int productSize = multiplicandSize + multiplierSize;
      memset(product, 0, (productSize+ 1)* sizeof(int));

      /* Multiple IT ! */

      multiplication( multiplicand, multiplier, product, multiplicandSize, multiplierSize, productSize );

      /* Output Result */

      for( int i = (productSize- 1) ; i >= 0; i-- ){
         
         cout << product[ i ];
      }
      cout<< '\n';

      /* Reset strX & strY */

      memset(strX, '\0', (M+ 1)* sizeof(char));
      memset(strY, '\0', (M+ 1)* sizeof(char));
   }

   return 0;
}
