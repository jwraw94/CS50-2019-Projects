#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2 || argv[1] < 0)
    {
        printf("Error!\n");
        
        return 1;
    }
    
    int k = atoi(argv[1]);

    int length = 0;

    int i = 0;

    printf("plaintext: ");

    string plaint = get_string();

    length = strlen(plaint);

    printf("ciphertext: ");

    for (i = 0; i < length; i++)
    {
        if (isupper(plaint[i]))
        {
            printf("%c", ((((plaint[i] + k) - 65) % 26) + 65));
        }
        else if (islower(plaint[i]))
        {
            printf("%c", ((((plaint[i] + k) - 97) % 26) + 97));
        }
        else
        {
            printf("%c", plaint[i]);
        }
    }
    printf("\n");
    return 0;
}