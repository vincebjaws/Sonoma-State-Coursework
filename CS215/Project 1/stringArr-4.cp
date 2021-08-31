/******************************************************/
/* Name: Vince Bjazevic                               */
/* Class: CS215                                       */
/* File: stringArr.cpp                                */
/* Assignment: Project 1                              */
/* Date: 3/7/19                                       */
/*                                                    */
/******************************************************/


/* Implementation of the StringArr class defined in StringArr.hpp */
#include <fstream>
#include <iostream>
#include "stringArr.hpp"

using namespace std;

/* StringArr's default constructor
 * Should initialize its private member variables appropriately
 */
StringArr::StringArr() {
  count = 0;
}

/* Alternate constructor: when passed a filename,
 * you should use its contents to populate the StringArr object
 */
StringArr::StringArr(string filename) {
  count = 0;
  readFromFile(filename);
}

/* Populate your string array by reading the named file
 * Overwrite array contents if they already exist
 * Return true if you were able to read the file, false otherwise
 */
bool StringArr::readFromFile(string filename) {
  string string; // A placeholder for the strings that will populate WordArray
  ifstream inFile;
  inFile.open(filename); //Opens a file the user chooses
  if (inFile.fail())
    return false; // If no file is return false
  count = 0; // Sets count to zero if it is not, OVERWRITE ANY PREVIOUS COUNT THAT EXISTS
  while (inFile >> string)  // Populate array
    {
      WordArray[count] = string; 
      count++;
    }

  return true;
}

/* Print all strings in the array, one per line,
 * in the original order
 */
void StringArr::print() {
  for(int i = 0; i<count; i++)
	cout << WordArray[i] << endl;
  cout << endl;
}

/* Return the shortest string in the array
 * Break ties however you want
 * For an empty array, return the empty string ("")
 */
string StringArr::shortest() {
  int Short = 0;
  for (int i=0; i<count;i++) { // Iterates through every word
    if (WordArray[Short].length() > WordArray[i].length()) // Compares length
      Short = i;
  }
  return WordArray[Short];
}

/* Return the longest string in the array
 * Break ties however you want
 * For an empty array, return the empty string ("")
 */
string StringArr::longest() {
  int Long = 0;
  for (int i =0;i<count;i++) { // Iterates through every word
    if (WordArray[Long].length() < WordArray[i].length()) // Compares length
      Long = i;
  }
  return WordArray[Long];
}

/* Print all strings in the array, one per line, in
 * alphabetically sorted order (using > and < operators).
 * DON'T CHANGE THE ORIGINAL ARRAY!!
 */
void StringArr::printSorted() {
  string SortedArray[MAXSIZE]; // A temp array to store sorted strings
  for (int i = 0;i < count;i++)   { // Populates Sorted array
      SortedArray[i] = WordArray[i];
    }
  for (int i = 1; i < count; i++) { // Goes through every word
      int j = i;
      while (j > 0 and SortedArray[j] < SortedArray[j -1])  {// Swap in the sorted array 
	string placeholder = SortedArray[j];
	placeholder = SortedArray[j - 1];
	SortedArray[j -1] = SortedArray[j];
	SortedArray[j] = placeholder;
	j--;
	}
    }
  for (int i = 0; i < count; i++)  { // Prints the sorted array
    cout << SortedArray[i] << endl;
  }
 cout << endl;
}

/* Populate the seq[] array with the longest ascending sequence of consecutive
 * strings in the file.
 */
int StringArr::longestAscending(string seq[]) {
  int counter = 0; // A placeholder for the largest amount of ascending strings in a row
  int increment = 1;// An incrementor that counts the amount of ascending strings in a row
  int ptr = 0; // A placeholder for the first word in the row
  for (int i = 1; i < count;i++){
    if (WordArray[i - 1] < WordArray[i]) { // Compares a string to the string behind it
      increment++;
      if(increment > counter) { // If the increment is larger than the placeholder, it sets the
	counter = increment;    // place holder to max counter
	ptr = i - increment; // Finds the new start by subtracting the incrementor from the total
	ptr++;       
      }
    }

    else
      increment = 1; // If the string is not ascending, set the incrementor to 1
  }
  
  populate(seq, ptr, counter); // Populates seq[]

  return counter;
}

/* Populate the seq[] array with the longest ascending sequence of consecutive
 * strings in the file.
 */

int StringArr::longestDescending(string seq[]) {
  int counter = 0; // A placeholder for the largest amount of ascending strings in a row
  int increment = 1;// An incrementor that counts the amount of ascending strings in a row
  int ptr = 0; // A placeholder for the first word in the row
  for (int i = 1; i < count;i++){
    if (WordArray[i - 1] > WordArray[i]) { 
      increment++;
      if(increment > counter) { // If the incrementor is larger than the placeholder, it sets the
	counter = increment;    
	ptr = i - increment; // Finds the new start by subtracting the incrementor from the total
	ptr++;       
      }
    }
    
    else
      increment = 1; // If the string is not ascending, set the incrementor to 1
  }
  
  populate(seq, ptr, counter); // Populates seq[]
  
  return counter;
}

// Member function populates the array
void StringArr::populate(string w[], int start, int n) {
  for (int i = 0; i< n;i++) {
    w[i] = WordArray[start+i];
  }

}


