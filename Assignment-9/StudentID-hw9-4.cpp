#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

class string
{
public:
   // prints all English words which are contiguous substrings of inputtedWord into a file
   void embeddedWords( string &inputtedWord );

   // returns true if and only if dictionaryWord is a substring of inputtedWord
   bool isSubstring( string &inputtedWord );

   size_t size = 0;
   char *charArray = new char[ 21 ]();
};

int main()
{
   string inputtedWord;
   cout << "Enter a word: ";
   cin >> inputtedWord.charArray;
   inputtedWord.size = strlen( inputtedWord.charArray );

   string dictionaryWord;
   dictionaryWord.embeddedWords( inputtedWord );

   system( "pause" );
}