// Polynomial division provided that the quotient and remainder have integer coefficients

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;


struct Polynomial
{
   int degree = 0;
   int *terms = nullptr;
};

void readPolynomial( ifstream &inFile, Polynomial &polynomial );

// outputs the specified polynomial
void output( Polynomial polynomial );

// returns true if and only if the specified polynomial is zero polynomial
bool isZero( Polynomial polynomial );

// returns true if and only if polynomial1 == polynomial2
bool equal( Polynomial polynomial1, Polynomial polynomial2 );

// polynomial1 = -polynomial2
void minus( Polynomial &polynomial1, Polynomial polynomial2 );

// addend += adder
void addition( Polynomial &addend, Polynomial adder );

// minuend -= subtrahend
void subtraction( Polynomial &minuend, Polynomial subtrahend );

// product = multiplicand * multiplier
void multiplication( Polynomial multiplicand, Polynomial multiplier, Polynomial &product );

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividend.degree >= divisor.degree
void division( Polynomial dividend, Polynomial divisor,
              Polynomial &quotient, Polynomial &remainder );

int main()
{
   ifstream inFile( "Polynomials.dat", ios::in | ios::binary );

   if( !inFile )
   {
      cout << "File could not be opened\n";
      system( "pause" );
      exit( 1 );
   }

   const int numTestCases = 200; // the number of test cases
   int numErrors = 2 * numTestCases;

   Polynomial dividend;
   Polynomial divisor;
   Polynomial quotient;
   Polynomial remainder;
   Polynomial buffer;

   for( int i = 0; i < numTestCases; i++ )
   {
      // read dividend from the file Polynomials.dat
      readPolynomial( inFile, dividend );

      // read divisor from the file Polynomials.dat
      readPolynomial( inFile, divisor );

      cout << " dividend: ";   output( dividend );
      cout << " divisor : ";   output( divisor );

      // quotient = dividend / divisor; remainder = dividend % divisor
      // thus, dividend == divisor * quotient + remainder
      division( dividend, divisor, quotient, remainder );

      cout << " quotient: ";   output( quotient );
      cout << "remainder: ";   output( remainder );
      cout << endl;

      if( dividend.degree >= divisor.degree && !isZero( quotient ) &&
          !equal( dividend, remainder ) )
          numErrors--;

      // buffer = divisor * quotient
      multiplication( divisor, quotient, buffer );

      // buffer = buffer + remainder = divisor * quotient + remainder
      addition( buffer, remainder );

      // if buffer != dividend, an error occurred!
      if( equal( buffer, dividend ) )
         numErrors--;

      delete[] dividend.terms;
      delete[] divisor.terms;
      delete[] quotient.terms;
      delete[] remainder.terms;
      delete[] buffer.terms;
   }

   inFile.close();

   cout << "There are " << numErrors << " errors!\n\n";

   system( "pause" );
}

void readPolynomial( ifstream &inFile, Polynomial &polynomial )
{
   const int arraySize = 20;
   int buffer[ arraySize ] = {};
   inFile.read( reinterpret_cast< char * >( buffer ), 80 );

   polynomial.degree = arraySize - 1;
   while( polynomial.degree > 0 && buffer[ polynomial.degree ] == 0 )
      polynomial.degree--;

   polynomial.terms = new int[ polynomial.degree + 1 ]();
   for( int i = 0; i <= polynomial.degree; i++ )
      polynomial.terms[ i ] = buffer[ i ];
}


// outputs the specified polynomial
void output( Polynomial polynomial )
{
   if( isZero( polynomial ) ) // zero polynomial
      cout << 0;
   else
   {
      if( polynomial.degree == 0 ) // constant polynomial
      {
         if( polynomial.terms[ 0 ] < 0 )
            cout << "-" << -polynomial.terms[ 0 ];
         else if( polynomial.terms[ 0 ] > 0 )
            cout << polynomial.terms[ 0 ];
      }
      else
      {
         if( polynomial.degree == 1 ) // polynomial of degree 1
         {
            if( polynomial.terms[ 1 ] < 0 )
               cout << "-" << -polynomial.terms[ 1 ] << "x";
            else if( polynomial.terms[ 1 ] > 0 )
               cout << polynomial.terms[ 1 ] << "x";
         }
         else // polynomial of degree at least 2
         {
            // display the leading term
            if( polynomial.terms[ polynomial.degree ] < 0 )
               cout << "-" << -polynomial.terms[ polynomial.degree ] << "x^" << polynomial.degree;
            else if( polynomial.terms[ polynomial.degree ] > 0 )
               cout << polynomial.terms[ polynomial.degree ] << "x^" << polynomial.degree;

            // display all other terms
            for( int i = polynomial.degree - 1; i > 1; i-- )
               if( polynomial.terms[ i ] < 0 )
                  cout << " - " << -polynomial.terms[ i ] << "x^" << i;
               else if( polynomial.terms[ i ] > 0 )
                  cout << " + " << polynomial.terms[ i ] << "x^" << i;

            // display the term of degree 1
            if( polynomial.terms[ 1 ] < 0 )
               cout << " - " << -polynomial.terms[ 1 ] << "x";
            else if( polynomial.terms[ 1 ] > 0 )
               cout << " + " << polynomial.terms[ 1 ] << "x";
         }

         // display the constant term
         if( polynomial.terms[ 0 ] < 0 )
            cout << " - " << -polynomial.terms[ 0 ];
         else if( polynomial.terms[ 0 ] > 0 )
            cout << " + " << polynomial.terms[ 0 ];
      }
   }

   cout << endl;
}

