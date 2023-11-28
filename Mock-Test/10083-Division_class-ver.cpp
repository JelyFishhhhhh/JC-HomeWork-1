#include <iostream>
#include <cstring>
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

    /* Assign divendend 2 remainder */
    for(int i= 0; i< size; i++){
        
        remainder.integer[i]= integer[i];
    }
    remainder.size= size;

    quotient.size= size- divisor.size;
    HugeInt buffer;
    buffer.integer= new long long int[M2]();
    buffer.size= divisor.size+ quotient.size;

    for(int i= 0; i< buffer.size; i++){
        if(i< quotient.size){
            
            buffer.integer[i]= 0;
            continue;
        }
        
        buffer.integer[i]= divisor.integer[i- quotient.size];
    }
    
    if(remainder.isLess(buffer)){

        buffer.divideBy10();
    }
    else{
        
        quotient.size++;
    }
    
    memset(quotient.integer, 0, quotient.size);
    for(int i= quotient.size-1; i>= 0; i--){
        
        while(!remainder.isLess(buffer)){
            
            remainder.subtraction(buffer);
            quotient.integer[i]++;   
            if(remainder.isZero()){
            
                return;
            }
        }
        
        buffer.divideBy10();
    }
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

    /* Multiple & Carry */
    HugeInt product;
    product.size= size+ multiplier.size;
    product.integer= new long long int[M2]();

    for(int ix= 0; ix< size; ix++){

        for(int iy= 0; iy< multiplier.size; iy++){
    
            product.integer[(ix+ iy)]+= (integer[ix]* multiplier.integer[iy]);     // Multiple
            product.integer[(ix+ iy+ 1)]+= (product.integer[(ix+ iy)]/ 10);             // Carry
            product.integer[(ix+ iy)]%= 10;
        }

    }

    /* Refresh Product Size */
   
    while(product.size> 0&& !product.integer[product.size- 1]){
        
        product.size--;
    }
    /* Return product 2 multiplicand */
    for(int i= 0; i< product.size; i++){
    
        integer[i]= product.integer[i];
    }
    /* Return productSize 2 multiplicandSize */
    size= product.size;
}

// minuend -= subtrahend provided that minuend > subtrahend
void HugeInt::subtraction( HugeInt &subtrahend ){

    /* Minus & Borrow */
    for(int i= 0; i< size; i++){
        
        /* Minuend- Subtrahend */
        integer[i]-= subtrahend.integer[i];
        
        /* Borrow */
        if(integer[i]< 0){

            integer[i]+= 10;
            integer[(i+ 1)]--;
        }
    }

    /* Refresh Difference Size */
    while(size> 0&& !integer[size- 1]){
        
        size--;
    }
}

// --hugeInt
void HugeInt::decrement(){

    integer[0]--;
    // borrow
    for(int i= 0; i< size; i++){

        if(integer[i]< 0){

            integer[i+1]--;
            integer[i]+= 10;
        }
    }
    while(size> 0&& !integer[size- 1]){
        
        size--;
    }
}

// returns true if and only if hugeInt1 < hugeInt2
bool HugeInt::isLess( HugeInt &hugeInt1 ){

    // Subtrahend >> Minuend
    if(size< hugeInt1.size){

        return true;
    }
    // Subtrahend << Minuend
    if(size> hugeInt1.size){

        return false;
    }
    // Size1== Size2
    for(int i= (size- 1); i>= 0; i--){
        if(integer[i]< hugeInt1.integer[i]){

            return true;
        }
        if(integer[i]> hugeInt1.integer[i]){

            return false;
        }
    }
    return false;
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