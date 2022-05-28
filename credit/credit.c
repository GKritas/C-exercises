#include <stdio.h>

int lengthOfNumber(long long int num);
void arrayOfNumbers(long long num, int *array, int length);
int validLength(int length);
int typeOfCard(int *array, int length);
int sumCheck(int *array, int length);

int main(void)
{
    long long cardNumber;
    int length, sum, type, numl;

    //User input
    printf("Enter your credit card number: ");
    scanf("%lld", &cardNumber);

    //Calculate the length
    length = lengthOfNumber(cardNumber);

    //Insert number into array from the end to start
    int array[length];
    arrayOfNumbers(cardNumber, array, length);

    type = typeOfCard(array, length);
    sum = sumCheck(array, length);
    numl = validLength(length);
    //Print type of card depends the contitions
    if (numl && sum && type == 1)
    {
        printf("VISA\n");
    }
    else if (numl && sum && type == 2)
    {
        printf("AMEX\n");
    }
    else if (numl && sum && type == 3)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }

}
// Function to find the length of the number
int lengthOfNumber(long long int num)
{
    int count = 0;
    do
    {
        num /= 10;
        count++;
    }
    while (num > 0);

    return count;
}
// Function to add the digits of the number into an array
void arrayOfNumbers(long long int num, int *array, int length)
{
    for (int i = 0; i < length; i++)
    {
        array[i] = num % 10;
        num /= 10;
    }
}
// Check if length meets the requirements
int validLength(int length)
{
    if (length >= 13 && length <= 16)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// Check the type of the card
int typeOfCard(int *array, int length)
{
    int check;
    check = (array[length - 1] * 10) + array[length - 2];

    if (array[length - 1] == 4)
    {
        //Visa
        return 1;
    }
    else if (check == 34 || check == 37)
    {
        //AmericanExpress
        return 2;
    }
    else if (check >= 51 && check <= 55)
    {
        //MasterCard
        return 3;
    }
    else
    {
        //Invalid
        return 0;
    }
}
// Check if the card is valid with luhn algorithm
int sumCheck(int *array, int length)
{
    int sum = 0;
    for (int i = 1; i < length; i += 2)
    {
        array[i] *= 2;
        if (array[i] > 9)
        {
            array[i] = (array[i] / 10) + (array[i] % 10);
        }
    }

    for (int i = 0; i < length; i++)
    {
        sum += array[i];
    }

    if (sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}