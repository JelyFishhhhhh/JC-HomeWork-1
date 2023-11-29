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

   // setting files

   ifstream dic("./Dictionary.txt", ios::in);   // input file
   if(!dic){                                    // exception if file not found

      cout<< "File not Founded.\n";
      return;
   }
   ofstream wds("./Words.txt", ios::out);       // output file
   // read file
   while(dic>> dictionaryWord){                            // end of file

      if(isSubstring(dictionaryWord, inputtedWord)){

         wds<< dictionaryWord<< '\n';                      // write in output file
      }
   }
   
   // file close
   dic.close();                        
   wds.close();
}

// returns true if and only if dictionaryWord is a substring of inputtedWord
bool isSubstring( string &dictionaryWord, string &inputtedWord ){

   int j= 0;
   for (int i = 0; i <= inputtedWord.size() - dictionaryWord.size() && (i+ j)< inputtedWord.size(); i++) {
      
      for (j = 0; j < dictionaryWord.size(); j++) {
         
         if (inputtedWord[i + j] != dictionaryWord[j]) {          // incorrect subString
            
            break;
         }
      }
      if (j == dictionaryWord.size()) {
      
         return true;
      }
   }
   return false;
}
