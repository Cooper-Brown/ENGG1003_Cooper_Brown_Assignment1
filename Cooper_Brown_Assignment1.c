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

char crossReference2(char inputText[2100][100], char wordBank[2100][100], char maxWords);


// ___________________________________________________________ MAIN _________________________________________________________ //
int main()
{
    // _____Initialising variables to be used in MAIN_____
    char taskNumber = 0; // holds a number that is used to choose which task will be performed

    char rotationKey = 0; // used to hold a number from 0-26 that will represent a caesar cypher key
    char originalLetters[] = "abcdefghijklmnopqrstuvwxyz"; // an array holding the letters of the alphabet. 
    char substitutionKey[27]; // an empty array that will contain an ordered list of letters that the letters in the above array will be substituted with

    char successful = 0; // a boolean variable used to hold the return status of the tasks. 1 = successful and 0 = not successful

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
            successful = task3and4(substitutionKey, originalLetters); // same as case 3, except parameters swapped so key is 'reversed' for decryption
            break;
        case 7: // this case will initially attempt a rotation cypher, and if a satisfactory result is not achieved it will attempt to crack it as though it was substitution
            taskNumber = 5; // initially attempts the rotation decryption
            printf("Attempting to complete task %d...\n", taskNumber);
            successful = task5(); // task5 will perform the necessary rotations and spelling checks
            if (successful == 0) // if this fails, substitution decryption is attempted
            {
                printf("Task %d failed\n", taskNumber); // informs the user that the caesar decryption has failed
                taskNumber = 6;
                printf("Attempting to complete task %d...\n\n", taskNumber);
                successful = task6(originalLetters); // task 6 will perform the decryption
            }
            break;
    }
    if (successful)
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
        
    else // if the task was not successful, the user is informed of this
        printf("No task could be completed.\n");

    return 0;
}

// _______________________________________________________ FUNCTIONS _________________________________________________________ //

/*  This function serves the purpose of determining the operation that the user wants to perform.
    Input:
    It takes in two pointers to the location of where the keys are stored in the calling function
    
    Return:
    The number of the task to be performed. The location of one of the pointers is also changed to a valid keys. 
    
    Functionality:
    1. Opens keyFile.txt
    2. grabs the wanted operation type(encode/decode) from the first line of the file.
    3. input matching through scanf() determines the type of key the user has entered.
    4. The data from steps 3 and 4 are used to select the desired task
*/
char getTaskAndKey(char *rotationKey, char *substitutionKey)
{
    FILE *keyFile;
    char command[100]; // this array is used to hold the text typed in the first line of the program
    char taskNumber = 0;
    fpos_t position; // this is an object used to indicate the read position of the file. It is used to re-read lines that have already been read
    
    keyFile = fopen("keyFile.txt", "r");

    if (keyFile == NULL) // this statement checks if the file exists, to avoid crashes later on and give the user information about why the program is not working
    {
        printf("Error: keyFile.txt is not in the current directory\n");
        return 0;
    }

    fscanf(keyFile, "%s", command); // 
    fgetpos(keyFile, &position);
    if (strcmp(strlwr(command),"encode") == 0)
    {
        if (fscanf(keyFile, "%*[^:]%*2c%2d", rotationKey) == 1)
            taskNumber = 1;
        else 
        {
            fsetpos(keyFile, &position);
            if (fscanf(keyFile, "%*[^:]%*2c%26c", substitutionKey) == 1)
                taskNumber = 3;
            else
                printf("Error: cannot encode without a valid key.\n");
        }
        
    }
    else if (strcmp(strlwr(command),"decode") == 0)
    {
        if (fscanf(keyFile, "%*[^:]%*2c%2d", rotationKey) == 1)
            if (*rotationKey > 26 || *rotationKey < 0)
            {
                printf("Error: key is out of range");
                taskNumber = 0;
            }
            else
                taskNumber = 2;
        else 
        {
            fsetpos(keyFile, &position);
            if (fscanf(keyFile, "%*[^:]%*2c%26c", substitutionKey) == 1)
                taskNumber = 4;
            else
            {
                printf("Could not detect a valid key. Attempting to decode without one...\n");
                taskNumber = 7;
            }
        }
            
    }
    else
        printf("1st line (the command header) of keyFile.txt is formatted incorrectly.\nIt should either be 'encode' or 'decode'.\n");
    //fclose(keyFile);
    return taskNumber;   
}


