// ___________________________________________________ READ ME ___________________________________________________ //
/*
NOTE: this comment block contains the same information as the file README.txt

My Details:
Name: Cooper Brown
ID: 3324706
Date: 29/04/19

Name of .c file: Cooper_Brown_Assignment1.c
Note: There are a lot of other files in this git folder. All the irrelevant ones should be contained in a separate folder

Instructions for use:
1. Place the text block that needs to be processed into the file inputFile.txt
2. Format keyFile.txt for the operation you want to perform
    a. The first line should be either the word 'encode' or 'decode'
    b. place in the second line 'key: ' (space is important) followed by either
        i. a number from 0-26 (representing a rotation key)
        ii. a series of letters e.g. 'stuvwghijklmnoabcdefpqrxyz' where s = a, t = b etc.
            (This represents a substitution key)
        iii. nothing (if you want to decode without a key)
            Note: this option only works for decryption
            Note: This will try to decrypt the file using caeser then substitution if the caeser fails. 
       The key type will be automatically detected and the task selected based on this

Task Number Key:
Task1 = encryption using caesar key
Task2 = decryption using caesar key
Task3 = encryption using substitution key
Task4 = decryption using substitution key
Task5 = decryption of caesar cypher without key
Task6 = decryption of substitution cypher without key


keyFile.txt formatting examples:
Task1:
encode
key: 21

Task2:
decode
key: 14

Task3:
encode
key: stuvwghijklmnoabcdefpqrxyz

Task4:
decode
key: stuvwghijklmnoabcdefpqrxyz

Task5:
decode
key: 

Task6:
decode
key: 

*/






// ___________________________________________________ IMPORTED LIBRARIES ___________________________________________________ //
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // contains tolower() and toupper() functions
#include <string.h>

// ___________________________________________________ FUNCTION PROTOTYPES ___________________________________________________ //

char getTaskAndKey(char *rotationKey, char *substitutionKey);

char task1and2(char rotationKey);
char task3and4(char *originalLetters, char *substituteKey);
char task5();
char task6(char *originalLetters);

char applyRotationKeyToCharacter(char inputCharacter, char key);

char get2DArrayFromFile(char inputText[2100][100], char *fileName);

void clearArray(char array[2100][100], int words, int characters);

char crossReference(char *word, char wordBank[2100][100], int maxWords);


// ___________________________________________________________ MAIN _________________________________________________________ //
int main()
{
    // _____VARIABLE INITIALISATION_____
    char taskNumber = 0; // holds a number that is used to choose which task will be performed

    char rotationKey = 0; // used to hold a number from 0-26 that will represent a caesar cypher key
    char originalLetters[] = "abcdefghijklmnopqrstuvwxyz"; // an array holding the letters of the alphabet. 
    char substitutionKey[27]; // an empty array that will contain an ordered list of letters that the letters in the above array will be substituted with

    char successful = 0; // a boolean variable used to hold the return status of the tasks. 1 = successful and 0 = not successful

    // _____PROCESSING_____
    taskNumber = getTaskAndKey(&rotationKey, substitutionKey); // gets the tasknumber and the needed key from the function getTaskAndKey

    switch (taskNumber) // switch case to choose between tasks based on tasknumber
    {
        case 1: // This case will encrypt the text using a caesar cypher with given key
            printf("Attempting to complete task %d...\n", taskNumber); // informs the user about what task is being performed
            successful = task1and2(rotationKey); // attempts to perform the encryption. If the process fails, successful becomes 0
            break;
        case 2: // This case will decrypt the text using a caesar cypher with given key
            printf("Attempting to complete task %d...\n", taskNumber);
            successful = task1and2(-1*rotationKey); // attempts to perform the encryption. Key is negative because letters need to be rotated the other way to get back to what they were before the original encrypion
            break;
        case 3: // this case will encrypt the text using a substitution key
            printf("Attempting to complete task %d...\n", taskNumber);
            successful = task3and4(originalLetters, substitutionKey); // attempts to perform encryption by substituting the letters of originalLetters with letters of substitutionKey
            break;
        case 4: // this case will decrypt the text using a substitution key
            printf("Attempting to complete task %d...\n", taskNumber);
            successful = task3and4(substitutionKey, originalLetters); // same as case 3, except parameters swapped so encryption is 'undone'
            break;
        case 7: // this case will initially attempt a rotation cypher, and if a satisfactory result is not achieved it will attempt to crack it as though it was substitution
            taskNumber = 5; // initially attempts the rotation decryption
            printf("Attempting to complete task %d...\n", taskNumber);
            successful = task5(); // task5 will perform the necessary rotations and spelling checks
            if (successful == 0) // if task5 fails, substitution decryption is attempted
            {
                printf("Task %d failed\n", taskNumber); // informs the user that the caesar decryption has failed
                taskNumber = 6;
                printf("Attempting to complete task %d...\n\n", taskNumber);
                successful = task6(originalLetters); // task 6 will perform the substitution decryption
            }
            break;
    }
    if (successful) // if the performed tasks were successful, this is indicated and the results are printed to the screen
    {
        printf("Task %d has been completed.\nBelow is a copy of the contents of outputFile.txt\n\n", taskNumber);
        FILE *outputFile;
        outputFile = fopen("outputFile.txt", "r"); // opens the output file so the contents can be printed to the screen
        // the file's existance does not need to be checked as in order to get to this state it must have existed in the first place
        char fileCharacter;
        while (fscanf(outputFile, "%c", &fileCharacter) == 1) // this loop prints every character in the file as is
        {
            printf("%c", fileCharacter);
        }
        fclose(outputFile);
    }
    // if the task was not successful, the user is informed of this. More specific error details would have already been provided within the task functions.    
    // This is just a final prompt to inform the user that the desired task has failed
    else
        printf("No task could be completed.\n");

    return 0;
}

