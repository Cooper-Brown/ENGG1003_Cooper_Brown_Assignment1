#include <stdio.h>

char getTaskAndKey(char *rotationKey, char *substitutionKey)
{
    FILE *keyFile;
    
    keyFile = fopen("keyFile.txt", "r");

    if (keyFile == NULL)
    {
        printf("Error: keyFile.txt is not in the current directory\n");
        return 0;
    }


    if (fscanf(keyFile, "key: %2d", rotationKey) == 1)
        return 1;
    else if (fscanf(keyFile, "key: %26c", substitutionKey) == 1)
        return 2;
    else
    {
        printf("Error: the key is in an incorrect format.\n");
        return 0;
    }
    //fclose(keyFile);
}

int main()
{
    FILE *keyFile;
    char input[100];
    char key=0;
    
    keyFile = fopen("keyFile.txt", "r");

    fscanf(keyFile, "%s", input);
    printf("1st line: %s\n", input);

    fscanf(keyFile, "%*[^:]%*2c%2d", &key);

    printf("2nd line: %d\n", key);

    return 0;
}