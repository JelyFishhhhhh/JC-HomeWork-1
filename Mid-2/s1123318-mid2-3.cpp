// vector< int > division provided that the quotient and remainder have integer coefficients

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

#include <vector>
using std::vector;

void readPolynomial( ifstream &inFile, vector< int > &polynomial );

// outputs the specified polynomial
void output( vector< int > polynomial );

// returns true if and only if the specified polynomial is zero polynomial
bool isZero( vector< int > polynomial );

// returns true if and only if polynomial1 == polynomial2
bool equal( vector< int > polynomial1, vector< int > polynomial2 );

// polynomial1 = -polynomial2
void minus( vector< int > &polynomial1, vector< int > polynomial2 );

// addend += adder
void addition( vector< int > &addend, vector< int > adder );

// minuend -= subtrahend
void subtraction( vector< int > &minuend, vector< int > subtrahend );

// product = multiplicand * multiplier
void multiplication( vector< int > multiplicand, vector< int > multiplier, vector< int > &product );

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividend.size() >= divisor.size()
void division( vector< int > dividend, vector< int > divisor,
              vector< int > &quotient, vector< int > &remainder );

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

   vector< int > dividend;
   vector< int > divisor;
   vector< int > quotient;
   vector< int > remainder;
   vector< int > buffer;

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

      if( dividend.size() >= divisor.size() && !isZero( quotient ) &&
          !equal( dividend, remainder ) )
          numErrors--;

      multiplication( divisor, quotient, buffer ); // buffer = divisor * quotient

      // buffer = buffer + remainder = divisor * quotient + remainder
      addition( buffer, remainder );

      // if buffer != dividend, an error occurred!
      if( equal( buffer, dividend ) )
         numErrors--;

      dividend.clear();
      divisor.clear();
      quotient.clear();
      remainder.clear();
      buffer.clear();
   }

   inFile.close();

   cout << "There are " << numErrors << " errors!\n\n";

   system( "pause" );
}

void readPolynomial( ifstream &inFile, vector< int > &polynomial )
{
   const int arraySize = 20;
   int buffer[ arraySize ] = {};
   inFile.read( reinterpret_cast< char * >( buffer ), 80 );

   int degree = arraySize - 1;
   while( degree > 0 && buffer[ degree ] == 0 )
      degree--;

   polynomial.resize( degree + 1 );
   for( int i = 0; i <= degree; i++ )
      polynomial[ i ] = buffer[ i ];
}


// outputs the specified polynomial
void output( vector< int > polynomial )
{
   int degree = polynomial.size() - 1;
   if( isZero( polynomial ) ) // zero polynomial
      cout << 0;
   else
   {
      if( degree == 0 ) // constant polynomial
      {
         if( polynomial[ 0 ] < 0 )
            cout << "-" << -polynomial[ 0 ];
         else if( polynomial[ 0 ] > 0 )
            cout << polynomial[ 0 ];
      }
      else
      {
         if( degree == 1 ) // polynomial of degree 1
         {
            if( polynomial[ 1 ] < 0 )
               cout << "-" << -polynomial[ 1 ] << "x";
            else if( polynomial[ 1 ] > 0 )
               cout << polynomial[ 1 ] << "x";
         }
         else // polynomial of degree at least 2
         {
            // display the leading term
            if( polynomial[ degree ] < 0 )
               cout << "-" << -polynomial[ degree ] << "x^" << degree;
            else if( polynomial[ degree ] > 0 )
               cout << polynomial[ degree ] << "x^" << degree;

            // display all other terms
            for( int i = degree - 1; i > 1; i-- )
               if( polynomial[ i ] < 0 )
                  cout << " - " << -polynomial[ i ] << "x^" << i;
               else if( polynomial[ i ] > 0 )
                  cout << " + " << polynomial[ i ] << "x^" << i;

            // display the term of degree 1
            if( polynomial[ 1 ] < 0 )
               cout << " - " << -polynomial[ 1 ] << "x";
            else if( polynomial[ 1 ] > 0 )
               cout << " + " << polynomial[ 1 ] << "x";
         }

         // display the constant term
         if( polynomial[ 0 ] < 0 )
            cout << " - " << -polynomial[ 0 ];
         else if( polynomial[ 0 ] > 0 )
            cout << " + " << polynomial[ 0 ];
      }
   }

   cout << endl;
}