// _______________________________________________________ FUNCTIONS _________________________________________________________ //






/*  This function serves the purpose of determining the operation that the user wants to perform.
    Input:
    1. Location for where the rotation key will be stored
    2. The location for where the substitution key will be stored
    
    Return:
    1. The number of the task to be performed (0, 1, 2, 3, 4 or 7).
    2. The location of the rotation or substitution key will be modified to a correct value
    
    Functionality:
    1. Opens keyFile.txt
    2. grabs the wanted operation type(encode/decode) from the first line of the file.
    3. input matching through scanf() determines the type of key the user has entered.
    4. The data from steps 3 and 4 are used to select the desired task

    Limitations:
    1. If the key in the file is a number larger than 2 digits e.g. 248, only the first 2, (i.e. 24) will be the number that is read, and the 
       user is not informed that the larger number has not been processed. This is due to the fact that rotationKey points to a char variable
       where only numbers under 128 can be stored
*/
char getTaskAndKey(char *rotationKey, char *substitutionKey)
{
    // ____ VARIABLE INITIALISATION ____
    FILE *keyFile; // used to hold a pointer to the file being read from
    char command[100]; // this array is used to hold the text typed in the first line of the program
    char taskNumber = 0;
    fpos_t position; // this is an object used to indicate the read position of the file. It is used to re-read lines that have already been read
    
    // ____ FUNCTION PROCESSING ____
    keyFile = fopen("keyFile.txt", "r"); // 

    if (keyFile == NULL) // this statement checks if the file exists, and if not, exits to avoid crashes later on and give the user information about why the program is not working
    {
        printf("Error: keyFile.txt is not in the current directory\n");
        return 0;
    }

    fscanf(keyFile, "%s", command); // the first line of the file holding the command (encode/decode) is read
    fgetpos(keyFile, &position); // the current read position (start of 2nd line) is remembered so that the program can read from this point later
    // this series of selections is used to determine the operation type
    if (strcmp(strlwr(command),"encode") == 0)
    {
        if (fscanf(keyFile, "%*[^:]%*2c%2d", rotationKey) == 1)  // reads the 2nd line of the file, ignoring 'key: ' and saving the key into the pointer parsed to the function if its format is correct
            if (*rotationKey > 26 || *rotationKey < 0) // if the key is out of range, the user needs to be informed
                printf("Error: key is out of range");
            else
                taskNumber = 1; // remembers the taskNumber. The variable is later parsed out of the function and used to select the task in MAIN
        else 
        {
            fsetpos(keyFile, &position); // the file reading position is set to the start of 2nd line so that it can be read again
            if (fscanf(keyFile, "%*[^:]%*2c%26c", substitutionKey) == 1) // re-reads the 2nd line, saving the key to the pointer if a valid one is present
                taskNumber = 3;
            else // prompt to inform the user of what went wrong. taskNumber is defined as 0, so it does not need to change if something goes wrong
                printf("Error: cannot encode without a valid key.\n");
        }
        
    }
    else if (strcmp(strlwr(command),"decode") == 0)// this selection is very similar to above, but selects the task numbers for decryption instead
    {
        if (fscanf(keyFile, "%*[^:]%*2c%2d", rotationKey) == 1)
            if (*rotationKey > 26 || *rotationKey < 0)
                printf("Error: key is out of range");
            else
                taskNumber = 2;
        else 
        {
            fsetpos(keyFile, &position);
            if (fscanf(keyFile, "%*[^:]%*2c%26c", substitutionKey) == 1)
                taskNumber = 4;
            else // if a valid key could not be detected, then the task is set to try and decrypt the file without one. The user is informed of this assumption
            {
                printf("Could not detect a valid key. Attempting to decode without one...\n");
                taskNumber = 7;
            }
        }
            
    }
    else // if the first line is not "encode" or "decode" then the user is informed of this and taskNumber remains at 0
        printf("1st line (the command header) of keyFile.txt is formatted incorrectly.\nIt should either be 'encode' or 'decode'.\n");
    //fclose(keyFile); 
    // ok for some reason my laptop throws segmentation faults when I try to close a file but the exact same code works fine on my desktop. 
    // I have left out fclose() wherever possible to try and minimise the chances of the code failing on other machines. 
    return taskNumber;
}

