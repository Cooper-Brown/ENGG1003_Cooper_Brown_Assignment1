char getSubstitutionKey(char *originalLetters, char *substituteLetters)
{
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
    return 1;
}
