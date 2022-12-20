/*
Created by: Arjun Mandair
Created on: November 21, 2022
Last modified: November 22, 2022
Version: 1.0

Purpose: To write a code to help Emily determine which books to read by
audiobook or printbook

Assumptions: We are assuming that there are no more than 50 unique books
to read from the audio and print files

Other notes: I used the "Book.cpp" file as a reference and slightly
modified the class to different names. Note that the class functions
exactly like the one in "Book.cpp"
*/

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

//Declaring constants
const int maxBooks = 50;

//Creating an object called "Book"
class Book 
{
		string bookTitle;
		int numberOfPages;
		string formatType;

	public:
		//Default constructor (setter)
		Book() 
		{
			bookTitle = "";
			numberOfPages = 0;
			formatType = "print";
		}

		//Data constructor (setter)
		Book(string title, int numPages, string isAudio) 
		{
			bookTitle = title;
			numberOfPages = numPages;
			formatType = isAudio;
		}

		//Getter that returns the name of a book
		string getName() const 
		{
			return bookTitle;
		}

		//Getter that returns the number of pages in a book
		int getNumPages() const 
		{
			return numberOfPages;
		}

		//Getter that returns if true if book is audiobook, false if print
		bool isAudio() const 
		{
			if(formatType == "audio") 
			{
				return true;
			} 
			else 
			{
				return false;
			}
		}


		//Function that reads from a file and stores data into a book object
		void readBook(ifstream & FileIn) 
		{
			string title;
			int pages;
			string format;
			FileIn >> title >> pages >> format;
			(*this).bookTitle = title;
			(*this).numberOfPages = pages;
			(*this).formatType = format;
			return;
		}


		//Function that prints out a book object information
		void printBook() const 
		{
			cout << setw(37) << bookTitle << setw(5)
			     << numberOfPages << setw(7) << formatType << endl;
		}

		//Function that returns true if books are same
		bool isSame(Book bookTwo) const 
		{
			if((*this).bookTitle == bookTwo.bookTitle
			        && (*this).numberOfPages == bookTwo.numberOfPages) 
			{
				return true;
			} 
			else 
			{
				return false;
			}
		}
};

//Function prototyping
int numBooks(ifstream & FileIn, Book bookArray[]);

int main() 
{
	//Declaring variables and arrays
	int numPrintBooks = 0;
	int numAudioBooks = 0;
	Book printBookArray[maxBooks];
	Book audioBookArray[maxBooks];

	//Opening files and checking if opened
	ifstream FileInPrint("print.txt");
	ifstream FileInAudio("audio.txt");

	if(!FileInPrint || !FileInAudio) 
	{
		cout << "Unable to open file";
		return EXIT_FAILURE;
	}

	//Storing data into arrays and finding num of books in each file
	numPrintBooks = numBooks(FileInPrint, printBookArray);
	numAudioBooks = numBooks(FileInAudio, audioBookArray);

	//Outputting the entire list of audiobooks
	for(int count = 0; count < numAudioBooks; count++) 
	{
		audioBookArray[count].printBook();
	}

	//Outputting print books that are not available as audiobooks
	for(int printCount = 0; printCount < numPrintBooks; printCount++) 
	{
		bool displayPrintBook = false;
		for(int audioCount = 0; audioCount < numAudioBooks; audioCount++) 
		{
			if(printBookArray[printCount].isSame(audioBookArray[audioCount])
			        == true) 
			{
				displayPrintBook = true;
			}
		}

		if(displayPrintBook == false) 
		{
			printBookArray[printCount].printBook();
		}
	}

	//Closing files
	FileInPrint.close();
	FileInAudio.close();
	return EXIT_SUCCESS;
}


//Function that reads data into bookArray and return num of books read
int numBooks(ifstream & FileIn, Book array[]) 
{
	int count = 0;

	while(FileIn) 
	{
		Book b;
		b.readBook(FileIn);
		array[count] = b;
		count++;
	}

	return count-1;
}

/*
  The_Hitchhikers_Guide_To_The_Galaxy  180  audio
                  The_Grapes_Of_Wrath  416  audio
                       The_Life_Of_Pi  352  audio
                        The_Alchemist  167  audio
                    A_Game_Of_Thrones  864  audio
                    Lord_Of_The_Flies  285  audio
                         Little_Women  248  audio
                         Frankenstein  288  audio
                          Vanity_Fair  883  audio
                     The_Hunger_Games  374  audio
                  Pride_And_Prejudice  398  audio
                 The_Age_Of_Innocence  301  audio
           The_Picture_of_Dorian_Gray  224  audio
                        Amongst_Women  184  audio
                    Wuthering_Heights  354  audio
                The_Devil_Wears_Prada  360  audio
                                 Dune  412  audio
                          The_Martian  369  audio
                            Jane_Erye  950  audio
                       The_Book_Thief  584  audio
                            Moby_Dick  720  audio
                     The_Great_Gatsby  184  audio
                          Disappeared  384  audio
                   A_Clockwork_Orange  158  print
                      Brave_New_World  201  print
                            If_I_Stay  224  print
              A_Brief_History_Of_Time  241  print
                   The_Scarlet_Letter  250  print
                                 Wild  315  print
                The_Girl_On_The_Train  316  print
                      The_Maze_Runner  371  print
                                 Emma  474  print
                          Don_Quixote 1056  print
                              Ulysses  719  print
                      Life_After_Life  622  print
                   The_Sun_Also_Rises  247  print
                     The_Longest_Ride  568  print
                       Milk_And_Honey  226  print
                    A_Christmas_Carol  100  print
                  The_Love_Hypothesis  384  print
                         The_Notebook  214  print
                          I_Am_Malala  288  print
                                Smile  213  print
              Becoming_Michelle_Obama  448  print
             The_Chronicles_Of_Narnia  766  print
                 Crime_And_Punishment  492  print
                   The_Wise_Mans_Fear  994  print

--------------------------------
Process exited after 0.1993 seconds with return value 0
Press any key to continue . . .
*/