/* This function performs tasks 1 and 2, which is encryption/decryption of the input file using the key provided. 
    If the key is positive, encryption is performed while if the key is negative, decryption is performed

    Input:
    1. The key that will be used to rotate the characters in the file

    Return:
    1. Boolean variable where 1 means that the operation was successfull and 0 means it was not
    2. outputFile.txt is modified

    Functionality:
    1. Check files exist and open them
    2. Loop through every character in inputFile.txt
    3. in this loop, rotate the character and write it to outputFile.txt

    Limitations:
    1. The function only writes uppercase letters to the file (although this is required by specification)
    2. There is no checking of how large the files are, and the function may continue for an unreasonable amount of time    
        before it is manually stopped
*/
char task1and2(char rotationKey)
{
    //______INITIALISATION______
    char errorFlag = 0; // this flag indicates whether either of the required files exist 0 = exist, 1 = doesn't exist
    char inputCharacter; // used to hold the 
    FILE *inputFile, *outputFile; // used to hold pointers to the files being read from/written to

    //______FUNCTION PROCESSING______
    inputFile = fopen("inputFile.txt", "r");
    outputFile = fopen("outputFile.txt", "w");

    if (inputFile == NULL) // these selections test if the files exist. If they do not, a flag is set to true
    {
        printf("Error: inputFile.txt is not in the current directory");
        errorFlag = 1; // having the flag may seem useless but if both files are missing I want an error message for each.
    }
    if (outputFile == NULL)
    {
        printf("Error: outputFile.txt is not in the current directory");
        errorFlag = 1;
    }
    if (errorFlag == 1) // if the files do not exist then the function halts execution before crashes occur
        return 0;


    // this loop goes through every character in the input file, rotates it and then writes it to the output file. 
    // This way no array is needed and only one loop is required to perform the operation
    while (fscanf(inputFile, "%c", &inputCharacter) == 1) 
    {
        inputCharacter = applyRotationKeyToCharacter(inputCharacter, rotationKey); // the key is rotated using the key parsed in 
        if (inputCharacter >= 97 && inputCharacter <= 122) // this selection ensures that the output to the file will be in uppercase (to meet specifications)
            inputCharacter -= 32;
        fprintf(outputFile, "%c", inputCharacter); // the rotated character is written to the file
    }
    
    fclose(inputFile);
    fclose(outputFile);
    return 1;
}



