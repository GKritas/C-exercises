#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 500

int count_letters(char text[]);
int count_words(char text[]);
int count_sentences(char text[]);

int main(void)
{
    char text[SIZE];
    printf("Text: ");
    gets(text);

    //Calling the functions
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    //Calculating with Coleman-Liau formula
    float L = (float)letters / words * 100;
    float S = (float)sentences / words * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    //Cheching the range of index in order to display the right message
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.f\n", index);
    }
}

int count_letters(char text[])
{
    int letters = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        // converting uppercase letters to lowercase
        if (isupper(text[i]))
        {
            text[i] = tolower(text[i]);
        }
        //Checking is the character is a letter
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            letters++;
        }
    }
    return letters;
}

int count_words(char text[])
{
    // setting words to 1 because we are checking for spaces and the last word wont count
    int words = 1;

    for (int i = 0; i < strlen(text); i++)
    {
        //Checking is the character is space and then increment the 'words'
        if (text[i] == ' ')
        {
            words++;
        }
    }

    return words;
}

int count_sentences(char text[])
{
    int sentences = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        //Checking if the character is '.', '!' or '?' and increment the 'sentences'
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}