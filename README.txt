/*
NOTE: this comment block contains the same information as the start of my c file

My Details:
Name: Cooper Brown
ID: 3324706
Date: 29/04/19

Name of .c file: Cooper_Brown_Assignment1.c
Note: There are a lot of other files in this git folder. All the irrelevant ones should be contained in a separate folder

Instructions for use:
1. Place the text block that needs to be processed into the file inputFile.txt
2. Format keyFile.txt for the operation you want to perform
    a. The first line should be either the word 'encode' or 'decode'
    b. place in the second line 'key: ' (space is important) followed by either
        i. a number from 0-26 (representing a rotation key)
        ii. a series of letters e.g. 'stuvwghijklmnoabcdefpqrxyz' where s = a, t = b etc.
            (This represents a substitution key)
        iii. nothing (if you want to decode without a key)
            Note: this option only works for decryption
            Note: This will try to decrypt the file using caeser then substitution if the caeser fails. 
       The key type will be automatically detected and the task selected based on this

Task Number Key:
Task1 = encryption using caesar key
Task2 = decryption using caesar key
Task3 = encryption using substitution key
Task4 = decryption using substitution key
Task5 = decryption of caesar cypher without key
Task6 = decryption of substitution cypher without key


keyFile.txt formatting examples:
Task1:
encode
key: 21

Task2:
decode
key: 14

Task3:
encode
key: stuvwghijklmnoabcdefpqrxyz

Task4:
decode
key: stuvwghijklmnoabcdefpqrxyz

Task5:
decode
key: 

Task6:
decode
key: 

*/