/* This function performs tasks 3 and 4, where are encryption/decryption of an input file using the key provided
   In the file, the letter contained in the string 'originalLetters' will be replaced with its respective letter in the string 'substituteLetters'
   In order to decrypt, these strings can be parsed in the opposite way to 'undo' the encryption operation performed by the key

   Input:
   1. A string containing all of the letters in the alphabet
   2. A string containing letters that the respective letters of originalLetters in the text will be substituted with

   Return:
   1. A boolean variable where 1 means that the task was successful and 0 means that it was not
   2. outputFile.txt is modified

   Functionality:
   1. Checks for the existance of relevant files and opens them
   2. Loops through every character of the input file
   3. In this loop, the new character is determined by searching for the input character in originalLetters and assigning the corresponding value in substituteLetters
   4. This new character is turned to upper case and written to outputFile.txt

   Limitations:
   1. An unreasonably large inputFile is not tested for and no prompts will be given to the user surrounding this
   2. Function only writes to the file uppercase letters and the original casing of the input is not retained (neccessary for specifications)
*/
char task3and4(char *originalLetters, char *substituteLetters)
{
    //______INITIALISATION______
    char inputCharacter; // holds the character of the input file being processed
    FILE *inputFile, *outputFile; // holds pointers to the relevant file locations

    //______FUNCTION PROCESSING______
    inputFile = fopen("inputFile.txt", "r");
    outputFile = fopen("outputFile.txt", "w");

    if (inputFile == NULL) // checks if the file exists so if not, execution can be halted prior to an error
    {
        printf("Error: inputFile.txt is not in the current directory");
        return 0;
    }
    if (outputFile == NULL)
    {
        printf("Error: outputFile.txt is not in the current directory");
        return 0;
    }

    while (fscanf(inputFile, "%c", &inputCharacter) == 1) // loops through each character of the file. Since there are no arrays holding the input this one loop saves processing time
    {
        for (int index = 0; index < 26; index++) // searches through each of the letters in the input string originalLetters. Index is used to access both of the arrays
        {
            if (inputCharacter == originalLetters[index]) // if the input character matches the letter in the first array, then it is assigned the corresponding value of the other
            {
                inputCharacter = substituteLetters[index];
                break; // process broken as since the letter is found the rest do not need to be searched through
            }
            else if (inputCharacter == toupper(originalLetters[index])) // if input character is uppercase then it is assigned its correspondint uppercase value
            {
                inputCharacter = toupper(substituteLetters[index]);
                break;
            }
        }
        if (inputCharacter >= 97 && inputCharacter <= 122) // ensures that the character written to outputFile.txt is uppercase
            inputCharacter -= 32;
        fprintf(outputFile, "%c", inputCharacter);
    }
    fclose(inputFile); // these file closes are necessary as outputFile is re-opened later
    fclose(outputFile);
    return 1;
}




