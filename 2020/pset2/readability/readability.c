#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
void grade(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");

    // printf("%i letter(s)\n", count_letters(text));
    // printf("%i word(s)\n", count_words(text));
    // printf("%i sentence(s)\n", count_sentences(text));
    grade(count_letters(text), count_words(text), count_sentences(text));

}


// counts the number of letters that show up in the text
int count_letters(string text)
{
    int count = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            count++;
        }
    }

    return count;
}


// counts the number of words in a sentence
int count_words(string text)
{
    int count = 0;

    // find the number of spaces
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 32)
        {
            count++;
        }
    }

    // add 1 for number of words
    return count + 1;
}


// determine the number of sentences
int count_sentences(string text)
{
    int count = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            count++;
        }
    }

    return count;
}

void grade(int letters, int words, int sentences)
{
    float L = (float)(letters * 100) / words;
    float S = (float)(sentences * 100) / words;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.f\n", round(index));
    }
}