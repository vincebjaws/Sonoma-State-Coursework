/*********************************************/
/* Name: Vince Bjazevic                      */
/* File: main.cpp                            */
/* Assignment: Project 1                     */
/* Date: 3/7/19                              */
/*                                           */
/*********************************************/

#include "stringArr.hpp"
#include <iostream>
using namespace std;

void TestArray(StringArr a) {
   cout << "**** ARRAY ****\n";
   cout << "Printing:\n";
   a.print(); 
   cout << "Printing sorted version:\n";
   a.printSorted(); 
   cout << "Printing shortest and longest strings:\n";
   cout << "Shortest: " << a.shortest() << endl;
   cout << "Longest: " << a.longest() << endl;
   string mySequence[MAXSIZE];
   int seqLength = a.longestAscending(mySequence);
   cout << "Length of longest ascending sequence: " << seqLength << endl;
   cout << "Printing the array: { ";
   for (int i = 0; i<seqLength;i++)
     cout << mySequence[i]<<' ';
   cout << '}' <<endl;
   seqLength = a.longestDescending(mySequence);
   cout << "Length of longest descending: " << seqLength << endl;
   cout << "Printing the array: { ";
   for (int i = 0; i<seqLength;i++)
     cout << mySequence[i]<<' ';
   cout << '}' << endl;
}

int main () {
  StringArr arr("string.txt");
  StringArr arr2("strings.txt");
  StringArr arr3("strings.txt");
  TestArray(arr);

  return 0;
}