/* This function attempts to perform decryption by assuming the input text was encoded with a caeser cypher
    
    Input:
    1. No direct input except that from inputFile.txt

    Return:
    1. A boolean value held in a char where 1 means the cypher was cracked and 0 means it was not
    2. outputFile.txt may get written to

    Functionality:
    1. calls functions to get 2D arrays of the word bank and input. Halts execution if something goes wrong with this process
    2. Loops through every possible key from 0-26
    3. In this loop, every character in the input array is rotated by the key
    4. Then, still in the loop, each word in the input array is spell checked against the wordbank, counting the number of matches
    5. If greater than 50% of the words match, the key is considered correct and task1and2 is performed using the found key

    Limitations:
    1. The 2D arrays processed have a maximum size of [2100][100] (including the wordbank, which may result in less matches being found than would actually be possible)
    2. Inefficient processing as same file is accessed more than once to get the same information (because im too lazy to write a loop)
    4. The first match over 50% is assumed correct, instead of assuming that the key with the most matches is correct. This is to allow a substitution decryption
        to be attempted if a fail is suspected, however may lead to the correct key being skipped over
*/
char task5()
{
    //______INITIALISATION______
    int maxWords = 2100; // remembers the maximum number of words that can be held by the arrays of this function
    int maxCharacters = 100; // remembers the maximum number characters per word that can be held by the arrays of this function
    char inputText[maxWords][maxCharacters]; // holds the contents of the input file
    char inputTextOriginal[maxWords][maxCharacters]; // an original copy of the input file that does not get modified. The key is applied to the contents of this array since the key is for the original text
    char wordBank[maxWords][maxCharacters]; // holds the contents of the wordbank
    // the above 2D arrays are cleared by the below funtions so that they all contain 0s and no previous values are carried over
    clearArray(inputText, maxWords, maxCharacters);
    clearArray(inputTextOriginal, maxWords, maxCharacters);
    clearArray(wordBank, maxWords, maxCharacters);

    char errorFlag = 0; // flag to indicate whether an error has occured or not. It is used to ensure that all relevant error messages get displayed

    int hit = 0, noHit = 0; // stores the number of times a match with the wordbank was found, and the times that it wasn't found

    if (get2DArrayFromFile(inputText, "inputFile.txt") == 0) // if the file does not exist, the called function will return 0 signalling an error, which is indicated
    {
        printf("Error: inputFile.txt is not in the current directory");
        errorFlag = 1;
    }
    get2DArrayFromFile(inputTextOriginal, "inputFile.txt"); // strcpy() cannot used as the array is 2D. Another alternative would be an embedded loop, however this function already exists

    if (get2DArrayFromFile(wordBank, "20k.txt") == 0) // obtains the wordbank and signals any potential errors
    {
        printf("Error: 20k.txt is not in the current directory");
        errorFlag = 1;
    }
    if (errorFlag == 1) // having the flag may seem useless but if both files are missing I want an error message for each before the error is indicated.
        return 0;


    for (int key = 0; key < 26; key++) // every key needs to be tested
    {
        hit = 0; // resets hit and noHit for each key/combinbination
        noHit = 0;
        // these embedded loops rotate each character in the input array
        for (int word = 0; word < maxWords; word++)
        {
            for (int letter = 0; letter < maxCharacters; letter++)
            {
                // The key is applied to the original input. inputText can be reassigned as we have this intact copy saved
                inputText[word][letter] = applyRotationKeyToCharacter(inputTextOriginal[word][letter], (-1*key)); 
            }
        }


        // this loop cross references a word from input with every word in wordbank
        for (int word = 0; word < maxWords; word++)
        {
            if (inputText[word][0] == 0) // ends the search if the word is empty (meaning all words have been searched). This saves unnecessary processing and therefore time
                break;
            if (crossReference(inputText[word], wordBank, maxWords) == 1) // this function determines if a match was found
                hit++; // remembers the times a match was found
            else
                noHit++; // remembers the times no match was found
            
        }

        // this formula determines if greater than 50% of the words match. This number is arbitrary, but I think it is low enough to catch any error but too high to be accidentally be triggered
        if ((hit*1.0)/(hit+noHit) > 0.5) 
        {
            printf("The key used to originally ENCODE the text is %d\n\n", key); // the key used to originally encode the input and the key used to decode are two different things
            task1and2((-1)*key); // this function will actually perform the rotations on the input file and store it in the output, since all that has been done is the key has been determined
            return 1; // the function is exited early if a match is suspected
        }
    }
    return 0;
}






