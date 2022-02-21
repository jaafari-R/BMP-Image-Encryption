/*
    This Program uses AES in CBC mode to encrypt
     an image in bmp format.
    The main function takes 2 arguments:
        arg1: e/encrypt for encryption.
              d/decrypt for decryption.
        
        arg2: the path of the bmp image that we
               want to encrypt/decrypt.

        arg3: the output image path.
*/

#include <iostream>
#include <string.h>

/* Reads the first argument and returns:
    'e' fo encryption
    'd' for decryption
    0 for invalid inputs */
char readArg1(char* arg);

int main(int argc, char* argv[])
{
    char option; // 'e' = encrypt / 'd' = decrypt / 0 = invalid option

    // -+-+-+-+- Input reading -+-+-+-+-
    if(argc < 3)
    {
        printf("Two arguements are required,\n\t"
        "arg1: e/encrypt or d/decrypt"
        "arg2: the path to the bmp image.\n");
        return 1;
    }

    option = readArg1(argv[1]);
    if(!option)
    {
        printf("The first argument may only be e/encrypt (for encryption) or d/decrypt (for decryption)\n");
        return 1;
    }



}

char readArg1(char* arg)
{
    char res = 0;
    if(strlen(arg) == 1)
    {
        if(arg[0] == 'e')
            res = 'e';
        else if(arg[0] == 'd')
            res = 'd';
    }
    else
    {
        if(strcmp(arg, "encrypt"))
            res = 'e';
        if(strcmp(arg, "decrypt"))
            res = 'd';
    }
    return res;
}