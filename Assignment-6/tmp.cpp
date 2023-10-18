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

// put the square root of hugeInt into the array squareRoot
void compSquareRoot( long long int *hugeInt, long long int *squareRoot, int hugeIntSize, int sqrtSize );

// put the square of hugeInt into the array square
void compSquare( long long int *hugeInt, long long int *square, int hugeIntSize, int &squareSize );

// if hugeInt1 == hugeInt2, return true; otherwise, return false
bool equal( long long int *hugeInt1, long long int *hugeInt2, int size1, int size2 );

bool recursiveEqual( long long int *hugeInt1, long long int *hugeInt2, int last );

// if hugeInt1 < hugeInt2, return true; otherwise, return false
bool less( long long int *hugeInt1, long long int *hugeInt2, int size1, int size2 );

bool recursiveLess( long long int *hugeInt1, long long int *hugeInt2, int last );

const int arraySize = 1010;

int main()
{
   int testCase;
   cin >> testCase;
   for( int i = 1; i <= testCase; i++ )
   {
      char str[ arraySize ] = {};
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
         size_t hugeIntSize = last + 1;
         long long int *hugeInt = new long long int[ hugeIntSize ]();
         for( size_t j = 0; j <= last; j++ )
            hugeInt[ j ] = digits[ 4 * j ] +
                          digits[ 4 * j + 1 ] * 10 +
                          digits[ 4 * j + 2 ] * 100 +
                          digits[ 4 * j + 3 ] * 1000;

         size_t sqrtSize = ( hugeIntSize + 1 ) / 2; // the number of digits of squareRoot is sqrtSize
         long long int *squareRoot = new long long int[ sqrtSize ](); // the square root of hugeInt

         // put the square root of hugeInt into the array squareRoot
         compSquareRoot( hugeInt, squareRoot, hugeIntSize, sqrtSize );

         cout << squareRoot[ sqrtSize - 1 ];
         for( int j = sqrtSize - 2; j >= 0; j-- )
            cout << setw( 4 ) << setfill( '0' ) << squareRoot[ j ];
         cout << endl;

         delete[] squareRoot;
         delete[] hugeInt;
         delete[] digits;
      }

      if( i < testCase )
         cout << endl;
   }

   system( "pause" );
}

// put the square root of hugeInt into the array squareRoot
void compSquareRoot( long long int *hugeInt, long long int *squareRoot, int hugeIntSize, int sqrtSize )
{
   int squareSize = hugeIntSize;
   
    for (int i = sqrtSize - 1; i >= 0;i--)
    {
        long long int low = 0;
        long long int high = 9999;
        while (low <= high)
        {
            long long int *square = new long long int[ squareSize ]();
            squareRoot[i] = (low + high) / 2;
            compSquare(squareRoot, square, sqrtSize,squareSize);
            if (equal(square, hugeInt, squareSize, hugeIntSize))
            {
                delete[] square;
                return;
            }
            if (less(square, hugeInt, squareSize, hugeIntSize))
            {
                low = squareRoot[i] + 1;
            }
            else
            {
                high = squareRoot[i] - 1;
            }
            delete[] square;
        }
    }
   

}

// put the square of hugeInt into the array square
void compSquare( long long int *hugeInt, long long int *square, int hugeIntSize, int &squareSize )
{
    for (int x = 0; x < hugeIntSize; x++)
    {
        for (int y = 0; y < hugeIntSize; y++)
        {
            square[x + y] += hugeInt[x] * hugeInt[y];
            if (square[x + y] > 9999)
            {
                square[x + y + 1] += square[x + y] / 10000;
                square[x + y] = square[x + y] % 10000;
            }
        }
    }
}

// if hugeInt1 == hugeInt2, return true; otherwise, return false
bool equal( long long int *hugeInt1, long long int *hugeInt2, int size1, int size2 )
{
   if( size1 != size2 )
      return false;

   return recursiveEqual( hugeInt1, hugeInt2, size1 - 1 );
}

bool recursiveEqual( long long int *hugeInt1, long long int *hugeInt2, int last )
{
    if (last == 0)
    {
        return true;
    }
    if (hugeInt1[last] == hugeInt2[last])
    {
        return recursiveEqual(hugeInt1, hugeInt2, last - 1);
    }
    else
    {
        return false;
    }

}

// if hugeInt1 < hugeInt2, retuen true; otherwise, return false
bool less( long long int *hugeInt1, long long int *hugeInt2, int size1, int size2 )
{
   if( size1 < size2 )
      return true;

   if( size1 > size2 )
      return false;

   return recursiveLess( hugeInt1, hugeInt2, size1 - 1 );
}

bool recursiveLess( long long int *hugeInt1, long long int *hugeInt2, int last )
{
    if (last == 0)
    {
        return false;
    }
    if (hugeInt1[last] < hugeInt2[last])
    {
        return true;
    }
    else if (hugeInt1[last] > hugeInt2[last])
    {
        return false;
    }
    else
    {
        return recursiveLess(hugeInt1, hugeInt2, last - 1);
    }
}