/* This function performs decryption assuming the input was encoded with a substitution cypher. 
    Note that it is not very good, and only correctly determines around 30% of the substitute characters

    Input:
    1. A pointer to a string of 26 letters representing the letters to be substituted

    Output:
    1. A boolean flag stored in a char where 1 means the task was completed and 0 means an error occured
    2. outputFile.txt may get modified

    Funtionality:
    1. Obtains arrays containing the input file and word bank (even though this is not used) and informs user of any errors that occured in this process
    2. Counts the number of times each relevant character in the file occurs
    3. Sorts these frequencies
    4. Calls a function to substitute the relative letter frequencies of those in the file with those known for the english language

    Limitations:
    1. The 2D arrays worked with have a maximum size of [2100][100]
    2. Inefficient processes as wordbank is never used
    3. The key printed is not in alphabetical order so takes longer to read through
*/
char task6(char *originalLetters)
{
    //______INITIALISATION______
    int maxWords = 2100; // remembers the maximum number of words that can be held by the arrays of this function
    int maxCharacters = 100; // remembers the maximum number characters per word that can be held by the arrays of this function
    char inputText[maxWords][maxCharacters]; // holds the contents of the input file
    char inputTextOriginal[maxWords][maxCharacters]; // an original copy of the input file that does not get modified. The key is applied to the contents of this array since the key is for the original text
    char wordBank[maxWords][maxCharacters]; // holds the contents of the wordbank
    // the above 2D arrays are cleared by the below funtions so that they all contain 0s and no previous values are carried over
    clearArray(inputText, maxWords, maxCharacters);
    clearArray(inputTextOriginal, maxWords, maxCharacters);
    clearArray(wordBank, maxWords, maxCharacters);

    char errorFlag = 0; // flag to indicate whether an error has occured or not. It is used to ensure that all relevant error messages get displayed

    // stores a string of characters by their frequency. Will be used to determine what letters in the input will be substituted with
    char standardLetterFrequencies[26] = "etaoinsrhdlucmfywgpbvkxqjz"; 
    int letterCounts[26]; // empty array that will store the numbers each of the above letters occur in the input
    for (int index = 0; index < 26; index++) // since clearArray only works for 2D arrays, this array needs to be cleared manually
        letterCounts[index] = 0;

    //______FUNCTION PROCESSING______

    if (get2DArrayFromFile(inputText, "inputFile.txt") == 0) // if the file does not exist, the called function will return 0 signalling an error, which is indicated
    {
        printf("Error: inputFile.txt is not in the current directory");
        errorFlag = 1;
    }
    get2DArrayFromFile(inputTextOriginal, "inputFile.txt"); // strcpy() cannot used as the array is 2D. Another alternative would be an embedded loop, however this function already exists

    if (get2DArrayFromFile(wordBank, "20k.txt") == 0) // obtains the wordbank and signals any potential errors
    {
        printf("Error: 20k.txt is not in the current directory");
        errorFlag = 1;
    }
    if (errorFlag == 1) // having the flag may seem useless but if both files are missing I want an error message for each before a failure is indicated.
        return 0;

    // these first two loops ensure that inside them each of the characters in the input array are accessed at some point in time
    for (int word = 0; word < maxWords; word++)
        {
            for (int letter = 0; letter < maxCharacters; letter++)
            {   
                // this inner loop goes through each letter in the standardLetterFrequencies
                for (int elementOfLetterFrequencies = 0; elementOfLetterFrequencies < 26; elementOfLetterFrequencies++)
                {
                    // this selection ensures that letters are turned into lowercase before they are compared with the lowercase letter frequency array
                    if (inputText[word][letter] >= 65 && inputText[word][letter] <= 90) 
                        inputText[word][letter] += 32;
                    if (standardLetterFrequencies[elementOfLetterFrequencies] == inputText[word][letter]) // this selection adds 1 to the frequency count of any found letter
                    {
                        letterCounts[elementOfLetterFrequencies] += 1;
                    }
                }
            }
        }

    //______MORE INITIALISATION______

    // highestIndex stores the index of the highest number in the search. 
    // startIndex stores where the sort will start from each iteration of the loop. This ensures that the already sorted values are not mixed with the unsorted
    // tempi is a temporary integer used to swap two other integers
    int highestIndex = 0, startIndex = 0, tempi = 0; 

    // tempc is a temporary char used to swap two other chars. 
    // inputLetterFrequencies holds an editable copy of standardLetterFrequencies. It is to be sorted
    char tempc, inputLetterFrequencies[27]; 
    strcpy(inputLetterFrequencies, standardLetterFrequencies); // makes inputLetterFrequencies a copy of standardLetterFrequencies

    //______MORE PROCESSING______
    // this loop is a sort (I'm pretty sure it is a selection sort). 
    // Its purpose is to sort the frequencies in letterCounts and at the same time sort inputLetterFrequencies so the two arrays 'line up'
    // this sorted array can then be substituted with the array of known frequencies to decode the input
    for (int startIndex = 0; startIndex < 26; startIndex++)
    {
        highestIndex = startIndex; // at the time this iteration starts, the highest element is also the first element as none have been scanned yet
        for (int index = startIndex+1; index < 26; index++) // loops through the array, starting at the next unscanned number (startIndex+1) to find the index of the highest number
        {
            if (letterCounts[index] > letterCounts[highestIndex]) // this selection remembers the index of the highest number
                highestIndex = index;
        }
        // this code will swap the highest element with the element in the position in which it should go
        tempi = letterCounts[startIndex];
        letterCounts[startIndex] = letterCounts[highestIndex];
        letterCounts[highestIndex] = tempi;

        tempc = inputLetterFrequencies[startIndex]; // the letters of inputLetterFrequencies are also swapped so that the program knows what frequency number corresponds to which letter
        inputLetterFrequencies[startIndex] = inputLetterFrequencies[highestIndex];
        inputLetterFrequencies[highestIndex] = tempc;
    }
         
    printf("Below is the calculated key for this task\n");
    for (int index = 0; index < 26; index++) // this loop serves the purpose of printing the key substitutions to the screen
        printf("%c --> %c\n", standardLetterFrequencies[index], inputLetterFrequencies[index]);
    printf("This key was used to ENCODE the data to its encrypted state.\nThe key used by this program to decrypt the text has the arrow inverted\ni.e. a --> b becomes b --> a\n\n");

    // the called function will actually modify the values of inputFile and store them in outputFile, as all this function does is determine the key
    task3and4(inputLetterFrequencies, standardLetterFrequencies); // parameters are passed in the other way to 'undo' the encryption
    return 1;
}







