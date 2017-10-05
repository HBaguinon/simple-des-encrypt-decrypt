/*******************************************************************************
* NAME: HAROLD DANE C. BAGUINON                                                *
* DATE: 02/18/2016                                                             *
* DATE DUE: 02/25/2016 11:59:00 PM                                             *
* COURSE: CSC555 010                                                           *
* PROFESSOR: DR. ZHANG                                                         *
* PROJECT: #2                                                                  *
* FILENAME: simple-des.cpp                                                     *
* PURPOSE: This program is the second project. The purpose of the project is to*
*          study the DES encryption algorithm by encrypting user text input    *
*          with the Simple DES encryption algorithm. This program will convert *
*          each character in the input into an 8-bit binary ciphertext, which  *
*          is created by first creating two keys based on user input, and then *
*          putting the text input through a series of manipulations of its bits*
*          such as permutation, rearrangement, shifts, swaps, expansions, and  *
*          xor functions. The final output is 8-bit binary ciphertext.         *
*******************************************************************************/

#include <iostream>				// for i/o functions
#include <fstream>				// for external file streams
#include <cstdlib>				// for EXIT_FAILURE
#include <string>				// for string objects
#include <cstring>				// for cstring objects
#include <bitset>               // for bitset
#include <sstream>              // for stringstream

using namespace std;

// Functions used ... 
/*******************************************************************************
*   Function name: menu                                                        *
*   Description: Displays menu choices, prompting the user to type a single    *
*                character as input in order to choose which menu option to    *
*                select. Once an option is executed, the menu appears again,   *
*                unless Q is chosen, which would quit the program. Input is not*
*                case sensitive.                                               *
*   Parameters: None.                                                          *
*   Return Value: int numberValue: Export; returns input from user.            *
*******************************************************************************/
char menu();

/*******************************************************************************
*   Function name: regulateOutput                                              *
*   Description: Regulates the output based on user input.                     *
*   Parameters: string &key: Import: The key as input from the user.           *
*                char keyBin[]: Import: The first key.                         *
*                char keyBin2[]: Import: The second key.                       *
*                char postIP1[]: Import: The key array after IP.               *
*                char postIP2[]: Import: The key array after IP.               *
*                char bitsetArray[]: Import: The bitset array.                 *
*                char preS[]: Import: The array before S Boxes.                *
*                char postS[]: Import: The array after S Boxes.                *
*                char preSwap[]: Import: The array before swap.                *
*                char bitsetArray2[]: Import: The second key array.            *
*                char preIP1[]: Import: The array before IP-1.                 *
*                char ciphertext[]: Import: The ciphertext array.              *
*                char decryptedText[]: Export: The decrypted text.             *
*   Return Value: None.                                                        *
*******************************************************************************/
void regulateOutput(string&, char[], char[], char[], char[], char[], char[], 
                    char[], char[], char[], char[], char[], char[]);

/*******************************************************************************
*   Function name: generateKeys                                                *
*   Description: Completes the steps in order to create the two keys.          *
*   Parameters: string &key: Import; The 10-digit key.                         *
*               char keyBin[]: Import: The first key.                          *
*               char keyBin2[]: Import: The second key.                        *
*   Return Value: None.                                                        *
*******************************************************************************/
void generateKeys(string&, char[], char[]);

/*******************************************************************************
*   Function name: createKey                                                   *
*   Description: Asks user for binary input to create the base 10-digit key.   *
*                This function also error-checks to make sure that the input is*
*                10-digits long and contains only 0 and 1.                     *
*   Parameters: string key: Import; The variable which contains user input.    *
*               char keyBin[]: Import; The key, stored as a 10-digit array.    *
*   Return Value: None.                                                        *
*******************************************************************************/
void createKey(string&, char[]);

/*******************************************************************************
*   Function name: P10                                                         *
*   Description: Executes a permutation for all 10 bits in the array, resulting*
*                in a rearranged key.                                          *
*   Parameters: char keyBin[]: Import; The key, stored as a 10-digit array.    *
*   Return Value: None.                                                        *
*******************************************************************************/
void P10(char[]);

/*******************************************************************************
*   Function name: LS1                                                         *
*   Description: Executes a left shift for the left half and the right half of *
*                the key, placing the first digit at the end of each half.     *
*                This function also makes a copy of the key for use later.     *
*   Parameters: char keyBin[]: Import; The key, stored as a 10-digit array.    *
*               char keyBin2[]: Import; A copy of the key.                     *
*   Return Value: None.                                                        *
*******************************************************************************/
void LS1(char[], char[]);

/*******************************************************************************
*   Function name: P8                                                          *
*   Description: Executes a permutation for the first 8 bits in the array,     *
*                resulting in a rearranged key. The array may still contain 10 *
*                digits, but only the first 8 are used in subsequent functions.*
*   Parameters: char keyBinary[]: Import; The key, stored as a 10-digit array. *
*   Return Value: None.                                                        *
*******************************************************************************/
void P8(char[]);

