#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 200

int check_args(int arg, char s[]);
char rotate(char c, int n);

int main(int argc, char* argv[])
{
    if (check_args(argc, argv[1]))
    {
        return 1;
    }
    char plain[SIZE];
    printf("plaintext: ");
    gets(plain);
    //Converting the string to int with atoi() function
    int key = atoi(argv[1]) % 26;

    printf("ciphertext: ");
    //checking the chars of the string 'plain'
    for (int i = 0; i < strlen(plain); i++)
    {
        printf("%c", rotate(plain[i], key));
    }
    printf("\n");

    return 0;

}
//Checking args if they met the requirements
int check_args(int arg, char s[])
{
    if (arg != 2)
    {
            printf("Usage: ./caesar key\n");
            return 1;
    }

    for (int i = 0; i < strlen(s); i++)
    {
        if (!isdigit(s[i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    return 0;
}
//Rotate the alphabet depending in the key
char rotate(char c, int n)
{
    char ci;
    if (isalpha(c))
    {
        ci = c + n % 26;
        if (!isalpha(ci))
        {
            return ci - 26;
        }
        else
        {
            return ci;
        }
    }
    else
    {
        return c;
    }
}