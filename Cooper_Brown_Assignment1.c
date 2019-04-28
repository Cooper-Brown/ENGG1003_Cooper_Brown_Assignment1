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
   1. 
*/
char task3and4(char *originalLetters, char *substituteLetters)
{
    //______INITIALISATION______
    char inputCharacter;
    FILE *inputFile, *outputFile;

    //______FUNCTION PROCESSING______
    inputFile = fopen("inputFile.txt", "r");
    outputFile = fopen("outputFile.txt", "w");

    if (inputFile == NULL)
    {
        printf("Error: inputFile.txt is not in the current directory");
        return 0;
    }
    if (outputFile == NULL)
    {
        printf("Error: outputFile.txt is not in the current directory");
        return 0;
    }

    while (fscanf(inputFile, "%c", &inputCharacter) == 1)
    {
        for (int index = 0; index < 26; index++)
        {
            if (inputCharacter == originalLetters[index])
            {
                inputCharacter = substituteLetters[index];
                break;
            }
            else if (inputCharacter == toupper(originalLetters[index]))
            {
                inputCharacter = toupper(substituteLetters[index]);
                break;
            }
        }
        if (inputCharacter >= 97 && inputCharacter <= 122)
            inputCharacter -= 32;
        fprintf(outputFile, "%c", inputCharacter);
    }
    fclose(inputFile);
    fclose(outputFile);
    return 1;
}





char task5()
{
    int maxWords = 2100;
    int maxCharacters = 100;
    char inputText[maxWords][maxCharacters];
    char inputTextOriginal[maxWords][maxCharacters];
    char wordBank[maxWords][maxCharacters];
    clearArray(inputText, maxWords, maxCharacters);
    clearArray(inputTextOriginal, maxWords, maxCharacters);
    clearArray(wordBank, maxWords, maxCharacters);

    char errorFlag = 0;


    if (get2DArrayFromFile(inputText, "inputFile.txt") == 0)
    {
        printf("Error: inputFile.txt is not in the current directory");
        errorFlag = 1;
    }
    get2DArrayFromFile(inputTextOriginal, "inputFile.txt"); // strcpy() not used as the array is 2D

    if (get2DArrayFromFile(wordBank, "20k.txt") == 0)
    {
        printf("Error: 20k.txt is not in the current directory");
        errorFlag = 1;
    }
    if (errorFlag == 1) // having the flag may seem useless but if both files are missing I want an error message for each.
        return 0;

    




    
    int hit = 0, noHit = 0;

    for (int key = 0; key < 26; key++)
    {
        hit = 0;
        noHit = 0;
        // _________rotates everything in array_________________ //
        for (int word = 0; word < maxWords; word++)
        {
            for (int letter = 0; letter < maxCharacters; letter++)
            {
                inputText[word][letter] = applyRotationKeyToCharacter(inputTextOriginal[word][letter], (-1*key));
            }
        }


        // ___________cross references a word from input with every word in wordbank
        for (int word = 0; word < maxWords; word++)
        {
            if (inputText[word][0] == 0) // ends the search if the word is empty (meaning all words have been searched)
                break;
            if (crossReference(inputText[word], wordBank, maxWords) == 1)
                hit++;
            else
                noHit++;
            
        }

        //printf("Hits: %d noHits: %d\n", hit, noHit);
        if ((hit*1.0)/(hit+noHit) > 0.5)
        {
            printf("The key used to originally ENCODE the text is %d\n\n", key);
            task1and2((-1)*key);
            return 1;
        }
    }
    return 0;
}


char task6(char *originalLetters)
{
    int maxWords = 2100;
    int maxCharacters = 100;
    char inputText[maxWords][maxCharacters];
    char inputTextOriginal[maxWords][maxCharacters];
    char wordBank[maxWords][maxCharacters];
    clearArray(inputText, maxWords, maxCharacters);
    clearArray(inputTextOriginal, maxWords, maxCharacters);
    clearArray(wordBank, maxWords, maxCharacters);

    char errorFlag = 0;

    char standardLetterFrequencies[26] = "etaoinsrhdlucmfywgpbvkxqjz";
    int letterCounts[26];
    for (int index = 0; index < 26; index++)
        letterCounts[index] = 0;



    if (get2DArrayFromFile(inputText, "inputFile.txt") == 0)
    {
        printf("Error: inputFile.txt is not in the current directory");
        errorFlag = 1;
    }
    get2DArrayFromFile(inputTextOriginal, "inputFile.txt"); // strcpy() not used as the array is 2D

    if (get2DArrayFromFile(wordBank, "20k.txt") == 0)
    {
        printf("Error: 20k.txt is not in the current directory");
        errorFlag = 1;
    }
    if (errorFlag == 1) // having the flag may seem useless but if both files are missing I want an error message for each.
        return 0;

    for (int word = 0; word < maxWords; word++)
        {
            for (int letter = 0; letter < maxCharacters; letter++)
            {   
                for (int elementOfLetterFrequencies = 0; elementOfLetterFrequencies < 26; elementOfLetterFrequencies++)
                {
                    //printf("iterator---%d---word---%d---letter---%d\n", elementOfLetterFrequencies, word, letter);
                    //printf("%c---%c\n", standardLetterFrequencies[elementOfLetterFrequencies], inputText[word][letter]);
                    if (inputText[word][letter] >= 65 && inputText[word][letter] <= 90)
                        inputText[word][letter] += 32;
                    if (standardLetterFrequencies[elementOfLetterFrequencies] == inputText[word][letter])
                    {
                        letterCounts[elementOfLetterFrequencies] += 1;
                    }
                }
            }
        }

    int highestIndex = 0, startIndex = 0, tempi = 0;
    char tempc, inputLetterFrequencies[27];
    strcpy(inputLetterFrequencies, standardLetterFrequencies);

    for (int startIndex = 0; startIndex < 26; startIndex++)
    {
        highestIndex = startIndex;
        for (int index = startIndex+1; index < 26; index++)
        {
            if (letterCounts[index] > letterCounts[highestIndex])
                highestIndex = index;
        }
        tempi = letterCounts[startIndex];
        letterCounts[startIndex] = letterCounts[highestIndex];
        letterCounts[highestIndex] = tempi;
        tempc = inputLetterFrequencies[startIndex];
        inputLetterFrequencies[startIndex] = inputLetterFrequencies[highestIndex];
        inputLetterFrequencies[highestIndex] = tempc;
    }
         
    printf("Below is the calculated key for this task\n");
    for (int index = 0; index < 26; index++)
        printf("%c --> %c\n", standardLetterFrequencies[index], inputLetterFrequencies[index]);
    printf("This key was used to ENCODE the data to its encrypted state.\nThe key used by this program to decrypt the text has the arrow inverted\ni.e. a --> b becomes b --> a\n\n");
    /*
    for (int word = 0; word < maxWords; word++)
    {
        for (int letter = 0; letter < maxCharacters; letter++)
        {
            for (int letterFrequenciesIndex = 0; letterFrequenciesIndex < 26; letterFrequenciesIndex++)
            {
                if (inputText[word][letter] == standardLetterFrequencies[letterFrequenciesIndex])
                {
                    inputText[word][letter] = inputLetterFrequencies[letterFrequenciesIndex];
                    break;
                }
            }
        }
    }
    */

    task3and4(inputLetterFrequencies, standardLetterFrequencies);
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