// returns true if and only if the specified polynomial is zero polynomial
bool isZero( vector< int > polynomial )
{
   if( polynomial.size() == 1 && polynomial[ 0 ] == 0 )  // leading term is 0
      return true;
   return false;
}

// returns true if and only if polynomial1 == polynomial2
bool equal( vector< int > polynomial1, vector< int > polynomial2 )
{
   if( polynomial1.size() != polynomial2.size() )
      return false;

   for( size_t i = 0; i < polynomial1.size(); i++ )
      if( polynomial1[ i ] != polynomial2[ i ] )
         return false;

   return true;
}

// polynomial1 = -polynomial2
void minus( vector< int > &polynomial1, vector< int > polynomial2 )
{
   polynomial1.resize( polynomial2.size() );
   for( size_t i = 0; i < polynomial1.size(); i++ )
      polynomial1[ i ] = -polynomial2[ i ];
}

// addend += adder
void addition( vector< int > &addend, vector< int > adder )
{

    vector<int> tmp((addend.size() > adder.size() ? addend.size() : adder.size()), 0);
    for (int i = 0; i < tmp.size(); i++) {

        tmp[i] += ((i < adder.size() ? adder[i] : 0) + (i < addend.size() ? addend[i] : 0));
    }

    addend = tmp;
    while (addend.size() > 1 && !addend.back()) {

        addend.pop_back();
    }

   if( addend.size() > 1 && addend[ addend.size() - 1 ] == 0 )
      cout << "Leading coefficient of addend cannot be zero!\n";
}

// minuend -= subtrahend
void subtraction( vector< int > &minuend, vector< int > subtrahend )
{
   vector< int > buffer;

   // buffer = -subtrahend
   minus( buffer, subtrahend );

   // minuend = minuend + buffer = minuend - subtrahend
   addition( minuend, buffer );

   if( minuend.size() > 1 && minuend[ minuend.size() - 1 ] == 0 )
      cout << "Leading coefficient of minuend cannot be zero!\n";
}

// product = multiplicand * multiplier
void multiplication( vector< int > multiplicand, vector< int > multiplier, vector< int > &product )
{

    product.assign(multiplicand.size() + multiplier.size()- 1, 0);
    for (int ix = 0; ix < multiplicand.size(); ix++) {

        for (int iy = 0; iy < multiplier.size(); iy++) {

            product[(size_t)ix + (size_t)iy] = multiplicand[ix] * multiplier[iy];
        }
    }

    while (product.size() > 1 && !product.back()) {

        product.pop_back();
    }


   if( product.size() > 1 && product[ product.size() - 1 ] == 0 )
      cout << "Leading coefficient of product cannot be zero!\n";
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividend.size() >= divisor.size()
void division( vector< int > dividend, vector< int > divisor,
              vector< int > &quotient, vector< int > &remainder )
{
    // init quotient
    quotient.assign(dividend.size() - divisor.size(), 0);

    // dividend -> remainder
    remainder.assign(dividend.size(), 0);
    for (int i = 0; i < remainder.size(); i++) {

        remainder[i] = dividend[i];
    }

    // init monomial & buffer
    vector<int> monomial(quotient.size(), 0);
    vector<int> buffer(divisor.size()+ quotient.size()- 1, 0);

    for (int i = quotient.size() - 1; i >= 0; i--) {
        quotient[i] = remainder.back() / divisor.back();
        monomial.assign((size_t)i+ 1, 0);
        monomial[i] = quotient[i];
        buffer.assign(divisor.size()+ monomial.size()- 1, 0);
        multiplication(divisor, monomial, buffer);
        subtraction(remainder, buffer);
        monomial.assign(monomial.size(), 0);
        buffer.assign(buffer.size(), 0);
    }
    monomial.clear();
    buffer.clear();
    while (remainder.size() > 1 && !remainder.back()) {

        remainder.pop_back();
    }
    while (quotient.size() > 1 && !quotient.back()) {

        quotient.pop_back();
    }
   if( quotient.size() > 1 && quotient[ quotient.size() - 1 ] == 0 )
      cout << "Leading coefficient of quotient cannot be zero!\n";

   if( remainder.size() > 1 && remainder[ remainder.size() - 1 ] == 0 )
      cout << "Leading coefficient of remainder cannot be zero!\n";
}