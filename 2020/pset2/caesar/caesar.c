#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool isValid(string key);
void encipher(string text, int key);

int main(int argc, string argv[])
{
    // check number of arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // validate key
    if (!isValid(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);
    string text = get_string("plaintext:  ");

    printf("ciphertext: ");
    encipher(text, key);
    printf("\n");

    return 0;
}


// encrypts messages using Caesar’s cipher
void encipher(string text, int key)
{
    const int l = strlen(text);
    char c;

    for (int i = 0; i < l; i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                // convert ascii to alphabetical index: int index = text[i] - 65
                // shift alphabetical index using formular ci = (pi + k) % 26: int shift = (index + k) % 26
                // conver result back to ascii: char c = shift + 65
                c = ((text[i] - 65 + key) % 26) + 65;
            }
            else
            {
                c = ((text[i] - 97 + key) % 26) + 97;
            }
            printf("%c", c);
        }
        else
        {
            printf("%c", text[i]);
        }
    }
}


// validate argument
bool isValid(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isdigit(key[i]))
        {
            return false;
        }
    }

    return true;
}