/* The purpose of this function is to shift the input character to the right by key times and return the result
    Input:
    1. a char value of the character to shift
    2. the key (from 0-25) that the character will be shifted by

    Return:
    1. A char value of the shifted character

    Functionality:
    1. If the letter is uppercase, it turns it into the lowercase version
    2. If the character is a letter, the key is added to it
    3. The boundaries are checked to make sure the key is still a letter. If not, the overhang is added to the start to make it one

    Limitations:
    1. The function does not return uppercase letters. This simplification is necessary as the word bank the shifted words are compared to is in lowercase
       regardless, this is still a limitation of the function
*/
char applyRotationKeyToCharacter(char inputCharacter, char key)
{
    //______NO INITIALISATION______

    //______FUNCTION PROCESSING______
    if (inputCharacter >= 65 && inputCharacter <= 90) // turns the input into lowercase so output is in lowercase
        inputCharacter += 32;
    
    // below selection works lowercase characters only
    if (inputCharacter >= 97 && inputCharacter <= 122) // this selection ensures that only letters are shifted. All puntuation is untouched
    {
        inputCharacter += key;
        if (inputCharacter > 122) // this selection checks if the key is out of range, and puts it back in range if this is the case. If this is not done, letters can become punctuation
            inputCharacter = 96 + (inputCharacter - 122); // the 'overhang' (inputCharacter - 122), is added to the start of the correct range
        else if (inputCharacter < 97)
            inputCharacter = 123 - (97 - inputCharacter); // the opposite is done if the key is negative the character gets pushed out the other side of the range
    }
    
    /* The below comment block is to work with uppercase. It is commented out since all input to the function is transformed to lowercase at the start
    // for upper case characters
    else if (inputCharacter >= 65 && inputCharacter <= 90)
    {
        inputCharacter += key;
        if (inputCharacter > 90)
            inputCharacter = 64 + (inputCharacter - 90);
        else if (inputCharacter < 65)
            inputCharacter = 91 - (65 - inputCharacter);
    }
    */

    return inputCharacter;
}






/* This function is designed to get a 2D array of all the letters and words contained in the file parsed to it
    Input:
    1. The location of where this 2D array is to be stored
    2. A string containing the path of the file to access

    Return:
    1. A boolean 1 if the function ran successfully, and a 0 if something went wrong
    2. The values of the 2D array passed in are modified.

    Functionality:
    1. Checks the file exists and opens it
    2. Loops through every character of the file, adding it to a the array
    3. If the character is a space, or a newline character, then a word is completed and a new one started 

    Limitations:
    1. The file will only save the first 2100 words of the file
    2. If a word is more than 100 characters, a buffer overflow may occur.
    3. Newline characters are lost from the input file and will not appear in the program's final output
*/
char get2DArrayFromFile(char inputText[2100][100], char *fileName)
{
    // _____INITIALISATION______ 
    FILE *inputFile; // used to hold a pointer to the file being read from
    char inputCharacter; // used to hold a character of input from the file
    int word = 0, letter = 0; // used to hold the position of the array being written to

    // ______FUNCTION PROCESSING______
    inputFile = fopen(fileName, "r");

    if (inputFile == NULL) // if the file doesn't exist then the user needs to be informed and the process stopped before an error occurs
    {
        printf("Error: inputFile.txt is not in the current directory");
        return 0;
    }

    word = 0;
    letter = 0;
    while (fscanf(inputFile, "%c", &inputCharacter) == 1) // this loop will access every character contained in the file
    {
        if ((inputCharacter == 32) || (inputCharacter == 10)) // if the character is a space(32) or a newline(10) the program moves to the next word
        {
            word++;
            letter = 0;
        }
        else // otherwise it adds the character to the current word
        {
            inputText[word][letter] = inputCharacter;
            letter++;
        }
        if (word > 2099) // under normal use it is substantially possible for 2100 words to be exceeded (which would cause a buffer overflow). This statement ensures that this is avoided
            break;
    }
    //fclose()
    return 1;
}







