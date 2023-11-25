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
   string sub;
   while(dic>> sub){

      if(isSubstring(sub, inputtedWord)){


         wds<< sub<< '\n';
      }
   }
   dic.close();
   wds.close();
}

// returns true if and only if dictionaryWord is a substring of inputtedWord
bool isSubstring( string &dictionaryWord, string &inputtedWord ){

   for (int i = 0; i <= inputtedWord.size() - dictionaryWord.size(); i++) {
      
      int j;
      for (j = 0; j < dictionaryWord.size(); j++) {
         
         if (inputtedWord[i + j] != dictionaryWord[j]) {
            
            break;
         }
      }
      if (j == dictionaryWord.size()) {
      
         return true; // Return true if the entire dictionaryWord is found in inputtedWord
      }
   }
   return false; // If the loop completes without finding the word
}