/*******************************************************************************
*   Function name: LS2                                                         *
*   Description: Executes a left shift for the left half and the right half of *
*                the key, placing the first two digits at the end of each half.*
*   Parameters: char keyBin2[]: Import; A copy of the first key, as an array.  *
*   Return Value: None.                                                        *
*******************************************************************************/
void LS2(char[]);

/*******************************************************************************
*   Function name: IP                                                          *
*   Description: Executes the initial permutation for each character of input, *
*                beginning the encryption process and resulting in a rearranged*
*                binary array. Function also creates copies of the array for   *
*                later use in the encryption process.                          *
*   Parameters: char bitSet1[]: Import; Bitset array for text character.       *
*               char copy[]: Import; Copy of bitset array for text character.  *
*               char copy2[]: Import; Second copy of array for text character. *
*   Return Value: None.                                                        *
*******************************************************************************/
void IP(char[], char[], char[]);

/*******************************************************************************
*   Function name: EP                                                          *
*   Description: Performs an expansion and permutation of the input, resulting *
*                in an 8-bit array from a 4-bit input. As the function is      *
*                written (and as the program is designed), the input is        *
*                actually an 8-bit array, but only the last 4 bits are used.   *
*   Parameters: char input[]: Import; Bitset array for text character.         *
*   Return Value: None.                                                        *
*******************************************************************************/
void EP(char[]);

/*******************************************************************************
*   Function name: xor8                                                        *
*   Description: Performs an exclusive or operation on two 8-bit arrays, with  *
*                an 8-bit array as output. One of the inputs may be a 10-bit   *
*                array, but only the first 8 bits go through the operation.    *
*   Parameters: char input1[]: Import; Bitset array for text character.        *
*               char input2[]: Import; The key, stored as a 10-digit array.    *
*               char output[]: Export; The result of the operation.            *
*   Return Value: None.                                                        *
*******************************************************************************/
void xor8(char[], char[], char[]);

/*******************************************************************************
*   Function name: s0s1                                                        *
*   Description: Uses 4 bits of input to output 2 bits. The output is chosen   *
*                based on two pre-written S-Box tables, which are written as   *
*                two-dimensional arrays. The input as designed here, is an     *
*                8-bit array, and the output is a 4-bit array. The first and   *
*                fourth bits of the input decide the row, and the second and   *
*                third bits of the input decide the column. The left half is   *
*                for S-Box 0 and the right half is for S-Box 1.                *
*   Parameters: char input[]: Import; Bitset array from previous xor function. *
*               char output[]: Export; 4-bit output from S-Boxes.              *
*   Return Value: None.                                                        *
*******************************************************************************/
void s0s1(char[], char[]);

/*******************************************************************************
*   Function name: P4                                                          *
*   Description: Executes a permutation for the first 4 bits in the array,     *
*                resulting in a rearranged array.                              *
*   Parameters: char input[]: Import; 4-bit output from S-Boxes.               *
*   Return Value: None.                                                        *
*******************************************************************************/
void P4(char[]);

/*******************************************************************************
*   Function name: xor4                                                        *
*   Description: Performs an exclusive or operation on two 4-bit arrays, with  *
*                a 4-bit array as output. One of the inputs may be an 8-bit    *
*                array, but only the first 4 bits go through the operation.    *
*   Parameters: char input1[]: Import; Bitset array for text character.        *
*               char input2[]: Import; 4-bit output from previous permutation. *
*               char output[]: Export; The result of the operation.            *
*   Return Value: None.                                                        *
*******************************************************************************/
void xor4(char[], char[], char[]);

/*******************************************************************************
*   Function name: SW                                                          *
*   Description: Performs a swap or switch of the left and right half of the   *
*                arrays which resulted from the previous xor operation and the *
*                initial permutation, respectively. The four bits from the xor *
*                function continue as the "right half" and the last 4 bits of  *
*                the IP function continue as the "left half". The "right half" *
*                portion continues to the second EP function.                  *
*   Parameters: char input1[]: Import; 4-bit output from previous operation.   *
*               char input2[]: Import; Bitset array for text character.        *
*               char copyof1[]: Import; A copy of the 4-bit xor output.        *
*   Return Value: None.                                                        *
*******************************************************************************/
void SW(char[], char[], char[]);

/*******************************************************************************
*   Function name: IP1                                                         *
*   Description: Executes the inverse of the initial permutation for each      *
*                character of input, completing the encryption process and     *
*                resulting in the 8-bit ciphertext, which is printed out.      *
*   Parameters: char preIP1[]: Import; 4-bit output from previous operation.   *
*               char postIP2[]: Import; "Right half" from SW function.         *
*               char output[]: Export; Resulting output of permutation.        *
*   Return Value: None.                                                        *
*******************************************************************************/
void IP1(char[], char[], char[]);

