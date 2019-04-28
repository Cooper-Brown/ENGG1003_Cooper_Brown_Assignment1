// ___________________________________________________ IMPORTED LIBRARIES ___________________________________________________ //
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // contains tolower() and toupper() functions
#include <string.h>

// ___________________________________________________ FUNCTION PROTOTYPES ___________________________________________________ //

char getTaskAndKey(char *rotationKey, char *substitutionKey);

char task1(char *rotationKey);
char task2(char *rotationKey);
char task3(char *substitutionKey);
char task4(char *substitutionKey);
char task5();
void task6();

char performRotation(char key);
char applyKeyToCharacter(char inputCharacter, char key);

char performSubstitution(char *originalLetters, char *substituteLetters);
char get2DArrayFromFile(char *inputText, char *fileName);


// ___________________________________________________________ MAIN _________________________________________________________ //
int main()
{
    char taskNumber = 0;
    char rotationKey = 0;
    char substitutionKey[27];
    char successful = 0;

    taskNumber = getTaskAndKey(&rotationKey, substitutionKey);
    printf("Task Number: %d\n", taskNumber);

    switch (taskNumber)
    {
        case 1:
            successful = task1(char *rotationKey);
            break;
        case 2:
            successful = task2(char *rotationKey);
            break;
        case 3:
            successful = task3(char *substitutionKey);
            break;
        case 4:
            successful = task4(char *substitutionKey);
            breaket
        case 7:
            successful = task5();
            if (successful == 0)
                task6();
            break;
    }
    if (successful)
        printf("Operation Successfully Completed\n");

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


char task1(char *rotationKey)
{
    if (performRotation(*rotationKey) == 1)
        return 1;
    return 0;
}


char task2(char *rotationKey)
{
    if (performRotation(-1*(*rotationKey)) == 1)
        return 1;
    return 0;
}



char task3(char *substitutionKey)
{
    char originalLetters[] = "abcdefghijklmnopqrstuvwxyz";
    if (performSubstitution(originalLetters, substitutionKey) == 1)
        return 1;
    return 0;
}



char task4(char *substitutionKey)
{
    char originalLetters[] = "abcdefghijklmnopqrstuvwxyz";
    if (performSubstitution(substitutionKey, originalLetters) == 1) // arrays passed in the opposite way to 'undo' the encryption done by the key
        return 1;
    return 0;
}



char task5()
{
    char inputText[2000][100];
    char inputTextCopy[2000][100]
    char wordBank[2100][100];

    char inputCharacter;

    char errorFlag = 0;

    if (get2DArrayFromFile(inputText, "inputFile.txt") == 0)
    {
        printf("Error: inputFile.txt is not in the current directory");
        errorFlag = 1;
    }
    if (get2DArrayFromFile(wordBank, "20k.txt") == 0)
    {
        printf("Error: 20k.txt is not in the current directory");
        errorFlag = 1;
    }
    if (errorFlag == 1) // having the flag may seem useless but if both files are missing I want an error message for each.
        return 0;





    for (int key = 0; key < 26; key++)
    {
        for (int inputWordNo = 0)
        {

        }
        inputCharacter = applyKeyToCharacter(inputCharacter, key)
    }


    for (int inputWord = 0, inputCharacter = 0; inputWord < 2000;)
    {

    }







        FILE *outputFile;

        outputFile = fopen("outputFile.txt", "w");
    }
    
    if (outputFile == NULL)
    {
        printf("Error: outputFile.txt is not in the current directory");
        errorFlag = 1;
    }


}





void task6()
{
    FILE *inputFile, *outputFile;
    char inputText[1000][100];
    char inputWord[100];
    char errorFlag = 0;
    int word = 0;


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
        //fclose()
        return 0;
    
    word = 0;
    while (fscanf(inputFile, "%s", inputWord) == 1)
    {
        inputText
    }
}





char performRotation(char key)
{   
    char errorFlag = 0;
    char text[1000];
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
        inputCharacter = applyKeyToCharacter(inputCharacter, key);
        fprintf(outputFile, "%c", inputCharacter);
    }
    
    //fclose(inputFile);
    //fclose(outputFile)
    return 1;

}

char applyKeyToCharacter(char inputCharacter, char key)
{
    // for lower case characters
    if (inputCharacter >= 97 && inputCharacter <= 122)
    {
        inputCharacter += key;
        if (inputCharacter > 122)
            inputCharacter = 96 + (inputCharacter - 122);
        else if (inputCharacter < 97)
            inputCharacter = 123 - (97 - inputCharacter);
    }

    // for upper case characters
    else if (inputCharacter >= 65 && inputCharacter <= 90)
    {
        inputCharacter += key;
        if (inputCharacter > 90)
            inputCharacter = 64 + (inputCharacter - 90);
        else if (inputCharacter < 65)
            inputCharacter = 91 - (65 - inputCharacter);
    }
    return inputCharacter;
}


// add file closes before each return
char performSubstitution(char *originalLetters, char *substituteLetters)
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


char get2DArrayFromFile(char *inputText, char *fileName)
{ 
    FILE *inputFile;
    char inputCharacter;
    int word = 0, letter = 0;


    inputFile = fopen(*fileName, "r");

    if (inputFile == NULL)
    {
        printf("Error: inputFile.txt is not in the current directory");
        return 0;
    }

    word = 0;
    letter = 0;
    while (fscanf(inputFile, "%c", &inputCharacter) == 1)
    {
        inputText[word][letter] = inputCharacter;
        if (inputCharacter == 32)
        {
            word++;
            letter = 0;
        }
        else
            letter++;
        
    }
    inputText[word][letter] = 0;
    //fclose()
    return 1;
}