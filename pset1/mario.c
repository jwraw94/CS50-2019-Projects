#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int height = -1;

    while (height < 0 || height > 23)
    {
        printf("Height: \n");
        height = get_int();
    }

    while (height >= 0 && height <= 23)
    {

        for (int i = 0; i < height; i++)
        {

            for (int j = 0 ; j < height - i - 1; j ++)
            {
                printf("%s", " ");
            }
            for (int k = 0; k < i + 1; k++)
            {
                printf("#");
            }
            printf("  ");
            for (int k = 0; k < i + 1; k++)
            {
                printf("#");
            }
            printf("\n");
        }
        return 0;
    }
}