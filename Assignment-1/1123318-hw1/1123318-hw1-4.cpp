#include <iostream>
using namespace std; 

int main()
{
   int side1;
   int side2;
   int side3;

   cout << "Enter side 1: ";
   cin >> side1;

   cout << "Enter side 2: ";
   cin >> side2;

   cout << "Enter side 3: ";
   cin >> side3;
      
   // sort

   if(side1>side2){
      swap(side1, side2);
   }
   if(side1>side3){
      swap(side1, side3);
   }
   if(side2>side3){
      swap(side2, side3);
   }

   if(side1* side1+ side2* side2== side3* side3){
      cout << "These are the sides of a right triangle.\n";
      return 0;
   }
   
   cout << "These do not form a right triangle.\n";
   return 0;
}