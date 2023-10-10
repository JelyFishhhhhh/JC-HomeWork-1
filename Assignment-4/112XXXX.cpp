#include<iostream>
#include<cstring>
using std::cin;
using std::cout;
using std::endl;
const int twoHundred = 200;
const int hundred = 100;


// returns true if and only if the specified huge integer is zero
bool isZero( int hugeInt[], int size );

// returns true if and only if hugeInt1 < hugeInt2
bool less( int hugeInt1[], int hugeInt2[], int size1, int size2 );

// --hugeInt
void decrement( int hugeInt[], int &size );

// minuend -= subtrahend provided that minuend > subtrahend
void subtraction( int minuend[], int subtrahend[], int &minuendSize, int subtrahendSize );

// multiplicand *= multiplier
void multiplication( int multiplicand[], int multiplier[], int &multiplicandSize, int multiplierSize );

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int dividend[], int divisor[], int quotient[], int remainder[],
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize );

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( int hugeInt[], int &size );

int main()
{
   int t, a, b;
   while( cin >> t >> a >> b )
   {
      cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";

      if( t == 1 )
         cout << "is not an integer with less than 100 digits.\n";
      else if( a == b )
         cout << "1\n";
      else if( a < b )
         cout << "is not an integer with less than 100 digits.\n";
      else
      {
         int dividend[ twoHundred ] = {};
         int divisor[ hundred ] = {};
         int quotient[ hundred ] = {};
         int remainder[ hundred ] = {};

         int dividendSize = 1;
         int divisorSize = 1;
         int quotientSize = 1;
         int remainderSize = 1;

         // put all digits of t into base
         int base[ twoHundred ] = {};
         int baseSize = 0;
         for( int i = t; i > 0; i /= 10 )
            base[ baseSize++ ] = i % 10;

         // dividend = pow( t, a )
         dividend[ 0 ] = 1;
         for( int i = 0; i < a; ++i )
         {
            multiplication( dividend, base, dividendSize, baseSize );
            if( dividendSize > twoHundred - baseSize )
               break;
         }

         if( dividendSize > twoHundred - baseSize )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            // divisor = pow( t, b )
            divisor[ 0 ] = 1;
            for( int i = 0; i < b; ++i )
            {
               multiplication( divisor, base, divisorSize, baseSize );
               if( divisorSize > hundred - baseSize )
                  break;
            }

            if( divisorSize > hundred - baseSize )
               cout << "is not an integer with less than 100 digits.\n";
            else
            {
               decrement( dividend, dividendSize ); // --dividend
               decrement( divisor, divisorSize );   // --divisor

               division( dividend, divisor, quotient, remainder,
                  dividendSize, divisorSize, quotientSize, remainderSize );

               // quotient is an integer with less than 100 digits
               if( quotientSize < 100 && isZero( remainder, remainderSize ) )
                  for( int i = quotientSize - 1; i >= 0; i-- )
                     cout << quotient[ i ];
               else
                  cout << "is not an integer with less than 100 digits.";
               cout << endl;
            }
         }
      }
   }
}

// returns true if and only if the specified huge integer is zero
bool isZero( int hugeInt[], int size )
{
   for( int i = 0; i < size; i++ )
      if( hugeInt[ i ] != 0 )
         return false;
   return true;
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( int hugeInt1[], int hugeInt2[], int size1, int size2 )
{
 if(size1 < size2)
 {
  return true;
 }
 else if(size1 > size2)
 {
  return false;
 }
 else
 {
     for (int x = {size1 - 1}; x >= 0; x--)
     {
         if (hugeInt1[x] < hugeInt2[x])
             return true;
         else if (hugeInt1[x] > hugeInt2[x])
             return false;
     }
 }
  return false;

}

// --hugeInt
void decrement( int hugeInt[], int &size )
{
 hugeInt[0]--;
 for(int a = 0; a < size; a++)
 {
  if(hugeInt[a] < 0)
  {
   hugeInt[a+1] -= 1;
   hugeInt[a] = hugeInt[a] + 10;
  }
 }
 while(size >= 1 && hugeInt[size - 1] ==0)
 {
  size --;
 }

}

// minuend -= subtrahend provided that minuend > subtrahend
void subtraction( int minuend[], int subtrahend[], int &minuendSize, int subtrahendSize )
{
    for(int iy{0};iy<minuendSize;iy++)
    {
       minuend[iy]-=subtrahend[iy];
       if(minuend[iy]<0)
       {
          minuend[iy]+=10;
          minuend[iy+1]--;
       }
    }
    while(minuendSize>=1 && minuend[minuendSize-1]==0)
    {
       minuendSize--;
    }
}
// multiplicand *= multiplier
void multiplication( int multiplicand[], int multiplier[], int &multiplicandSize, int multiplierSize )
{
    int productSize=multiplicandSize+multiplierSize;
    int product[200]={0};
    for(int b = 0; b <multiplicandSize; b++)
    {
        for(int c = 0; c < multiplierSize; c++)
        {
            product[c + b] += multiplicand[b] * multiplier[c];          // b-> multiplicand's index, c-> multiplier's index
            product[c + b + 1] += product[c + b] / 10;
            product[c + b] = product[c + b] % 10;
        }
    }
    while(productSize > 1 && product[productSize - 1] == 0)
    {
        productSize--;
    }
    memset(multiplicand,0,productSize);
    for(int d = 0; d < productSize; d++)
    {
        multiplicand[d] = product[d];
    }
    multiplicandSize = productSize;
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int dividend[], int divisor[], int quotient[], int remainder[],
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize )
{
    int buffer[200];                        // buffer init
    int bufferSize;
    quotientSize=dividendSize-divisorSize;
    bufferSize=divisorSize+quotientSize;
    remainderSize=dividendSize;
    for(int i2{0};i2<dividendSize;i2++)
    {
       remainder[i2]=dividend[i2];
    }
    for(int i3{0};i3<bufferSize;i3++)
    {
       if(i3<quotientSize)
       {
           buffer[i3]=0;
           continue;
       }
        buffer[i3]=divisor[i3-quotientSize];
 
    }
    if(less (remainder,buffer,remainderSize,bufferSize))
    {
       divideBy10(buffer,bufferSize);
    }
    else
    {
       quotientSize++;
    }
    memset(quotient,0,quotientSize);
    for(int i6{quotientSize-1};i6>=0;i6--)
    {
       while(!less(remainder,buffer,remainderSize,bufferSize))
       {
          subtraction(remainder,buffer,remainderSize,bufferSize);
          quotient[i6]++;
          if(isZero(remainder,remainderSize))
          {
            return;
          }
       }
       divideBy10(buffer,bufferSize);
    }
}

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( int hugeInt[], int &size )
{
   if( size == 1 )
      hugeInt[ 0 ] = 0;
   else
   {
      for( int i = 1; i < size; i++ )
         hugeInt[ i - 1 ] = hugeInt[ i ];

      size--;
      hugeInt[ size ] = 0;
   }
}