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

// prints all English words which are contiguous substrings of inputtedWord into a file
void string::embeddedWords( string &inputtedWord ){

   // setting files

   ifstream dic("./Dictionary.txt", ios::in);   // input file
   if(!dic){                                    // exception if file not found

      cout<< "File not Founded.\n";
      return;
   }
   ofstream wds("./Words.txt", ios::out);       // output file
   // read file
   while(dic>> this->charArray){                            // end of file
   
      this->size= strlen(this->charArray);
      if(this->isSubstring(inputtedWord)){

         wds<< this->charArray<< '\n';                      // write in output file
      }
   }
   
   // file close
   dic.close();                        
   wds.close();
}

// returns true if and only if dictionaryWord is a substring of inputtedWord
bool string::isSubstring( string &inputtedWord ){

   int j= 0;
   for (int i = 0; i <= inputtedWord.size - this->size && (i+ j)< inputtedWord.size; i++) {
      
      for (j = 0; j < this->size; j++) {
         
         if (inputtedWord.charArray[i + j] != this->charArray[j]) {          // incorrect subString
            
            break;
         }
      }
      if (j == this->size) {
      
         return true;
      }
   }
   return false;
}
