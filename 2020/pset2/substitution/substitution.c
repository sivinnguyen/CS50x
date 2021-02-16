#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


bool isValid(string key);
void encipher(string text, string key);

int main(int argc, string argv[])
{
    // check number of arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // validate key
    if (!isValid(argv[1]))
    {
        return 1;
    }

    string text = get_string("plaintext:  ");

    printf("ciphertext: ");
    encipher(text, argv[1]);
    printf("\n");

    return 0;
}


// encrypts messages using Caesar’s cipher
void encipher(string text, string key)
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
                // replace the letter according to the mapping determined by the key: c = key[index]
                // preserve case: c = toupper(c)
                c = toupper(key[text[i] - 65]);
            }
            else
            {
                c = tolower(key[text[i] - 97]);
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
    const int l = strlen(key);

    // check key length
    if (l != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    // check for non-alphabetic characters
    for (int i = 0; i < l; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must be alphabetic characters\n");
            return false;
        }
    }

    // check for duplicated characters
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < l; j++)
        {
            if ((i != j) && (tolower(key[i]) == tolower(key[j])))
            {
                printf("Duplicated characters\n");
                return false;
            }
        }
    }

    return true;
}