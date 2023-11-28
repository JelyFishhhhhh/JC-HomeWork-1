#include <iostream>
#include <cstring>
using namespace std;
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define M 1000
#define M2 2000

const int twoHundred = 200;
const int hundred = 100;

struct HugeInt
{
    int size= 1;
    long long int *integer = nullptr;
};

// returns true if and only if the specified huge integer is zero
bool isZero( HugeInt &hugeInt ){
   
   for( int i = 0; i < hugeInt.size; i++ ){

      if( hugeInt.integer[ i ]){

         return false;
      }
   }
   return true;
}

// returns true if and only if hugeInt1 < hugeInt2
bool isLess( HugeInt &hugeInt1, HugeInt &hugeInt2 ){
   
    
}

// --hugeInt
void decrement( HugeInt hugeInt ){

    
}

// minuend -= subtrahend provided that minuend > subtrahend
void subtraction( HugeInt &minuend, HugeInt &subtrahend ){

    
}


// multiplicand *= multiplier
void multiplication( HugeInt &multiplicand, HugeInt &multiplier ){

    
}

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( HugeInt &hugeInt ){
    if( hugeInt.size == 1 ){

        hugeInt.integer[ 0 ] = 0;
    }
    else{
        
        for( int i = 1; i < hugeInt.size; i++ ){

            hugeInt.integer[ i - 1 ] = hugeInt.integer[ i ];
        }

        hugeInt.integer[ --hugeInt.size ] = 0;
    }
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division( HugeInt &dividend, HugeInt &divisor, HugeInt &quotient, HugeInt &remainder){
   
   
}


int main(){

    int t, a, b;
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
        HugeInt dividend;
        dividend.integer= new long long int[M2]();
        HugeInt divisor;
        divisor.integer= new long long int[M]();
        HugeInt quotient;
        quotient.integer= new long long int[M]();
        HugeInt remainder;
        remainder.integer= new long long int[M]();

        // put all digits of t into base
        HugeInt base;
        base.integer= new long long int[M2]();
        base.size= 0;
        for( int i = t; i > 0; i /= 10 ){

            base.integer[ base.size++ ] = i % 10;
        }

        // dividend = pow( t, a )
        dividend.integer[ 0 ] = 1;
        for( int i = 0; i < a; ++i ){
            multiplication( dividend, base );
            if( dividend.size > twoHundred - base.size ){

            break;
            }
        }

        if( dividend.size > twoHundred - base.size ){

            cout << "is not an integer with less than 100 digits.\n";
        }
        else{
            // divisor = pow( t, b )
            divisor.integer[ 0 ] = 1;
            for( int i = 0; i < b; ++i ){

            multiplication( divisor, base );
            if( divisor.size > hundred - base.size ){

                break;
            }
            }

            if( divisor.size > hundred - base.size ){

            cout << "is not an integer with less than 100 digits.\n";
            }
            else{
            decrement( dividend ); // --dividend
            decrement( divisor );   // --divisor

            division( dividend, divisor, quotient, remainder );

            // quotient is an integer with isNegative than hundred digits
            if( quotient.size < hundred && isZero( remainder ) ){

                for( int i = quotient.size - 1; i >= 0; i-- ){

                    cout << quotient.integer[ i ];
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