char task1and2(char rotationKey)
{
    char errorFlag = 0;
    char inputCharacter;
    FILE *inputFile, *outputFile;

    inputFile = fopen("inputFile.txt", "r");
    outputFile = fopen("outputFile.txt", "w");

    if (inputFile == NULL)
    {
        printf("Error: inputFile.txt is not in the current directory");
        errorFlag = 1;
    }
    if (outputFile == NULL)
    {
        printf("Error: outputFile.txt is not in the current directory");
        errorFlag = 1;
    }
    if (errorFlag == 1) // having the flag may seem useless but if both files are missing I want an error message for each.
        return 0;



    while (fscanf(inputFile, "%c", &inputCharacter) == 1)
    {
        inputCharacter = applyRotationKeyToCharacter(inputCharacter, rotationKey);
        fprintf(outputFile, "%c", inputCharacter);
    }
    
    //fclose(inputFile);
    //fclose(outputFile)
    return 1;
}

char task3and4(char *originalLetters, char *substituteLetters)
{
    char inputCharacter;
    FILE *inputFile, *outputFile;

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

char applyRotationKeyToCharacter(char inputCharacter, char key)
{
    if (inputCharacter >= 65 && inputCharacter <= 90)
        inputCharacter += 32;
    // for lower case characters
    if (inputCharacter >= 97 && inputCharacter <= 122)
    {
        inputCharacter += key;
        if (inputCharacter > 122)
            inputCharacter = 96 + (inputCharacter - 122);
        else if (inputCharacter < 97)
            inputCharacter = 123 - (97 - inputCharacter);
    }
    /*
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

char get2DArrayFromFile(char inputText[2100][100], char *fileName)
{ 
    FILE *inputFile;
    char inputCharacter;
    int word = 0, letter = 0;

    inputFile = fopen(fileName, "r");

    if (inputFile == NULL)
    {
        printf("Error: inputFile.txt is not in the current directory");
        return 0;
    }

    word = 0;
    letter = 0;
    while (fscanf(inputFile, "%c", &inputCharacter) == 1)
    {
        if ((inputCharacter == 32) || (inputCharacter == 10))
        {
            word++;
            letter = 0;
        }
        else
        {
            inputText[word][letter] = inputCharacter;
            letter++;
        }
        if (word > 2099)
            break;
    }
    //fclose()
    return 1;
}

void clearArray(char array[2100][100], int words, int characters)
{
    int xIndex, yIndex;
    for (xIndex = 0; xIndex < words; xIndex++)
    {
        for (yIndex = 0; yIndex < characters; yIndex++)
        {
            array[xIndex][yIndex] = 0;
        }
    }
}

char crossReference2(char inputText[2100][100], char wordBank[2100][100], char maxWords)
{
    char wordBankEditable[100]; // does not need clearing as it is copied to from another array

    // ___________cross references a word from input with every word in wordbank
    for (int word = 0; word < maxWords; word++)
    {
        if (inputText[word][0] == 0) // skips over the empty space left at the end of the array
            break;
        for (int wordBankWord = 0; wordBankWord < maxWords; wordBankWord++)
        {
            strcpy(wordBankEditable, wordBank[wordBankWord]);
            if (strcmp(inputText[word], wordBank[wordBankWord]) == 0)
                return 1;

            strcpy(wordBankEditable, wordBank[wordBankWord]);
            if (strcmp(inputText[word], strcat(wordBankEditable,".")) == 0)
                return 1;

            strcpy(wordBankEditable, wordBank[wordBankWord]);
            if (strcmp(inputText[word], strcat(wordBankEditable,",")) == 0)
                return 1;

            strcpy(wordBankEditable, wordBank[wordBankWord]);
            if (strcmp(inputText[word], strcat(wordBankEditable,"?")) == 0)
                return 1;

            strcpy(wordBankEditable, wordBank[wordBankWord]);
            if (strcmp(inputText[word], strcat(wordBankEditable,"!")) == 0)
                return 1;
        }
    }
    return 0;
}

char crossReference(char *word, char wordBank[2100][100], int maxWords)
{
    char wordBankEditable[100]; // does not need clearing as it is copied to from another array

    for (int wordBankWord = 0; wordBankWord < maxWords; wordBankWord++)
    {
        //printf("I:%s---B:%s---\n", word, wordBank[wordBankWord]);
        strcpy(wordBankEditable, wordBank[wordBankWord]);
        if (strcmp(word, wordBank[wordBankWord]) == 0)
            return 1;

        strcpy(wordBankEditable, wordBank[wordBankWord]);
        if (strcmp(word, strcat(wordBankEditable,".")) == 0)
            return 1;

        strcpy(wordBankEditable, wordBank[wordBankWord]);
        if (strcmp(word, strcat(wordBankEditable,",")) == 0)
            return 1;

        strcpy(wordBankEditable, wordBank[wordBankWord]);
        if (strcmp(word, strcat(wordBankEditable,"?")) == 0)
            return 1;

        strcpy(wordBankEditable, wordBank[wordBankWord]);
        if (strcmp(word, strcat(wordBankEditable,"!")) == 0)
            return 1;
    }
    return 0;
}