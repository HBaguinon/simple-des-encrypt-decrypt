/*******************************************************************************
* NAME: HAROLD DANE C. BAGUINON                                                *
* DATE: 02/18/2016                                                             *
* DATE DUE: 02/25/2016 11:59:00 PM                                             *
* COURSE: CSC555 010                                                           *
* PROFESSOR: DR. ZHANG                                                         *
* PROJECT: #2                                                                  *
* FILENAME: binaryTest.cpp                                                     *
* PURPOSE: This program is the first project. The purpose of the project is to *
*          decrypt a message which was encrypted using a monoalphabetic cipher.*
*          The first program will read in the ciphertext file and analyze it   *
*          for the frequency of letters. The second program will allow the user*
*          to manually decrypt the message by substituing individual letters in*
*          the ciphertext, eventually leading to the decrypted message.        *
*******************************************************************************/

#include <iostream>				// for i/o functions
#include <fstream>				// for external file streams
#include <cstdlib>				// for EXIT_FAILURE
#include <string>				// for string objects
#include <algorithm>			// for swap 
using namespace std;

// wordRec is the struct which will contain each letter with its occurrence.
/*struct wordRec
{
    char letter;
    int occurrence;
};*/

// Functions used ...
/*
	Function name: printAll
	Description: Prints all of the letters in the array with the corresponding
                 occurrence (count) of each letter.
	Parameters: wordRec list[]: The array which stores the letters and counts.
				int &items: The maximum number of letters to process.
	Return Value: None.
*/
//void printAll(wordRec list[], int items, int totalChars);

int main() {
    string key;
    char keybin[10];
    
    string plaintext;
    int keyInt;
    int plaintextInt;
    
    // entertext(key, plaintext);
    int items = 0;
    int totalChars = 0;
    
    char h = 'h';
    int ih = h;
    char b = 'b';
    int ib = b;
    int bh = b+h;
    int hb = h^b;
    int ibih = ib+ih;
    int ihib = ih^ib;
    char cbh = b+h;
    char h1 = (h+1);
    
    cout << "h: " << h << " ih: " << ih << endl;
    cout << "b: " << b << " ib: " << ib << endl;
    cout << "char b+h: " << bh << endl;
    cout << "char h^b: " << hb << endl;
    cout << "int b+h: " << ibih << endl;
    cout << "int h^b: " << ihib << endl;
    cout << "char cbh: " << cbh << endl;
    cout << "h + 1: " << h1 << endl;
    printf("x: %x\n", h);
    // printf("s: %s\n", h);
    
    /*openFile(inf, fileName);
    countChars(inf, totalChars);
    reopenFile(inf, fileName);
    readTokens(inf, list, items);
    selSort(list, items);
    // freqSort(list, items);              EXPERIMENTAL FUNCTION. COMMENT OUT.
    cout << "Frequency analysis for " << fileName << ": \n";
    printAll(list, items, totalChars);*/
    return 0;
}