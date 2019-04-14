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

void performRotation(char key);

// This function 
int inbuiltCommandSelector();

int cliCommandSelector(int argc, char *argv[]);











char task1()
{
    char successful = 0;
    char key = 0;
    key = getRotationKey();
    if (key == 27)
    {
        printf("Error:\n");
        printf("Key file was non-existant or in the wrong format.\n");
        printf("Please fix the error and try again.\n");
    }
    else
    {
        performRotation(key);
        successful = 1;
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
        printf("Error:\n");
        printf("Key file was non-existant or in the wrong format.\n");
        printf("Please fix the error and try again.\n");
    }
    else
    {
        performRotation(key);
        successful = 1;
    }
    return successful;
}
char task3()
{

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




void performRotation(char key)
{
    char lineOfInput[400];
    FILE *inputFile;

    inputFile = fopen("inputFile.txt", "r");

    //printf("Before Loop");
    while (!feof(inputFile))
    {
        fscanf(inputFile, "%s", lineOfInput);
        printf("File Contents: %d", lineOfInput);
    }
    
    //fclose(inputFile);

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
    if (successful)
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
