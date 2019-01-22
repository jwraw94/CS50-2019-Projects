#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int lengthCalc(long long card_number)
{
    long long length = (log10(card_number) + 1) ;
    return length;
}


int main(void)
{
    // Declare variable to store card number
    long long card_number = 0;

    //Ask user for their card number
    printf("Card Number: \n");
    card_number = get_long_long();

    // size of returns the size in bytes. Use Log???
    long long length = lengthCalc(card_number);

    //Initial quick check for invalid card numbers
    if (length != 13 && length != 15 && length != 16)
    {
        printf("INVALID\n");
        return 0;
    }

    //declare array for the card number
    long long card_number_array[length];
    int individual_number = 0;

    //put card number into an array
    for (int i = 0; i < length; i++)
    {
        individual_number = card_number % 10;
        card_number_array[length - 1 - i] = individual_number;
        card_number = card_number / 10;
    }

    long long k = length;
    long x = 0;
    long doubled_number = 0;
    long doubled_number_sum = 0;
    long other_number_sum = 0;

    while (k > 0)
    {
        other_number_sum = other_number_sum + card_number_array[k - 1];
        k -= 2;
    }

    k = length ;

    while (k > 1)
    {
        doubled_number = 2 * card_number_array[k - 2];

        if (doubled_number >= 10)
        {
            doubled_number = (doubled_number - 10) + 1;
        }

        doubled_number_sum = doubled_number + x;
        x = doubled_number_sum ;
        k -= 2;
    }

    int total_sum = other_number_sum + doubled_number_sum;

    if (total_sum % 10 == 0)
    {
        if (length == 15 && card_number_array[0] == (3) && (card_number_array[1] == (7) || card_number_array[1] == (4)))
        {
            printf("AMEX\n");
        }
        else if ((length == 13 || length == 16)  && (card_number_array[0] == 4))
        {
            printf("VISA\n");
        }
        else if (length == 16 && card_number_array[0] == (5) && (card_number_array[1] == (1) || card_number_array[1] == (2)
                 || card_number_array[1] == (3) || card_number_array[1] == (4) || card_number_array[1] == (5)))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}