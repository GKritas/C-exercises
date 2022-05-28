#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define SIZE 100

int check_args(int arg, char s[]);
char sub(char c, char s[]);

int main(int argc, char* argv[])
{
    if (check_args(argc, argv[1]))
    {
        return 1;
    }

    char plain[SIZE];
    printf("plaintext: ");
    gets(plain);

    printf("ciphertext: ");
    for (int i = 0; i < strlen(plain); i++)
    {
        printf("%c", sub(plain[i], argv[1]));
    }
    printf("\n");

    return 0;
}
//Check if the args meet the requirements
int check_args(int arg, char s[])
{
    //Check if arg = 2
    if (arg != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //Check if the length of the string is 26
    if (strlen(s) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        //Check if the key is only chars
        for (int i = 0; i < strlen(s); i++)
        {
            if (!isalpha(s[i]))
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
            //Check for duplicate chars
            for (int j = 0; j < strlen(s); j++)
            {
                if (toupper(s[i]) == toupper(s[j]) && i != j)
                {
                    printf("Key must not contain the same character.\n");
                    return 1;
                }
            }
        }
        return 0;
    }
}
//Substitute chars of the plaintext with chars of the key
char sub(char c, char  s[])
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (isalpha(s[i]) && isupper(c))
        {
            return toupper(s[c - 65]);
        }
        else if (isalpha(s[i]) && islower(c))
        {
            return tolower(s[c - 97]);
        }
        else
        {
            return c;
        }
    }

    return 0;
}