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
   
    // Subtrahend >> Minuend
    if(hugeInt1.size< hugeInt2.size){

        return true;
    }
    // Subtrahend << Minuend
    if(hugeInt1.size> hugeInt2.size){

        return false;
    }
    // Size1== Size2
    for(int i= (hugeInt1.size- 1); i>= 0; i--){
        if(hugeInt1.integer[i]< hugeInt2.integer[i]){

            return true;
        }
        if(hugeInt1.integer[i]> hugeInt2.integer[i]){

            return false;
        }
    }
    return false;
}

// --hugeInt
void decrement( HugeInt hugeInt ){

    hugeInt.integer[0]--;
    // borrow
    for(int i= 0; i< hugeInt.size; i++){

        if(hugeInt.integer[i]< 0){

            hugeInt.integer[i+1]--;
            hugeInt.integer[i]+= 10;
        }
    }
    while(hugeInt.size> 0&& !hugeInt.integer[hugeInt.size- 1]){
        
        hugeInt.size--;
    }
}

// minuend -= subtrahend provided that minuend > subtrahend
void subtraction( HugeInt &minuend, HugeInt &subtrahend ){

    /* Minus & Borrow */
    for(int i= 0; i< minuend.size; i++){
        
        /* Minuend- Subtrahend */
        minuend.integer[i]-= subtrahend.integer[i];
        
        /* Borrow */
        if(minuend.integer[i]< 0){

            minuend.integer[i]+= 10;
            minuend.integer[(i+ 1)]--;
        }
    }

    /* Refresh Difference Size */
    while(minuend.size> 0&& !minuend.integer[minuend.size-1]){
        
        minuend.size--;
    }

}


// multiplicand *= multiplier
void multiplication( HugeInt &multiplicand, HugeInt &multiplier ){

    /* Multiple & Carry */
    HugeInt product;
    product.integer= new long long int[M2]();
    product.size= multiplicand.size+ multiplier.size;
    for(int ix= 0; ix< multiplicand.size; ix++){

        for(int iy= 0; iy< multiplier.size; iy++){
    
            product.integer[(ix+ iy)]+= (multiplicand.integer[ix]* multiplier.integer[iy]);     // Multiple
            product.integer[(ix+ iy+ 1)]+= (product.integer[(ix+ iy)]/ 10);             // Carry
            product.integer[(ix+ iy)]%= 10;
        }

    }

    /* Refresh Product Size */
    
    while(product.size> 0&& !product.integer[product.size- 1]){
        
        product.size--;
    }

    /* Reset Multiplicand */
    memset(multiplicand.integer, 0, product.size);
    /* Reset Multiplicand */
    // memset(multiplicand, 0, productSize);
    /* Return product 2 multiplicand */
    for(int i= 0; i< product.size; i++){
    
        multiplicand.integer[i]= product.integer[i];
    }
    /* Return productSize 2 multiplicandSize */
    multiplicand.size= product.size;
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
   
   /* Assign divendend 2 remainder */
    for(int i= 0; i< dividend.size; i++){
        
        remainder.integer[i]= dividend.integer[i];
    }
    remainder.size= dividend.size;

    quotient.size= dividend.size- divisor.size;
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
   
    if(isLess(remainder, buffer)){

        divideBy10(buffer);
    }
    else{
        
        quotient.size++;
    }
   
    memset(quotient.integer, 0, quotient.size);
    for(int i= quotient.size-1; i>= 0; i--){
        
        while(!isLess(remainder, buffer)){
            
            subtraction(remainder, buffer);
            quotient.integer[i]++;   
            if(isZero(remainder)){
            
            return;
            }
        }
    
        divideBy10(buffer);
    }
   
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