/*******************************************************************************
*   Function name: createCipherNumber                                          *
*   Description: Sets the number of times that the decryption algorithm will   *
*                occur based on user input of number of ciphertexts.           *
*   Parameters: string &input: Import; user text input (number).               *
*               int &cipherNum: Export; the input converted into an integer.   *
*   Return Value: None.                                                        *
*******************************************************************************/
void createCipherNumber(string&, int&);

/*******************************************************************************
*   Function name: createCiphertext                                            *
*   Description: Sets the number of times that the decryption algorithm will   *
*                occur based on user input of number of ciphertexts.           *
*   Parameters: string &input: Import; user text input (number).               *
*               char ciphertext[]: Import: Ciphertext array.                   *
*   Return Value: None.                                                        *
*******************************************************************************/
void createCiphertext(string&, char[]);

/*******************************************************************************
*   Function name: encrypt                                                     *
*   Description: Conducts the entire encryption algorithm and outputs.         *
*   Parameters: char keyBin[]: Import: The first key.                          *
*               char keyBin2[]: Import: The second key.                        *
*               char postIP1[]: Import: The key array after IP.                *
*               char postIP2[]: Import: The key array after IP.                *
*               char bitsetArray[]: Import: The bitset array.                  *
*               char preS[]: Import: The array before S Boxes.                 *
*               char postS[]: Import: The array after S Boxes.                 *
*               char preSwap[]: Import: The array before swap.                 *
*               char bitsetArray2[]: Import: The second key array.             *
*               char preIP1[]: Import: The array before IP-1.                  *
*               char ciphertext[]: Import: The ciphertext array.               *
*   Return Value: None.                                                        *
*******************************************************************************/
void encrypt(char[], char[], char[], char[], char[], char[], 
                    char[], char[], char[], char[], char[]);
                    
/*******************************************************************************
*   Function name: decrypt                                                     *
*   Description: Conducts the entire decryption algorithm and outputs.         *
*   Parameters: char keyBin[]: Import: The first key.                          *
*               char keyBin2[]: Import: The second key.                        *
*               char postIP1[]: Import: The key array after IP.                *
*               char postIP2[]: Import: The key array after IP.                *
*               char decryptedText[]: Export: The decrypted text.              *
*               char preS[]: Import: The array before S Boxes.                 *
*               char postS[]: Import: The array after S Boxes.                 *
*               char preSwap[]: Import: The array before swap.                 *
*               char bitsetArray2[]: Import: The second key array.             *
*               char preIP1[]: Import: The array before IP-1.                  *
*               char ciphertext[]: Import: The ciphertext array.               *
*   Return Value: None.                                                        *
*******************************************************************************/
void decrypt(char[], char[], char[], char[], char[], char[], 
                    char[], char[], char[], char[], char[]);

int main() {
    string key;
    char keyBin[10];
    char keyBin2[10];
    char postIP1[8];
    char postIP2[8];
    char bitsetArray[8];
    char preS[8];
    char postS[4];
    char preSwap[4];
    char bitsetArray2[8];
    char preIP1[4];
    char ciphertext[8];
    char decryptedText[8];
    
    regulateOutput(key, keyBin, keyBin2, postIP1, postIP2, bitsetArray,
                   preS, postS, preSwap, bitsetArray2, preIP1, ciphertext,
                   decryptedText);
    
    return 0;
}

/*******************************************************************************
*   Function name: menu                                                        *
*   Description: Displays menu choices, prompting the user to type a single    *
*                character as input in order to choose which menu option to    *
*                select. Once an option is executed, the menu appears again,   *
*                unless Q is chosen, which would quit the program. Input is not*
*                case sensitive.                                               *
*******************************************************************************/
char menu()
{
    char SelectedCharacter;
    cout << "\nPlease make a selection (E or D): " << endl;
    cout << "E)ncrypt" << endl;
    cout << "D)ecrypt" << endl;
    cout << "Q)uit" << endl;
    cin >> SelectedCharacter;
    return SelectedCharacter;
}

/*******************************************************************************
*   Function name: regulateOutput                                              *
*   Description: Regulates the output based on user input.                     *
*******************************************************************************/
void regulateOutput(string &key, char keyBin[], char keyBin2[], char postIP1[], 
                  char postIP2[], char bitsetArray[], char preS[], char postS[],
                    char preSwap[], char bitsetArray2[], char preIP1[],
                    char ciphertext[], char decryptedText[])
{   
    char inputCharacter = menu();
    
    while (inputCharacter!='Q' && inputCharacter!='q')
    {
        switch(inputCharacter)
        {
        case 'e':
        case 'E':
            generateKeys(key, keyBin, keyBin2);
            encrypt(keyBin, keyBin2, postIP1, postIP2, bitsetArray,
                   preS, postS, preSwap, bitsetArray2, preIP1, ciphertext);
            break;
        case 'd':
        case 'D':
            generateKeys(key, keyBin, keyBin2);
            decrypt(keyBin, keyBin2, postIP1, postIP2, decryptedText,
                   preS, postS, preSwap, bitsetArray2, preIP1, ciphertext);
            break;
        default:
            cout<<"\n";
            cout<<"Error: Invalid Entry"<<endl;
          break;
        }
      inputCharacter = menu();
    }
}

