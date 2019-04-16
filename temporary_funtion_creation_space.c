char getTaskAndKey(char *rotationKey, char *substitutionKey)
{
    FILE *keyFile;
    char command[100];
    char taskNumber = 0;
    
    keyFile = fopen("keyFile.txt", "r");

    if (keyFile == NULL)
    {
        printf("Error: keyFile.txt is not in the current directory\n");
        return 0;
    }

    fscanf(keyFile, "%s", command);
    if (tolower(command) == "encode")
    {
        if (fscanf(keyFile, "%*[^:]%*2c%2d", rotationKey) == 1)
            taskNumber = 1;
        else if (fscanf(keyFile, "%*[^:]%*2c%26c", substitutionKey) == 1)
            taskNumber = 3;
        else
            printf("Error: cannot encode without a valid key.\n");
    }
    else if (tolower(command) == "decode")
    {
        if (fscanf(keyFile, "%*[^:]%*2c%2d", rotationKey) == 1)
            taskNumber = 2;
        else if (fscanf(keyFile, "%*[^:]%*2c%26c", substitutionKey) == 1)
            taskNumber = 4;
        else
            printf("Could not detect a valid key. Attempting to decode without one...\n");
            taskNumber = 7;
    }
    else
        printf("1st line (the command header) of keyFile.txt is formatted incorrectly.\nIt should either be 'encode' or 'decode'.\n");
    //fclose(keyFile);
    return taskNumber;   
}