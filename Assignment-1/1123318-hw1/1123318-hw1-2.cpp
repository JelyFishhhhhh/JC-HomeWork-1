#include <iostream>
using namespace std;

int main()
{
   int number;

   cout << "Enter a five-digit positive integer: ";
   cin >> number;

   cout<<"\t\t    ";

   for(int x= 0; x<= 5; x++){
      cout<<"\b\b\b\b"<<number% 10<<"\b";
      if(x== 4){
         break;
      }
      number/=10;
      // cout<<number;
   }

   cout << number << endl;

}