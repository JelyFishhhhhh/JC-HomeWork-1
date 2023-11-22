#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// prints all English words which are contiguous substrings of inputtedWord into a file
void embeddedWords( string &dictionaryWord, string &inputtedWord );

// returns true if and only if dictionaryWord is a substring of inputtedWord
bool isSubstring( string &dictionaryWord, string &inputtedWord );

int main()
{
   string inputtedWord;
   cout << "Enter a word: ";
   cin >> inputtedWord;

   string dictionaryWord;
   embeddedWords( dictionaryWord, inputtedWord );

   system( "pause" );
}

// prints all English words which are contiguous substrings of inputtedWord into a file
void embeddedWords( string &dictionaryWord, string &inputtedWord ){

   ifstream dic("./Dictionary.txt");
   ofstream wds("./Words.txt");
   string i;
   while(dic>> i){

      wds<< i<< '\n';
   }
   dic.close();
}

// returns true if and only if dictionaryWord is a substring of inputtedWord
bool isSubstring( string &dictionaryWord, string &inputtedWord ){


}
