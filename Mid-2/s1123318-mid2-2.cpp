// Polynomial division provided that the quotient and remainder have integer coefficients

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;


class Polynomial
{
public:

   void readPolynomial( ifstream &inFile );

   // outputs the specified polynomial
   void output();

   // returns true if and only if the specified polynomial is zero polynomial
   bool isZero();

   // returns true if and only if polynomial1 == polynomial2
   bool equal( Polynomial polynomial );

   // polynomial1 = -polynomial2
   void minus( Polynomial polynomial );

   // addend += adder
   void addition( Polynomial adder );

   // minuend -= subtrahend
   void subtraction( Polynomial subtrahend );

   // product = multiplicand * multiplier
   void multiplication( Polynomial multiplicand, Polynomial multiplier );

   // quotient = dividend / divisor
   // provided that dividend.degree >= divisor.degree
   void computeQuotient( Polynomial dividend, Polynomial divisor );

   // remainder = dividend % divisor
   // provided that dividend.degree >= divisor.degree
   void computeRemainder( Polynomial dividend, Polynomial divisor );

   int degree = 0;
   int *terms = nullptr;
};


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
      dividend.readPolynomial( inFile );

      // read divisor from the file Polynomials.dat
      divisor.readPolynomial( inFile );

      cout << " dividend: ";   dividend.output();
      cout << " divisor : ";   divisor.output();

      // quotient = dividend / divisor; remainder = dividend % divisor
      // thus, dividend == divisor * quotient + remainder
      quotient.computeQuotient( dividend, divisor );

      remainder.computeRemainder( dividend, divisor );

      cout << " quotient: ";   quotient.output();
      cout << "remainder: ";   remainder.output();
      cout << endl;

      if( dividend.degree >= divisor.degree && !quotient.isZero() &&
          !dividend.equal( remainder ) )
          numErrors--;

      // buffer = divisor * quotient
      buffer.multiplication( divisor, quotient );

      // buffer = buffer + remainder = divisor * quotient + remainder
      buffer.addition( remainder );

      // if buffer != dividend, an error occurred!
      if( buffer.equal( dividend ) )
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

void Polynomial::readPolynomial( ifstream &inFile )
{
   const int arraySize = 20;
   int buffer[ arraySize ] = {};
   inFile.read( reinterpret_cast< char * >( buffer ), 80 );

   degree = arraySize - 1;
   while( degree > 0 && buffer[ degree ] == 0 )
      degree--;

   terms = new int[ degree + 1 ]();
   for( int i = 0; i <= degree; i++ )
      terms[ i ] = buffer[ i ];
}

// outputs the specified polynomial
void Polynomial::output()
{
   if( isZero() ) // zero polynomial
      cout << 0;
   else
   {
      if( degree == 0 ) // constant polynomial
      {
         if( terms[ 0 ] < 0 )
            cout << "-" << -terms[ 0 ];
         else if( terms[ 0 ] > 0 )
            cout << terms[ 0 ];
      }
      else
      {
         if( degree == 1 ) // polynomial of degree 1
         {
            if( terms[ 1 ] < 0 )
               cout << "-" << -terms[ 1 ] << "x";
            else if( terms[ 1 ] > 0 )
               cout << terms[ 1 ] << "x";
         }
         else // polynomial of degree at least 2
         {
            // display the leading term
            if( terms[ degree ] < 0 )
               cout << "-" << -terms[ degree ] << "x^" << degree;
            else if( terms[ degree ] > 0 )
               cout << terms[ degree ] << "x^" << degree;

            // display all other terms
            for( int i = degree - 1; i > 1; i-- )
               if( terms[ i ] < 0 )
                  cout << " - " << -terms[ i ] << "x^" << i;
               else if( terms[ i ] > 0 )
                  cout << " + " << terms[ i ] << "x^" << i;

            // display the term of degree 1
            if( terms[ 1 ] < 0 )
               cout << " - " << -terms[ 1 ] << "x";
            else if( terms[ 1 ] > 0 )
               cout << " + " << terms[ 1 ] << "x";
         }

         // display the constant term
         if( terms[ 0 ] < 0 )
            cout << " - " << -terms[ 0 ];
         else if( terms[ 0 ] > 0 )
            cout << " + " << terms[ 0 ];
      }
   }

   cout << endl;
}

// returns true if and only if the specified polynomial is zero polynomial
bool Polynomial::isZero()
{
   if( degree == 0 && terms[ 0 ] == 0 )  // leading term is 0
      return true;
   return false;
}

// returns true if and only if polynomial1 == polynomial2
bool Polynomial::equal( Polynomial polynomial )
{
   if( degree != polynomial.degree )
      return false;

   for( int i = 0; i <= degree; i++ )
      if( terms[ i ] != polynomial.terms[ i ] )
         return false;

   return true;
}

// polynomial1 = -polynomial2
void Polynomial::minus( Polynomial polynomial )
{
   degree = polynomial.degree;
   terms = new int[ degree + 1 ]();
   for( int i = 0; i <= degree; i++ )
      terms[ i ] = -polynomial.terms[ i ];
}