/*******************************************************************************
*   Function name: generateKeys                                                *
*   Description: Completes the steps in order to create the two keys.          *
*******************************************************************************/
void generateKeys(string &key, char keyBin[], char keyBin2[])
{
    createKey(key, keyBin);
    P10(keyBin);
    LS1(keyBin, keyBin2);
    P8(keyBin);
    LS2(keyBin2);
    P8(keyBin2);
    cout << "Key 1: ";
    for (int i = 0; i < 8; i++)
    {
        cout << keyBin[i];
    }
    cout << endl;
    cout << "Key 2: ";
    for (int i = 0; i < 8; i++)
    {
        cout << keyBin2[i];
    }
    cout << endl;
}

/*******************************************************************************
*   Function name: createKey                                                   *
*   Description: Asks user for binary input to create the base 10-digit key.   *
*                This function also error-checks to make sure that the input is*
*                10-digits long and contains only 0 and 1.                     *
*******************************************************************************/
void createKey(string &key, char keyBin[])
{
    cout << "Please enter a 10-digit key: ";
    cin >> key;
    if (key.size() > 10)
    {
       cout << "The input is too long." << endl;
       createKey(key, keyBin);
    }
    if (key.size() < 10)
    {
       cout << "The input is too short." << endl;
       createKey(key, keyBin);
    }
    for (int i = 0; i < 10; i++)
    {
        if (key[i] != '0' && key[i] != '1')
        {
            cout << "Please use 0 and 1 only." << endl;
            createKey(key, keyBin);
        }
    }
    for (int i = 0; i < 10; i++)
    {
        keyBin[i] = key[i];
    }
}

/*******************************************************************************
*   Function name: P10                                                         *
*   Description: Executes a permutation for all 10 bits in the array, resulting*
*                in a rearranged key.                                          *
*******************************************************************************/
// Normally: 3 5 2 7 4 10 1 9 8 6
// In array: 2 4 1 6 3  9 0 8 7 5 
void P10(char keyBin[])
{
    char temp[10];
    /*cout << "keyBin: ";                  ERROR CHECKING
    for (int i = 0; i < 10; i++)
    {
        cout << keyBin[i];
    }
    cout << endl;*/
    for (int i = 0; i < 10; i++)
    {
        temp[i] = keyBin[i];
    }
    keyBin[0] = temp[2];
    keyBin[1] = temp[4];
    keyBin[2] = temp[1];
    keyBin[3] = temp[6];
    keyBin[4] = temp[3];
    keyBin[5] = temp[9];
    keyBin[6] = temp[0];
    keyBin[7] = temp[8];
    keyBin[8] = temp[7];
    keyBin[9] = temp[5];
    
    /*cout << "temp: ";                      ERROR CHECKING
    for (int i = 0; i < 10; i++)
    {
        cout << temp[i];
    }
    cout << endl;
    
    cout << "new keyBin: ";
    for (int i = 0; i < 10; i++)
    {
        cout << keyBin[i];
    }
    cout << endl;*/
}

/*******************************************************************************
*   Function name: LS1                                                         *
*   Description: Executes a left shift for the left half and the right half of *
*                the key, placing the first digit at the end of each half.     *
*                This function also makes a copy of the key for use later.     *
*******************************************************************************/
void LS1(char keyBin[], char keyBin2[])
{
    char temp[10];
    /*cout << "keyBin: ";                    ERROR CHECKING
    for (int i = 0; i < 10; i++)
    {
        cout << keyBin[i];
    }
    cout << endl;*/
    for (int i = 0; i < 10; i++)
    {
        temp[i] = keyBin[i];
    }
    keyBin[0] = temp[1];
    keyBin[1] = temp[2];
    keyBin[2] = temp[3];
    keyBin[3] = temp[4];
    keyBin[4] = temp[0];
    keyBin[5] = temp[6];
    keyBin[6] = temp[7];
    keyBin[7] = temp[8];
    keyBin[8] = temp[9];
    keyBin[9] = temp[5];
    
    for (int i = 0; i < 10; i++)
    {
        keyBin2[i] = keyBin[i];
    }
    
    /*cout << "temp: ";                    ERROR CHECKING
    for (int i = 0; i < 10; i++)
    {
        cout << temp[i];
    }
    cout << endl;
    
    cout << "new keyBin: ";
    for (int i = 0; i < 10; i++)
    {
        cout << keyBin[i];
    }
    cout << endl;
    
    cout << "keyBin2: ";
    for (int i = 0; i < 10; i++)
    {
        cout << keyBin2[i];
    }
    cout << endl;*/
}

