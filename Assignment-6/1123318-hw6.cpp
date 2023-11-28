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
        if( numDigits < 10 ){

            cout << sqrt( atoi( str ) ) << endl;// < 10正常做除法運算
        }
        else{

            int *digits = new int[ numDigits + 3 ]();
            for( size_t j = 0; j < numDigits; ++j )
            digits[ j ] = static_cast< int >( str[ numDigits - 1 - j ] ) - '0';

            size_t last = ( numDigits - 1 ) / 4;
            size_t hugeIntSize = last + 1;
            long long int *hugeInt = new long long int[ hugeIntSize ]();
            for( size_t j = 0; j <= last; j++ )
            hugeInt[ j ] =  digits[ 4 * j ] +
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
    // init square(tmp)
    int squareSize = hugeIntSize + 1;
    long long int *square = new long long int[ squareSize ]();
    
    // finding sqrt by binary search method
    for (int i = sqrtSize - 1; i >= 0; i--) {
        // init low/ high
        long long int low = 0; 
        long long int high = 9999;
        long long int mid;
        while (low <= high) {

            // set mid 
            mid = (low + high) / 2;
            squareRoot[i] = mid;

            // square= (sqrt)^2
            compSquare(squareRoot, square, sqrtSize, squareSize); //mid^2

            // square== hugeInt: set high as mid
            if (equal(square, hugeInt, squareSize, hugeIntSize)){
                high = mid;
                break;
            }

            // square< hugeInt: range switch right; update lower bound
            else if(less(square, hugeInt, squareSize, hugeIntSize)){
                
                low = mid + 1;
            }
            
            // square> hugeInt: range switch left; update upper bound
            else {
                
                high = mid - 1;
            }
        }

        // set squareRoot as high
        squareRoot[i] = high;
    }

    // clear the dynamic array
    delete[] square;
}

// put the square of hugeInt into the array square
void compSquare( long long int *hugeInt, long long int *square, int hugeIntSize, int &squareSize ){

    // assign square
    squareSize = hugeIntSize + hugeIntSize;
    memset(square, 0, squareSize * sizeof(long long int));

    // square= (hugeInt)^2
    for (int ix = 0; ix < hugeIntSize; ix++) {
        for (int iy = 0; iy < hugeIntSize; iy++) {
            square[ix + iy] += hugeInt[ix] * hugeInt[iy];
        }
    }
    
    // carry
    for (int ix = 0; ix < squareSize; ix++) {
        if (square[ix] > 9999) {
            square[ix + 1] += square[ix] / 10000;
            square[ix] %= 10000;//每個index放四個數字
        }
    }
    
    // update pratical squareSize
    while(squareSize > 1 && square[squareSize - 1] == 0) {
    
        squareSize--;
    }
}

// if hugeInt1 == hugeInt2, return true; otherwise, return false
bool equal( long long int *hugeInt1, long long int *hugeInt2, int size1, int size2 ){
   
    if( size1 != size2 ){

            return false;
    }

    return recursiveEqual( hugeInt1, hugeInt2, size1 - 1 );
}

bool recursiveEqual( long long int *hugeInt1, long long int *hugeInt2, int last ){

    if (last < 0) {
    
        return true;
    }
    else if (hugeInt1[last] == hugeInt2[last]) {

        return recursiveEqual(hugeInt1, hugeInt2, last - 1);
    }
    else {

        return false;
    }
}

// if hugeInt1 < hugeInt2, retuen true; otherwise, return false
bool less( long long int *hugeInt1, long long int *hugeInt2, int size1, int size2 ){

    if( size1 < size2 ){

        return true;
    }

    if( size1 > size2 ){

        return false;
    }

    return recursiveLess( hugeInt1, hugeInt2, size1 - 1 );
}

bool recursiveLess( long long int *hugeInt1, long long int *hugeInt2, int last ){

    if (last < 0) {
    
        return false;
    }
    if (hugeInt1[last] < hugeInt2[last]) {
    
        return true;
    }
    else if (hugeInt1[last] > hugeInt2[last]) {
    
        return false;
    }
    else {
    
        return recursiveLess(hugeInt1, hugeInt2, last - 1);
    }

}
