#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char task1(); // encode rotation cypher with key
char task2(); // decode rotation cypher with key
char task3();
char task4();
char task5();
char task6();

char getRotationKey(char *key);
char performRotation(char key);

char getSubstitutionKey(char *originalLetters, char *substituteLetters);
char performSubstitution(char *originalLetters, char *substituteLetters);

int inbuiltCommandSelector();
int cliCommandSelector(int argc, char *argv[]);



char task1()
{
    char key = 0;
    if (getRotationKey(&key) == 1)
        if (performRotation(key) == 1)
            return 1;
    return 0;
}
char task2()
{
    char key = 0;
    if (getRotationKey(&key) == 1)
        if (performRotation(-1*key) == 1)
            return 1;
    return 0;
}
char task3()
{
    char originalLetters[27];
    char substituteLetters[27]; // 27 because room is required for the end of string/array character
    
    if (getSubstitutionKey(originalLetters, substituteLetters) == 1)
        if (performSubstitution(originalLetters, substituteLetters) == 1)
            return 1;
    return 0;

}
char task4()
{
    char originalLetters[] = "abcdefghijklmnopqrstuvwxyz";
    char substituteLetters[27]; // 27 because room is required for the end of string/array character
    
    if (getSubstitutionKey(originalLetters, substituteLetters) == 1)
        if (performSubstitution(substituteLetters, originalLetters) == 1) // they are passed the opposite way as the key needs to be performed backwards to decode
            return 1;
    return 0;
}
char task5()
{
    FILE *inputFile, *outputFile;
    char inputWord[50];

    inputFile = fopen("inputFile.txt", "r");
    if (inputFile == NULL)
    {
        printf("Error: inputFile.txt is not in the current directory");
        return 0;
    }

    while (fscanf(inputFile, "%s", &inputWord) == 1)
    {

    }

    //fclose(inputFile);
}
char task6()
{

}


char getSubstitutionKey(char *substituteLetters)
{
    FILE *keyFile;
    
    keyFile = fopen("keyFile.txt", "r");

    if (keyFile == NULL)
    {
        printf("Error: keyFile.txt is not in the current directory\n");
        return 0;
    }

    if (fscanf(keyFile, "%*[^\n]%*[^:]%*2c%26c", substituteLetters) != 1)
    {
        printf("Error: the key is in an incorrect format.\n");
        return 0;
    }
    //fclose(keyFile);
    return 1;
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

char getRotationKey(char *key)
{
    char itemsMatched = 0;
    FILE *keyFile;

    keyFile = fopen("keyFile.txt", "r");
    if (keyFile == NULL)
    {
        printf("Error: keyFile.txt is not in the current directory\n");
        return 0;
    }

    if (fscanf(keyFile, "%2d", key) != 1)
    {
        printf("Error: the key is in an incorrect format.\n");
        return 0;
    }

    if (*key > 26 || *key < 0)
    {
        printf("Error: key is out of range");
        return 0;
    }

    //fclose(keyFile);
    return 1;
}

// add fcloses after setting error flags
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
        fprintf(outputFile, "%c", inputCharacter);
    }
    
    //fclose(inputFile);
    //fclose(outputFile)
    return 1;

}



















int main(int argc, char *argv[])
{
    char taskNumber = 1;




    //taskNumber = inbuiltCommandSelector();

    switch (taskNumber) {
        case 1 :
            successful = task1();
            break;
        case 2 :
            successful = task2();
            break;
        case 3 :
            successful = task3();
            break;
        case 4 :
            successful = task4();
            break;
        case 5 :
            successful = task5();
            break;
        case 6 :
            successful = task6();
            break;
    }
    if (successful == 1)
        printf("Operation completed successfully\n");







            /*
            if (encryptFileR(key) == 1)
                printf("Encryption Successful\n");
            else
                printf("Encryption Failed\n");
            break;
            */
    return 0;

}













int inbuiltCommandSelector()
{
    const char prntCommands[] = "-arguements",
                 task1[] = "-encode -rotation -key",
                 task2[] = "-decode -rotation -key",
                 task3[] = "-encode -substitution -key",
                 task4[] = "-decode -substitution -key",
                 task5[] = "-decode -rotation",
                 task6[] = "-decode -substitution";
    char command[100];
    int taskNumber = 0;

    printf("Arguements not given/incorrect. Please enter them here instead. (type -arguements for list of options) \n> ");
    
    do 
    {
        // takes input up until a newline character
        // Note space in front to ensure the last newline character isn't read
        scanf(" %[^\n]s", command);
            
        // strcmp(command, prntCommands) == 0 when the strings command and prntCommands are equal
        if (strcmp(command, prntCommands) == 0)
        {
            printf("\n \n");
            printf("> %s          =>     prints list of commands \n \n", prntCommands);
            printf("> %s          =>     encodes rotation cypher with key given \n \n", task1);
            printf("> %s          =>     decodes rotation cypher with key given \n \n", task2);
            printf("> %s          =>     encodes substitution cypher with key given \n \n", task3);
            printf("> %s          =>     decodes substitution cypher with key given \n \n", task4);
            printf("> %s          =>     decodes rotation cypher without key \n \n", task5);
            printf("> %s          =>     decodes substitution cypher without key \n \n", task6);
            printf("> ");
        } else if (strcmp(command, task1) == 0)
            taskNumber = 1;
        else if (strcmp(command, task2) == 0)
            taskNumber = 2;
        else if (strcmp(command, task3) == 0)
            taskNumber = 3;
        else if (strcmp(command, task4) == 0)
            taskNumber = 4;
        else if (strcmp(command, task5) == 0)
            taskNumber = 5;
        else if (strcmp(command, task6) == 0)
            taskNumber = 6;
        else 
            printf("Invalid Command \n> ");
        
    } while (taskNumber == 0);
    
    return taskNumber;
}

int cliCommandSelector(int argc, char *argv[])
{
    const char  ARG1[] = "-encode",
                ARG2[] = "-decode",
                ARG3[] = "-substitution",
                ARG4[] = "-rotation",
                ARG5[] = "-key",
                ARG6[] = "-nokey";


    if (argc == 1)
    {
        char taskNumber = inbuiltCommandSelector();
    } else 
    {
        //do something with the arguements
    }


    return 0;
}