/*******************************************************************************
*   Function name: P8                                                          *
*   Description: Executes a permutation for the first 8 bits in the array,     *
*                resulting in a rearranged key. The array may still contain 10 *
*                digits, but only the first 8 are used in subsequent functions.*
*******************************************************************************/
// Normally: 6 3 7 4 8 5 10 9
// In array: 5 2 6 3 7 4  9 8
void P8(char keyBinary[])
{
    char temp[10];
    /*cout << "keyBin preP8: ";                ERROR CHECKING
    for (int i = 0; i < 10; i++)
    {
        cout << keyBinary[i];
    }
    cout << endl;*/
    for (int i = 0; i < 10; i++)
    {
        temp[i] = keyBinary[i];
    }
    keyBinary[0] = temp[5];
    keyBinary[1] = temp[2];
    keyBinary[2] = temp[6];
    keyBinary[3] = temp[3];
    keyBinary[4] = temp[7];
    keyBinary[5] = temp[4];
    keyBinary[6] = temp[9];
    keyBinary[7] = temp[8];
    keyBinary[8] = temp[8];
    keyBinary[9] = temp[9];
    
    /*cout << "temp: ";                     ERROR CHECKING
    for (int i = 0; i < 10; i++)
    {
        cout << temp[i];
    }
    cout << endl;
    
    cout << "new keyBin: ";
    for (int i = 0; i < 10; i++)
    {
        cout << keyBinary[i];
    }
    cout << endl;*/
}

/*******************************************************************************
*   Function name: LS2                                                         *
*   Description: Executes a left shift for the left half and the right half of *
*                the key, placing the first two digits at the end of each half.*
*******************************************************************************/
void LS2(char keyBin2[])
{
    char temp[10];
    /*cout << "keyBin2: ";                 ERROR CHECKING
    for (int i = 0; i < 10; i++)
    {
        cout << keyBin2[i];
    }
    cout << endl;*/
    for (int i = 0; i < 10; i++)
    {
        temp[i] = keyBin2[i];
    }
    keyBin2[0] = temp[2];
    keyBin2[1] = temp[3];
    keyBin2[2] = temp[4];
    keyBin2[3] = temp[0];
    keyBin2[4] = temp[1];
    keyBin2[5] = temp[7];
    keyBin2[6] = temp[8];
    keyBin2[7] = temp[9];
    keyBin2[8] = temp[5];
    keyBin2[9] = temp[6];
    
    /*cout << "temp: ";                     ERROR CHECKING
    for (int i = 0; i < 10; i++)
    {
        cout << temp[i];
    }
    cout << endl;
    
    cout << "new keyBin2: ";
    for (int i = 0; i < 10; i++)
    {
        cout << keyBin2[i];
    }
    cout << endl;*/
    
}

/*******************************************************************************
*   Function name: IP                                                          *
*   Description: Executes the initial permutation for each character of input, *
*                beginning the encryption process and resulting in a rearranged*
*                binary array. Function also creates copies of the array for   *
*                later use in the encryption process.                          *
*******************************************************************************/
// Normally: 2 6 3 1 4 8 5 7
// In array: 1 5 2 0 3 7 4 6
void IP(char bitSet1[], char copy[], char copy2[])
{
    char temp[8];
    
    for (int i = 0; i < 8; i++)
    {
        temp[i] = bitSet1[i];
    }
    bitSet1[0] = temp[1];
    bitSet1[1] = temp[5];
    bitSet1[2] = temp[2];
    bitSet1[3] = temp[0];
    bitSet1[4] = temp[3];
    bitSet1[5] = temp[7];
    bitSet1[6] = temp[4];
    bitSet1[7] = temp[6];
    
    for (int i = 0; i < 8; i++)
    {
        copy[i] = bitSet1[i];
    }
    for (int i = 0; i < 8; i++)
    {
        copy2[i] = bitSet1[i];
    }
}

/*******************************************************************************
*   Function name: EP                                                          *
*   Description: Performs an expansion and permutation of the input, resulting *
*                in an 8-bit array from a 4-bit input. As the function is      *
*                written (and as the program is designed), the input is        *
*                actually an 8-bit array, but only the last 4 bits are used.   *
*******************************************************************************/
// Normally: 4 1 2 3 2 3 4 1
// In array: 3 0 1 2 1 2 3 0
// Right Hf: 8 5 6 7 6 7 8 5
// In array: 7 4 5 6 5 6 7 4
void EP(char input[])
{
    char temp[8];
    
    for (int i = 0; i < 8; i++)
    {
        temp[i] = input[i];
    }
    
    input[0] = temp[7];
    input[1] = temp[4];
    input[2] = temp[5];
    input[3] = temp[6];
    input[4] = temp[5];
    input[5] = temp[6];
    input[6] = temp[7];
    input[7] = temp[4];
}

