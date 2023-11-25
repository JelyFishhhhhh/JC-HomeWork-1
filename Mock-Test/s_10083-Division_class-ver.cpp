#include <iostream>
using namespace std;
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define M 1000
#define M2 2000

const int twoHundred = 200;
const int hundred = 100;

class HugeInt{

    public:
        
        // constructor-N-destructor
        HugeInt();
        ~HugeInt();

        // variable
        long long int *integer = nullptr;
        int size;

        // function
        void division( HugeInt &divisor, HugeInt &quotient, HugeInt &remainder);
        void divideBy10();
        void multiplication( HugeInt &multiplier );
        void subtraction( HugeInt &subtrahend );
        void decrement();
        bool isLess( HugeInt &hugeInt1 );
        bool isZero();
};

HugeInt::HugeInt(){

    size= 1;
}

HugeInt::~HugeInt(){

    delete[] integer;
}

// quotient = dividend / divisor; remainder = dividend % divisor
void HugeInt::division( HugeInt &divisor, HugeInt &quotient, HugeInt &remainder){

    
}

// hugeInt /= 10, or equivalently, shifts right by one position
void HugeInt::divideBy10(){

    if( size == 1 ){

        integer[ 0 ] = 0;
    }
    else{
        for( int i = 1; i < size; i++ ){

            integer[ i - 1 ] = integer[ i ];
        }

        integer[ --size ] = 0;
    }
}

// multiplicand *= multiplier
void HugeInt::multiplication( HugeInt &multiplier ){

    
}

// minuend -= subtrahend provided that minuend > subtrahend
void HugeInt::subtraction( HugeInt &subtrahend ){

    
}

// --hugeInt
void HugeInt::decrement(){

    
}

// returns true if and only if hugeInt1 < hugeInt2
bool HugeInt::isLess( HugeInt &hugeInt1 ){

    
}

// returns true if and only if the specified huge integer is zero
bool HugeInt::isZero(){

    for( int i = 0; i < size; i++ ){

        if( integer[ i ]){

            return false;
        }
    }
    return true;
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
        base.size = 0;
        for( int i = t; i > 0; i /= 10 ){

            base.integer[ base.size++ ] = i % 10;
        }

        // dividend = pow( t, a )
        dividend.integer[ 0 ] = 1;
        for( int i = 0; i < a; ++i ){
            dividend.multiplication( base );
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

                divisor.multiplication( base );
                if( divisor.size > hundred - base.size ){

                    break;
                }
            }

            if( divisor.size > hundred - base.size ){

                cout << "is not an integer with less than 100 digits.\n";
            }
            else{
                
                dividend.decrement(); // --dividend
                divisor.decrement();   // --divisor

                dividend.division( divisor, quotient, remainder);

                // quotient is an integer with isNegative than hundred digits
                if( quotient.size < hundred && remainder.isZero() ){

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