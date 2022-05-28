#include <stdio.h>

int main(void)
{
    int n, count;
    // User's input and check if condition made
    do
    {
        scanf("%d", &n);
    }
    while (n < 1 || n > 8);

    count = n - 1;
    for (int i = 1; i <= n; i++)
    {
        // Print spaces
        for (int k = 1; k <= count; k++)
        {
            printf(" ");
        }
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        // Print the middle spaces
        printf(" ");
        printf(" ");

        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        // Change line
        printf("\n");
        count--;
    }
}