/*******************************************************************************
*   Function name: xor8                                                        *
*   Description: Performs an exclusive or operation on two 8-bit arrays, with  *
*                an 8-bit array as output. One of the inputs may be a 10-bit   *
*                array, but only the first 8 bits go through the operation.    *
*******************************************************************************/
void xor8(char input1[], char input2[], char output[])
{
    for (int i = 0; i < 8; i++)
    {
        if (input1[i] == input2[i])
            output[i] = '0';
        else
            output[i] = '1';
    }
}

/*******************************************************************************
*   Function name: s0s1                                                        *
*   Description: Uses 4 bits of input to output 2 bits. The output is chosen   *
*                based on two pre-written S-Box tables, which are written as   *
*                two-dimensional arrays. The input as designed here, is an     *
*                8-bit array, and the output is a 4-bit array. The first and   *
*                fourth bits of the input decide the row, and the second and   *
*                third bits of the input decide the column. The left half is   *
*                for S-Box 0 and the right half is for S-Box 1.                *
*******************************************************************************/
/*
bit1,bit4 specifies row
bit2,bit3 specifies column

S-Box 0             S-Box 1
   0  1  2  3       0  1  2  3
0  1  0  3  2    0  0  1  2  3
1  3  2  1  0    1  2  0  1  3
2  0  2  1  3    2  3  0  1  0
3  3  1  3  2    3  2  1  0  3

S-Box 0             S-Box 1
   00 01 10 11      00 01 10 11
00 01 00 11 10   00 00 01 10 11
01 11 10 01 00   01 10 00 01 11
10 00 10 01 11   10 11 00 01 00 
11 11 01 11 10   11 10 01 00 11
*/
void s0s1(char input[], char output[])
{
    int sbox0[4][4];
    sbox0[0][0] = 1;
    sbox0[0][1] = 0;
    sbox0[0][2] = 3;
    sbox0[0][3] = 2;
    sbox0[1][0] = 3;
    sbox0[1][1] = 2;
    sbox0[1][2] = 1;
    sbox0[1][3] = 0;
    sbox0[2][0] = 0;
    sbox0[2][1] = 2;
    sbox0[2][2] = 1;
    sbox0[2][3] = 3;
    sbox0[3][0] = 3;
    sbox0[3][1] = 1;
    sbox0[3][2] = 3;
    sbox0[3][3] = 2;
    
    int rowSB0;
    int colSB0;
    if (input[0] == '0' && input[3] == '0')
        rowSB0 = 0;
    else if (input[0] == '0' && input[3] == '1')
        rowSB0 = 1;
    else if (input[0] == '1' && input[3] == '0')
        rowSB0 = 2;
    else if (input[0] == '1' && input[3] == '1')
        rowSB0 = 3;
    
    if (input[1] == '0' && input[2] == '0')
        colSB0 = 0;
    else if (input[1] == '0' && input[2] == '1')
        colSB0 = 1;
    else if (input[1] == '1' && input[2] == '0')
        colSB0 = 2;
    else if (input[1] == '1' && input[2] == '1')
        colSB0 = 3;
    
    int selection0 = sbox0[rowSB0][colSB0];
    if (selection0 == 0)
    {
        output[0] = '0';
        output[1] = '0';
    }
    else if (selection0 == 1)
    {
        output[0] = '0';
        output[1] = '1';
    }
    else if (selection0 == 2)
    {
        output[0] = '1';
        output[1] = '0';
    }
    else if (selection0 == 3)
    {
        output[0] = '1';
        output[1] = '1';
    }
    
    int sbox1[4][4];
    sbox1[0][0] = 0;
    sbox1[0][1] = 1;
    sbox1[0][2] = 2;
    sbox1[0][3] = 3;
    sbox1[1][0] = 2;
    sbox1[1][1] = 0;
    sbox1[1][2] = 1;
    sbox1[1][3] = 3;
    sbox1[2][0] = 3;
    sbox1[2][1] = 0;
    sbox1[2][2] = 1;
    sbox1[2][3] = 0;
    sbox1[3][0] = 2;
    sbox1[3][1] = 1;
    sbox1[3][2] = 0;
    sbox1[3][3] = 3;
    
    int rowSB1;
    int colSB1;
    if (input[4] == '0' && input[7] == '0')
        rowSB1 = 0;
    else if (input[4] == '0' && input[7] == '1')
        rowSB1 = 1;
    else if (input[4] == '1' && input[7] == '0')
        rowSB1 = 2;
    else if (input[4] == '1' && input[7] == '1')
        rowSB1 = 3;
    
    if (input[5] == '0' && input[6] == '0')
        colSB1 = 0;
    else if (input[5] == '0' && input[6] == '1')
        colSB1 = 1;
    else if (input[5] == '1' && input[6] == '0')
        colSB1 = 2;
    else if (input[5] == '1' && input[6] == '1')
        colSB1 = 3;
    
    int selection1 = sbox1[rowSB1][colSB1];
    if (selection1 == 0)
    {
        output[2] = '0';
        output[3] = '0';
    }
    else if (selection1 == 1)
    {
        output[2] = '0';
        output[3] = '1';
    }
    else if (selection1 == 2)
    {
        output[2] = '1';
        output[3] = '0';
    }
    else if (selection1 == 3)
    {
        output[2] = '1';
        output[3] = '1';
    }
    /*cout << "S-Box Output: ";                   ERROR CHECKING
    for (int i = 0; i < 4; i++)
    {
        cout << output[i];
    }
    cout << endl;*/
}