// returns true if and only if the specified polynomial is zero polynomial
bool isZero( Polynomial polynomial )
{
   if( polynomial.degree == 0 && polynomial.terms[ 0 ] == 0 )  // leading term is 0
      return true;
   return false;
}

// returns true if and only if polynomial1 == polynomial2
bool equal( Polynomial polynomial1, Polynomial polynomial2 )
{
   if( polynomial1.degree != polynomial2.degree )
      return false;

   for( int i = 0; i <= polynomial1.degree; i++ )
      if( polynomial1.terms[ i ] != polynomial2.terms[ i ] )
         return false;

   return true;
}

// polynomial1 = -polynomial2
void minus( Polynomial &polynomial1, Polynomial polynomial2 )
{
   polynomial1.degree = polynomial2.degree;
   polynomial1.terms = new int[ polynomial1.degree + 1 ]();
   for( int i = 0; i <= polynomial1.degree; i++ )
      polynomial1.terms[ i ] = -polynomial2.terms[ i ];
}

// addend += adder
void addition( Polynomial &addend, Polynomial adder )
{
    if (addend.degree > adder.degree) {
        for (int i = 0; i <= addend.degree; i++)//modify
            addend.terms[i] += (i <= adder.degree ? adder.terms[i] : 0);//modify
    }
    else if (addend.degree < adder.degree) {
        addend.degree = adder.degree;//add
        for (int i = 0; i <= adder.degree; i++) {//modify
            addend.terms[i] += (i <= adder.degree ? adder.terms[i] : 0);//modify
        }
    }
    else {
        for (int i = 0; i <= addend.degree; i++) {//modify
            addend.terms[i] += (i <= adder.degree ? adder.terms[i] : 0);//modify
        }
    }
    
    

    while (addend.degree > 0 && addend.terms[addend.degree] == 0) {
        addend.degree--;
    }

   if( addend.degree != 0 && addend.terms[ addend.degree ] == 0 )
      cout << "Leading coefficient of addend cannot be zero!\n";
}

// minuend -= subtrahend
void subtraction( Polynomial &minuend, Polynomial subtrahend )
{
   Polynomial buffer;

   // buffer = -subtrahend
   minus( buffer, subtrahend );

   // minuend = minuend + buffer = minuend - subtrahend
   addition( minuend, buffer );

   delete[] buffer.terms;

   if( minuend.degree != 0 && minuend.terms[ minuend.degree ] == 0 )
      cout << "Leading coefficient of minuend cannot be zero!\n";
}

// product = multiplicand * multiplier
void multiplication( Polynomial multiplicand, Polynomial multiplier, Polynomial &product )
{
    product.degree = multiplicand.degree + multiplier.degree;
    product.terms = new int[product.degree + 1]();//added
    for (int ix = 0; ix <= multiplicand.degree; ix++) {
        for (int iy = 0; iy <= multiplier.degree; iy++) {
            product.terms[ix + iy] += multiplicand.terms[ix] * multiplier.terms[iy];
        }
    }
    while (product.degree > 0 && product.terms[product.degree] == 0) {
        product.degree--;
    }

   if( product.degree != 0 && product.terms[ product.degree ] == 0 )
      cout << "Leading coefficient of product cannot be zero!\n";
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividend.degree >= divisor.degree
void division( Polynomial dividend, Polynomial divisor, Polynomial &quotient, Polynomial &remainder )
{
    remainder.degree = dividend.degree;//add
    quotient.degree = dividend.degree - divisor.degree;//add
    remainder.terms = new int[dividend.degree + 1]();//add
    quotient.terms = new int[quotient.degree + 1]();//add

    //add start
    for (int i = 0; i <= dividend.degree; i++) {
        remainder.terms[i] = dividend.terms[i];
    }//add end

    Polynomial buffer;
    Polynomial monomial;
    buffer.degree = remainder.degree;
    monomial.degree = remainder.degree - divisor.degree;
    buffer.terms = new int [buffer.degree + 1]();//modify
    monomial.terms = new int [monomial.degree + 1]();//modify
    if (dividend.degree >= divisor.degree) {
        for (int ix = dividend.degree; ix >= divisor.degree; ix--) {//modify
            quotient.terms[ix - divisor.degree] = remainder.terms[ix] / divisor.terms[divisor.degree];
            monomial.terms[ix - divisor.degree] = quotient.terms[ix - divisor.degree];
            monomial.degree = ix - divisor.degree; //add
            buffer.degree = divisor.degree + monomial.degree; //add
            multiplication(monomial, divisor, buffer);
            subtraction(remainder, buffer);

            for (int m = 0; m <= monomial.degree; m++) { //add start
                monomial.terms[m] = 0;
            }//add end
        }
    }
    delete[] buffer.terms;
    delete[] monomial.terms;
 /*
    while (quotient.degree > 0 && quotient.terms[quotient.degree] == 0 ) {
        quotient.degree--;
    }

    while (remainder.degree > 0 && remainder.terms[quotient.degree] == 0) {
        remainder.degree--;
    }    delet
*/
   if( quotient.degree != 0 && quotient.terms[ quotient.degree ] == 0 )
      cout << "Leading coefficient of quotient cannot be zero!\n";

   if( remainder.degree != 0 && remainder.terms[ remainder.degree ] == 0 )
      cout << "Leading coefficient of remainder cannot be zero!\n";
}