/* This function is designed to clear 2D arrays parsed to it, so that any data previously in this location is forgotten
    Input:
    1. A pointer to the array to be cleared
    2. The maximum x dimension of the array
    3. The maximum y dimension of the array

    Return:
    1. No direct return value
    2. The values of the array parsed in are modified

    Functionality:
    1. Two loops to go through each item in the array and set it to the number 0

    Limitations:
    1. Array must be less than [2100][100] in size, otherwise buffer overflows may occur

*/
void clearArray(char array[2100][100], int words, int characters)
{
    // ______INITIALISATION______
    int xIndex, yIndex; // used to hold the position of the array being cleared

    // ______FUNCTION PROCESSING______
    // These loops will ensure that every element of the array is accessed and assigned to 0
    for (xIndex = 0; xIndex < words; xIndex++)
    {
        for (yIndex = 0; yIndex < characters; yIndex++)
        {
            array[xIndex][yIndex] = 0;
        }
    }
}






/* This function determines if the word parsed in is contained in the 2D array also parsed in
    Input:
    1. A 1D array of letters (forming a word)
    2. A 2D array of letters that form words
    3. The maximum words that are in this 2D array

    Return:
    1. A boolean 1 or 0. 1 means that the word was found, 0 means it wasn't

    Functionality:
    1. Loops through each word in the wordbank.
    2. If a match is found with or without punctuation, 1 is returned
    3. Otherwise 0 is returned

    Limitations:
    1. The word bank can only have up to 2100 words with up to 100 characters in each word
    2. '.', ',', '!', '?', ';' and ':' at the end of the input word is the only punctuation that will get ignored

*/
char crossReference(char *word, char wordBank[2100][100], int maxWords)
{
    // _____INITIALISATION______
    char wordBankEditable[100]; // this array is needed because strcat() edits the array parsed to it and the program requires the word bank to remain unchanged 
    // above does not need clearing as it is entirely copied to from another array

    // ______FUNCTION PROCESSING______
    for (int wordBankWord = 0; wordBankWord < maxWords; wordBankWord++) // looping through each word in the array
    {
        strcpy(wordBankEditable, wordBank[wordBankWord]); // copies the word from the bank to an editable array
        if (strcmp(word, wordBank[wordBankWord]) == 0) // determines if the words are equal
            return 1;

        strcpy(wordBankEditable, wordBank[wordBankWord]);
        if (strcmp(word, strcat(wordBankEditable,".")) == 0) // determines if the word is equal to the wordBank word with a '.' on the end of it
            return 1;

        strcpy(wordBankEditable, wordBank[wordBankWord]); // copies the word again as strcat() has changed it and it needs to be the same as the original, otherwise punctuation will build up on the end
        if (strcmp(word, strcat(wordBankEditable,",")) == 0)
            return 1;

        strcpy(wordBankEditable, wordBank[wordBankWord]);
        if (strcmp(word, strcat(wordBankEditable,"?")) == 0)
            return 1;

        strcpy(wordBankEditable, wordBank[wordBankWord]);
        if (strcmp(word, strcat(wordBankEditable,"!")) == 0)
            return 1;

        strcpy(wordBankEditable, wordBank[wordBankWord]);
        if (strcmp(word, strcat(wordBankEditable,";")) == 0)
            return 1;

        strcpy(wordBankEditable, wordBank[wordBankWord]);
        if (strcmp(word, strcat(wordBankEditable,":")) == 0)
            return 1;
    }
    // if the whole loops executes and no matches are found then 0 is returned
    return 0;
}