/*******************************************************************************
*   Function name: P4                                                          *
*   Description: Executes a permutation for the first 4 bits in the array,     *
*                resulting in a rearranged array.                              *
*******************************************************************************/
// Normally: 2 4 3 1
// In array: 1 3 2 0
void P4(char input[])
{
    char temp[4];
    
    for (int i = 0; i < 4; i++)
    {
        temp[i] = input[i];
    }
    input[0] = temp[1];
    input[1] = temp[3];
    input[2] = temp[2];
    input[3] = temp[0];
}

/*******************************************************************************
*   Function name: xor4                                                        *
*   Description: Performs an exclusive or operation on two 4-bit arrays, with  *
*                a 4-bit array as output. One of the inputs may be an 8-bit    *
*                array, but only the first 4 bits go through the operation.    *
*******************************************************************************/
void xor4(char input1[], char input2[], char output[])
{
    for (int i = 0; i < 4; i++)
    {
        if (input1[i] == input2[i])
            output[i] = '0';
        else
            output[i] = '1';
    }
}

/*******************************************************************************
*   Function name: SW                                                          *
*   Description: Performs a swap or switch of the left and right half of the   *
*                arrays which resulted from the previous xor operation and the *
*                initial permutation, respectively. The four bits from the xor *
*                function continue as the "right half" and the last 4 bits of  *
*                the IP function continue as the "left half". The "right half" *
*                portion continues to the second EP function.                  *
*******************************************************************************/
// preSwap, postIP2, bitsetArray2
// 4 bits,  8 bits,  8 bits
// left to right, right to left, copy of left
void SW(char input1[], char input2[], char copyof1[])
{
    char temp[4];
    for (int i = 0; i < 4; i++)
    {
        temp[i] = input1[i];
    }
    
    copyof1[4] = input1[0];
    copyof1[5] = input1[1];
    copyof1[6] = input1[2];
    copyof1[7] = input1[3];
    // copyof1/bitsetArray2 done, goes to center as bitsetArray2 4-7
    // send preSwap to left side
    input1[0] = input2[4];
    input1[1] = input2[5];
    input1[2] = input2[6];
    input1[3] = input2[7];
    // input1/preSwap done, goes to left side as preSwap 0-3
    
    input2[4] = temp[0];
    input2[5] = temp[1];
    input2[6] = temp[2];
    input2[7] = temp[3];
    // input2/postIP2 done, goes to right side as postIP2 4-7
}

/*******************************************************************************
*   Function name: IP1                                                         *
*   Description: Executes the inverse of the initial permutation for each      *
*                character of input, completing the encryption process and     *
*                resulting in the 8-bit ciphertext, which is printed out.      *
*******************************************************************************/
// input 1: preIP1, input 2: postIP2, output: output
// Normally: 4 1 3 5 7 2 8 6
// In array: 3 0 2 4 6 1 7 5 
void IP1(char preIP1[], char postIP2[], char output[])
{
    char temp[8];
    
    for (int i = 0; i < 4; i++)
    {
        temp[i] = preIP1[i];
    }
    for (int i = 4; i < 8; i++)
    {
        temp[i] = postIP2[i];
    }
    
    output[0] = temp[3];
    output[1] = temp[0];
    output[2] = temp[2];
    output[3] = temp[4];
    output[4] = temp[6];
    output[5] = temp[1];
    output[6] = temp[7];
    output[7] = temp[5];
}

/*******************************************************************************
*   Function name: createCipherNumber                                          *
*   Description: Sets the number of times that the decryption algorithm will   *
*                occur based on user input of number of ciphertexts.           *
*******************************************************************************/
void createCipherNumber(string &input, int &cipherNum)
{
    cout << "How many sets of ciphertext will be decrypted? " << endl;
    cin >> input;
    
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] != '0' && input[i] != '1' && input[i] != '2' && 
            input[i] != '3' && input[i] != '4' && input[i] != '5' &&
            input[i] != '6' && input[i] != '7' && input[i] != '8' &&
            input[i] != '9')
        {
            cout << "Please use numbers only." << endl;
            createCipherNumber(input, cipherNum);
        }
    }
    stringstream ss (input);
    ss >> cipherNum;
    //cout << cipherNum << endl;
}

