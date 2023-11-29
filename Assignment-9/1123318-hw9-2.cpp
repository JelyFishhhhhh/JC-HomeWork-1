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

// prints all English words which are contiguous substrings of inputtedWord into a file
void embeddedWords( vector< char > &dictionaryWord, vector< char > &inputtedWord ){

   // setting files

   ifstream dic("./Dictionary.txt", ios::in);   // input file
   if(!dic){                                    // exception if file not found

      cout<< "File not Founded.\n";
      return;
   }
   ofstream wds("./Words.txt", ios::out);       // output file
   string tmp;
   // read file
   while(dic>> tmp){                            // end of file

      dictionaryWord.assign(tmp.size(), '\0');
      for(int i= 0; i< tmp.size(); i++){

         dictionaryWord[i]= tmp[i];
      }

      if(isSubstring(dictionaryWord, inputtedWord)){

         wds<< tmp<< '\n';                      // write in output file
      }
   }
   
   // file close
   dic.close();                        
   wds.close();
}

// returns true if and only if dictionaryWord is a substring of inputtedWord
bool isSubstring( vector< char > &dictionaryWord, vector< char > &inputtedWord ){

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