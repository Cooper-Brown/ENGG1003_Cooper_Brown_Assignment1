#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char task1(); // encode rotation cypher with key
char task2(); // decode rotation cypher with key
char task3();
char task4();
char task5();
char task6();

char getRotationKey();

char performRotation(char key);

// This function 
int inbuiltCommandSelector();
int cliCommandSelector(int argc, char *argv[]);

void keyFileFault();

void keyFileFault()
{
    printf("Key File Error:\n\n");
    printf("Key is either:\n-out of range\n-in the wrong format\nOr the file does not exist.\n\n");
    printf("Encryption could not be completed.\n");
    printf("Please fix the error with the key file and try again.\n");
}









char task1()
{
    char successful = 0;
    char key = 0;
    key = getRotationKey();
    if (key == 27)
    {
        keyFileFault();
    }
    else
    {
        successful = performRotation(key);
    }
    return successful;
}
char task2()
{
    char successful = 0;
    char key = 0;
    key = -1*getRotationKey();
    if (key == 27)
    {
        keyFileFault();
    }
    else
    {
        successful = performRotation(key);
    }
    return successful;
}
char task3()
{
    char inputCharacter;
    char originalLetters[27];
    char substituteLetters[27]; // 27 because room is required for the end of string/array character
    FILE *keyFile;
    
    keyFile = fopen("keyFile.txt", "r");

    if (keyFile == NULL)
    {
        printf("Error: keyFile.txt is not in the current directory");
        return 0;
    }

    if (fscanf(keyFile, "%26c%*c%26c", originalLetters, substituteLetters) != 2)
    {
        printf("Error: the key is in an incorrect format.\n");
        return 0;
    }
    //fclose(keyFile);

    FILE *inputFile, *outputFile;

    inputFile = fopen("inputFile.txt", "r");
    outputFile = fopen("outputFile.txt", "w");

    while (fscanf(inputFile, "%c", &inputCharacter) == 1)
    {
        for (int index = 0; index < 26; index++)
        {
            if (inputCharacter == originalLetters[index])
        }
    }

    return 1;
}
char task4()
{

}
char task5()
{

}
char task6()
{

}




char performRotation(char key)
{   
    char errorFlag = 0;
    int textSize = 1000;
    char text[textSize];
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
    if (errorFlag = 1)
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
    return 1;

}



char getRotationKey()
{
    char key = 27;
    char itemsMatched = 0;
    FILE *keyFile;

    keyFile = fopen("keyFile.txt", "r");
    if (keyFile != NULL)
    {
        itemsMatched = fscanf(keyFile, "%2d", &key);
        if (itemsMatched != 1 || key > 26 || key < 0)
            key = 27;
        //fclose(keyFile);
    }

    //printf("Key: %d", key);

    return key;
}















int main(int argc, char *argv[])
{
    char successful = 0;
    char taskNumber = 3;

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