/*******************************************************************************
*   Function name: createCiphertext                                            *
*   Description: Sets the number of times that the decryption algorithm will   *
*                occur based on user input of number of ciphertexts.           *
*******************************************************************************/
void createCiphertext(string &input, char ciphertext[])
{
    cout << "8-digit ciphertext: ";
    cin >> input;
    if (input.size() > 8)
    {
       cout << "The input is too long." << endl;
       createCiphertext(input, ciphertext);
    }
    if (input.size() < 8)
    {
       cout << "The input is too short." << endl;
       createCiphertext(input, ciphertext);
    }
    for (int i = 0; i < 8; i++)
    {
        if (input[i] != '0' && input[i] != '1')
        {
            cout << "Please use 0 and 1 only." << endl;
            createCiphertext(input, ciphertext);
        }
    }
    for (int i = 0; i < 8; i++)
    {
        ciphertext[i] = input[i];
    }
}

/*******************************************************************************
*   Function name: encrypt                                                     *
*   Description: Conducts the entire encryption algorithm and outputs.         *
*******************************************************************************/
void encrypt(char keyBin[], char keyBin2[], char postIP1[], 
             char postIP2[], char bitsetArray[], char preS[], char postS[],
             char preSwap[], char bitsetArray2[], char preIP1[],
             char ciphertext[])
{
    string plaintext;
    
    cin.ignore();
    cout << "Please enter text to be encrypted: ";
    
    getline(cin, plaintext);
    int plaintextSize = plaintext.size();
    char *textArray = new char [plaintext.size()];
    memcpy(textArray, plaintext.c_str(), plaintextSize);
    
        
    // Error checking
    /*for (int i = 0; i < plaintextSize; i++)
    {
        // textArray[i] = plaintext[i];
        cout << textArray[i];
    }
    cout << endl;*/
    
    // Here begins output of Ciphertext
    for (int i = 0; i < plaintextSize; i++)
    {
        string bitsetString = bitset<8>(textArray[i]).to_string();
        for (int j = 0; j < 8; j++)
        {
            bitsetArray[j] = bitsetString[j];
            // cout << bitsetArray[j];   ERROR CHECKING
        }
        IP(bitsetArray, postIP1, postIP2);
        EP(bitsetArray);
        xor8(bitsetArray, keyBin, preS);
        s0s1(preS, postS);
        P4(postS);
        xor4(postIP1, postS, preSwap);
        SW(preSwap, postIP2, bitsetArray2);
        EP(bitsetArray2);
        xor8(bitsetArray2, keyBin2, preS);
        s0s1(preS, postS);
        P4(postS);
        xor4(preSwap, postS, preIP1);
        IP1(preIP1, postIP2, ciphertext);
        cout << "Ciphertext: ";
        for (int i = 0; i < 8; i++)
        {
            cout << ciphertext[i];
        }
        cout << endl;
        // cout << bitset<8>(textArray[i]) << endl; ERROR CHECKING
    }
}

/*******************************************************************************
*   Function name: decrypt                                                     *
*   Description: Conducts the entire decryption algorithm and outputs.         *
*******************************************************************************/
void decrypt(char keyBin[], char keyBin2[], char postIP1[], 
             char postIP2[], char decryptedText[], char preS[], char postS[],
             char preSwap[], char bitsetArray2[], char preIP1[],
             char ciphertext[])
{
    string input;
    string input2;
    string finalText;
    cin.ignore();
    int cipherNum;
    createCipherNumber(input, cipherNum);
    bitset<8> actualBits;
    long bitsetLong;
    char finalChar;
    
    // Here begins output of decrypted text
    // cout << "Decrypted text: " << endl;
    for (int i = 0; i < cipherNum; i++)
    {
        cin.ignore();
        cout << "Please enter ciphertext to be decrypted. " << endl;
        createCiphertext(input2, ciphertext);
        IP(ciphertext, postIP1, postIP2);
        EP(ciphertext);
        xor8(ciphertext, keyBin2, preS);
        s0s1(preS, postS);
        P4(postS);
        xor4(postIP1, postS, preSwap);
        SW(preSwap, postIP2, bitsetArray2);
        EP(bitsetArray2);
        xor8(bitsetArray2, keyBin, preS);
        s0s1(preS, postS);
        P4(postS);
        xor4(preSwap, postS, preIP1);
        IP1(preIP1, postIP2, decryptedText);
        cout << "Decrypted text: ";
        for (int i = 0; i < 8; i++)
        {
            cout << decryptedText[i];
        }
        cout << endl;
        string bitsetString;
        for (int i = 0; i < 8; i++)
        {
            bitsetString += decryptedText[i];
        }
        actualBits = bitset<8>(bitsetString);
        bitsetLong = actualBits.to_ulong(); 
        finalChar = static_cast<char>(bitsetLong);
        cout << "Decrypted char: " << finalChar << endl;
        finalText += finalChar;
        cout << "Message: " << finalText << endl;
        // cout << bitset<8>(textArray[i]) << endl; ERROR CHECKING
    }
}
