#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //Check that a key & enough keys have been supplied
    if (argc != 2)
    {
        printf("ERROR\n");
        return 1;
    }

    string key = argv[1];
    int i = 0;
    int key_length = 0;
    key_length = strlen(key);

    //Check that the key is only letters - (isalpha for no letters/nums/other)

    for (i = 0; i < key_length; i++)
    {
        if (isalpha(key[i]) == false)
        {
            printf("ERROR\n");
            return 1;
        }
    }

    printf("plaintext: ");
    string plaintext = get_string();

    int length = strlen(plaintext);

    printf("ciphertext: ");

    int k = 0;
    int n = 0;

    for (int j = 0; j < length; j++)
    {
        k = (j - n) % key_length ; 
        
        //Ignore all non letters, and increase n to keep place in the cipher
        if (65 > plaintext[j] || (90 < plaintext[j] && plaintext[j] < 97)  || plaintext[j] > 122)
        { 
            printf("%c", plaintext[j]);
            n++;
        }
        else if (isupper(plaintext[j]) && isupper(key[k]))
        {
            printf("%c", ((((plaintext[j] + key[k]) - 130) % 26) + 65));
        }
        else if (islower(plaintext[j]) && islower(key[k]))
        {
            printf("%c", ((((plaintext[j] + key[k]) - 194) % 26) + 97));
        }
        else if (islower(plaintext[j]) && isupper(key[k]))
        {
            printf("%c", ((((plaintext[j] + key[k]) - 162) % 26) + 97));
        }
        else if (isupper(plaintext[j]) && islower(key[k]))
        {
            printf("%c", ((((plaintext[j] + key[k]) - 162) % 26) + 65));
        }
        
        else
        {
            printf("%c", plaintext[j]);
        }
    }
    printf("\n");
    return 0;
}