// addend += adder
void Polynomial::addition( Polynomial adder )
{

    this->degree = (this->degree > adder.degree ? this->degree : adder.degree);
    for (int i = 0; i <= this->degree; i++) {

        // addition
        this->terms[i] += (i <= adder.degree ? adder.terms[i] : 0);
    }

    while (this->degree > 0 && !this->terms[this->degree]) {

        this->degree--;
    }




   if( degree != 0 && terms[ degree ] == 0 )
      cout << "Leading coefficient of addend cannot be zero!\n";
}

// minuend -= subtrahend
void Polynomial::subtraction( Polynomial subtrahend )
{
   Polynomial buffer;

   // buffer = -subtrahend
   buffer.minus( subtrahend );

   // minuend = minuend + buffer = minuend - subtrahend
   addition( buffer );

   delete[] buffer.terms;

   if( degree != 0 && terms[ degree ] == 0 )
      cout << "Leading coefficient of minuend cannot be zero!\n";
}

// product = multiplicand * multiplier
void Polynomial::multiplication( Polynomial multiplicand, Polynomial multiplier )
{
    this->degree = multiplicand.degree + multiplier.degree;
    this->terms = new int[this->degree + 1]();

    // multiplicand
    for (int ix = 0; ix <= multiplicand.degree; ix++) {

        for (int iy = 0; iy <= multiplier.degree; iy++) {

            this->terms[ix + iy] = multiplicand.terms[ix] * multiplier.terms[iy];
        }
    }

    while (!this->terms[this->degree] && this->degree > 0) {

        this->degree--;
    }

   if( degree != 0 && terms[ degree ] == 0 )
      cout << "Leading coefficient of product cannot be zero!\n";
}

// quotient = dividend / divisor
// provided that dividend.degree >= divisor.degree
void Polynomial::computeQuotient( Polynomial dividend, Polynomial divisor )
{

    Polynomial remainder;
    remainder.degree = dividend.degree;
    remainder.terms = new int[remainder.degree + 1]();
    // init
    this->degree = dividend.degree - divisor.degree;
    this->terms = new int[this->degree + 1]();
    remainder.degree = dividend.degree;
    remainder.terms = new int[remainder.degree + 1]();

    // dividend-> remainder
    for (int i = 0; i <= remainder.degree; i++) {

        remainder.terms[i] = dividend.terms[i];
    }

    Polynomial monomial;
    Polynomial buffer;
    monomial.degree = this->degree;
    monomial.terms = new int[monomial.degree + 2]();
    buffer.degree = divisor.degree + this->degree;
    buffer.terms = new int[buffer.degree + 1]();

    for (int i = this->degree; i >= 0; i--) {

        this->terms[i] = remainder.terms[remainder.degree] / divisor.terms[divisor.degree];
        monomial.terms[i] = this->terms[i];
        monomial.degree = i;
        buffer.degree = divisor.degree + monomial.degree;
        buffer.multiplication(divisor, monomial);
        remainder.subtraction(buffer);
        monomial.terms[i] = 0;
    }

    while (!this->terms[this->degree] && this->degree > 0) {

        this->degree--;
    }
    while (!remainder.terms[remainder.degree] && remainder.degree > 0) {

        remainder.degree--;
    }

   if( degree != 0 && terms[ degree ] == 0 )
      cout << "Leading coefficient of quotient cannot be zero!\n";

   if( remainder.degree != 0 && remainder.terms[ remainder.degree ] == 0 )
      cout << "Leading coefficient of remainder cannot be zero!\n";

   delete[] remainder.terms;
}

// remainder = dividend % divisor
// provided that dividend.degree >= divisor.degree
void Polynomial::computeRemainder( Polynomial dividend, Polynomial divisor )
{

    Polynomial quotient;
    quotient.degree = dividend.degree - divisor.degree;
    quotient.terms = new int[quotient.degree + 1]();
    // init
    quotient.degree = dividend.degree - divisor.degree;
    quotient.terms = new int[quotient.degree + 1]();
    this->degree = dividend.degree;
    this->terms = new int[this->degree + 1]();

    // dividend-> remainder
    for (int i = 0; i <= this->degree; i++) {

        this->terms[i] = dividend.terms[i];
    }

    Polynomial monomial;
    Polynomial buffer;
    monomial.degree = quotient.degree;
    monomial.terms = new int[monomial.degree + 2]();
    buffer.degree = divisor.degree + quotient.degree;
    buffer.terms = new int[buffer.degree + 1]();

    for (int i = quotient.degree; i >= 0; i--) {

        quotient.terms[i] = this->terms[this->degree] / divisor.terms[divisor.degree];
        monomial.terms[i] = quotient.terms[i];
        monomial.degree = i;
        buffer.degree = divisor.degree + monomial.degree;
        buffer.multiplication(divisor, monomial);
        subtraction(buffer);
        monomial.terms[i] = 0;
    }

    while (!quotient.terms[quotient.degree] && quotient.degree > 0) {

        quotient.degree--;
    }
    while (!this->terms[this->degree] && this->degree > 0) {

        this->degree--;
    }




   if( quotient.degree != 0 && quotient.terms[ quotient.degree ] == 0 )
      cout << "Leading coefficient of quotient cannot be zero!\n";

   if( degree != 0 && terms[ degree ] == 0 )
      cout << "Leading coefficient of remainder cannot be zero!\n";

   delete[] quotient.terms;
}