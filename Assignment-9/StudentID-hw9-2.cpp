#include <iostream>
#include <fstream>
#include <vector>
using namespace::std;

// prints all English words which are contiguous substrings of inputtedWord into a file
void embeddedWords( vector< char > &dictionaryWord, vector< char > &inputtedWord );

// returns true if and only if dictionaryWord is a substring of inputtedWord
bool isSubstring( vector< char > &dictionaryWord, vector< char > &inputtedWord );

int main()
{
   vector< char > inputtedWord;

   cout << "Enter a word: ";
   char ch = cin.get();
   while( ch != '\n' )
   {
      inputtedWord.push_back( ch );
      ch = cin.get();
   }

   vector< char > dictionaryWord;
   embeddedWords( dictionaryWord, inputtedWord );

   system( "pause" );
}