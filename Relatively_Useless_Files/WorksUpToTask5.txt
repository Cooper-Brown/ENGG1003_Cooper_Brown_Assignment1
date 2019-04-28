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
    char taskNumber = 0;

    char rotationKey = 0;
    char originalLetters[] = "abcdefghijklmnopqrstuvwxyz";
    char substitutionKey[27];

    char successful = 0;

    taskNumber = getTaskAndKey(&rotationKey, substitutionKey);

    switch (taskNumber)
    {
        case 1:
            printf("Attempting to complete task %d...\n", taskNumber);
            successful = task1and2(rotationKey);
            break;
        case 2:
            printf("Attempting to complete task %d...\n", taskNumber);
            successful = task1and2(-1*rotationKey);
            break;
        case 3:
            printf("Attempting to complete task %d...\n", taskNumber);
            successful = task3and4(originalLetters, substitutionKey);
            break;
        case 4:
            printf("Attempting to complete task %d...\n", taskNumber);
            successful = task3and4(substitutionKey, originalLetters); // input parameters swapped so key is 'reversed'
            break;
        case 7:
            taskNumber = 5;
            printf("Attempting to complete task %d...\n", taskNumber);
            successful = task5();
            if (successful == 0)
            {
                printf("Task %d failed\n", taskNumber);
                taskNumber = 6;
                printf("Attempting to complete task %d...\n", taskNumber);
                successful = task6(originalLetters);
            }
            break;
    }
    if (successful)
        printf("Task %d has been completed.\n", taskNumber);
        // print output file to screen
    else
        printf("No task could be completed.\n");

    return 0;
}



// _______________________________________________________ FUNCTIONS _________________________________________________________ //

char getTaskAndKey(char *rotationKey, char *substitutionKey)
{
    FILE *keyFile;
    char command[100];
    char taskNumber = 0;
    fpos_t position;
    
    keyFile = fopen("keyFile.txt", "r");

    if (keyFile == NULL)
    {
        printf("Error: keyFile.txt is not in the current directory\n");
        return 0;
    }

    fscanf(keyFile, "%s", command);
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

    for (int key = 7; key < 8; key++)
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

        printf("Hits: %d noHits: %d\n", hit, noHit);
        if ((hit*1.0)/(hit+noHit) > 0.5)
        {
            printf("The key is %d\n", key);
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

    int letterFrequencies[27];

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
    

    for (int index = 0; index < 26; index++)
    {
        
    }
    


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
        printf("I:%s---B:%s---\n", word, wordBank[wordBankWord]);
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