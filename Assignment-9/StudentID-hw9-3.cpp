#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include <cstring>
using std::strlen;

struct string
{
   size_t size = 0;
   char *charArray = new char[ 21 ]();
};

// prints all English words which are contiguous substrings of inputtedWord into a file
void embeddedWords( string &dictionaryWord, string &inputtedWord );

// returns true if and only if dictionaryWord is a substring of inputtedWord
bool isSubstring( string &dictionaryWord, string &inputtedWord );

int main()
{
   string inputtedWord;
   cout << "Enter a word: ";
   cin >> inputtedWord.charArray;
   inputtedWord.size = strlen( inputtedWord.charArray );

   string dictionaryWord;

   embeddedWords( dictionaryWord, inputtedWord );

   system( "pause" );
}

void embeddedWords( string &dictionaryWord, string &inputtedWord ){

   // setting files

   ifstream dic("./Dictionary.txt", ios::in);   // input file
   if(!dic){                                    // exception if file not found

      cout<< "File not Founded.\n";
      return;
   }
   ofstream wds("./Words.txt", ios::out);       // output file
   // read file
   while(dic>> dictionaryWord.charArray){                  // end of file

      dictionaryWord.size= strlen(dictionaryWord.charArray);
      if(isSubstring(dictionaryWord, inputtedWord)){

         wds<< dictionaryWord.charArray<< '\n';                      // write in output file
      }
   }
   
   // file close
   dic.close();                        
   wds.close();
   delete[] inputtedWord.charArray;
   delete[] dictionaryWord.charArray;
}

// returns true if and only if dictionaryWord is a substring of inputtedWord
bool isSubstring( string &dictionaryWord, string &inputtedWord ){

   int j= 0;
   for (int i = 0; i <= inputtedWord.size - dictionaryWord.size && (i+ j)< inputtedWord.size; i++) {
      
      for (j = 0; j < dictionaryWord.size; j++) {
         
         if (inputtedWord.charArray[i + j] != dictionaryWord.charArray[j]) {          // incorrect subString
            
            break;
         }
      }
      if (j == dictionaryWord.size) {
      
         return true;
      }
   }
   return false;
}