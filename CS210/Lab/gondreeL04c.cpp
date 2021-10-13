// Assignment :
// File :
// Author :
// Date :
// Description :

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct worddata
{
	string word;
	int vowels;
	int consonants;
	int digits;
	int specialchars;
};

int ReadFile (ifstream & input, worddata * & Words);
void WriteReport (ostream & output, worddata Words [], int count);
void Swap (worddata & a, worddata & b);
void WordSort (worddata Words [], int N);

int main (int argc, char * argv [])
{
	// Check to see if the user entered a file name
 	// Exit if no file name
 	if (argc < 3)
 	{
	 	cout << "Usage: " << argv[0] << " <input-file> <output-file>\n";
 		exit (1);
 	}

 	// Open the input file
 	ifstream input (argv[1]);

 	// Check to see if the file was successfully opened
 	// Exit if no file found
 	if (input.fail())
 	{
 		cout << "File: " << argv[1] << " not found\n";
 		exit (2);
 	}

 	// Open the output file
 	ofstream output (argv[2]);

 	// Check to see if the file was successfully opened
 	// Exit if file could not be opened
 	if (output.fail())
 	{
 		cout << "File: " << argv[2] << " could not be opened\n";
 		exit (3);
 	}

	// Declare an array of worddata objects to hold the words
	// and their vowel, consonant, digit, and special
	// character counts.
	worddata * WordArray;
	// Call the ReadFile function to read the file, store the
	// words in the array and return the number of words read
	// from the file.
	int count = ReadFile (input, WordArray);
	// Call the WordSort function to sort the words into
	// alphabetical order.
	WordSort (WordArray, count);
	// Call the WriteReport function to write the data
	// stored in the array in a formatted fashion.
	WriteReport (output, WordArray, count);

	// Close the input file
	input.close ();
	// Close the output file
	output.close ();
	return 0;
}

int ReadFile (ifstream & input, worddata * & Words)
{
	int count = 0;
	string oneword;
	// Read and count the words in the file
	while (input >> oneword)
		count++;
	// Allocate space for the number of words counted by the 
	// previous loop
	Words = new worddata [count];
	// Clear the fail flag
	input.clear();
	// Reposition the file pointer to the beginning of the file
	input.seekg (0, ios::beg);
	count = 0;
	// Read the words from the file into the array
	while (input >> Words[count].word)
	{
		Words[count].vowels = Words[count].consonants = 0;
		Words[count].digits = Words[count].specialchars = 0;

		// Count the number of vowels, consonants, digits
		// and special characters in the word and store them
		// in the object Words[count]
		for (int i = 0; i < Words[count].word.size(); i++)
			if (isalpha (Words[count].word[i]))
			{
				char lc = tolower (Words[count].word[i]);
				if (lc == 'a' || lc == 'e' || lc == 'i' ||
				    lc == 'o' || lc == 'u')
					Words[count].vowels++;
				else
					Words[count].consonants++;
			}
			else
				if (isdigit (Words[count].word[i]))
					Words[count].digits++;
				else
					Words[count].specialchars++;
		count++;
	}
	// Close the file
	input.close();
	// Return the size of the Words array
	return count;
}

void WriteReport (ostream & output, worddata Words [], int count)
{
	worddata totals;
	totals.vowels = totals.consonants = 0;
	totals.digits = totals.specialchars = 0;
	output << setw (15) << left << "Words";
	output << setw (8) << right << "Vowels";
	output << setw (8) << "Const.";
	output << setw (8) << "Digits";
	output << setw (8) << "Special" << endl;;
	for (int i = 0; i < count; i++)
	{
		output << setw (15) << left << Words[i].word;
		output << setw (8) << right << Words[i].vowels;
		output << setw (8) << Words[i].consonants;
		output << setw (8) << Words[i].digits;
		output << setw (8) << Words[i].specialchars << endl;;
		totals.vowels += Words[i].vowels;
		totals.consonants += Words[i].consonants;
		totals.digits += Words[i].digits;
		totals.specialchars += Words[i].specialchars;
	}
	output << setw (47) << "---     ---     ---     ---" << endl;
	output << setw (15) << left << "Totals";
	output << setw (8) << right << totals.vowels;
	output << setw (8) << totals.consonants;
	output << setw (8) << totals.digits;
	output << setw (8) << totals.specialchars << endl;;
}

void Swap (worddata & w1, worddata & w2)
{
	worddata temp = w1;
	w1 = w2;
	w2 = temp;
}

void WordSort (worddata Words [], int N)
{
	for (int i = 1; i < N; i++)
		for (int j = i; j > 0 && Words[j].word < Words[j-1].word; j--)
			Swap (Words[j], Words[j-1]);
}

	

