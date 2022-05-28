#include <stdio.h>
#define SIZE 20
int main(void)
{
    char name[SIZE];
    // User input
    printf("What's your name: ");
    gets(name);

    // Print the message
    printf("Hello, %s!\n", name);
}