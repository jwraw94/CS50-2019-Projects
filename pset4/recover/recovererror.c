#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int main (int argc, char *argv[] )
{

    if (argc != 2)
    {
        fprintf(stderr, "Incorrect usage!\n");
        return 1;
    }

    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");

    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    unsigned char buffer[512];
    fread(buffer, 512, 1, inptr);

    int n = 1;
    FILE* img = NULL;
    //Determine if filename logic if newfile. 1 = is at start.
/*    bool newimg == 1;
*/
    //Check that there is enough space in the remainder of the input to be a jpeg.
    while ( fread(buffer, 512, 1, inptr) == 1)
    {

        //check if currently at the start of a jpeg.
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
/*            if (newimg == 1)
            {*/
                // close any currently opened outfile, as at the start of new image.
                fclose(img);

                //print out the jpeg to a new file, with ascending name.
                char filename[8];
                sprintf(filename, "%03i.jpg", n);

                //Open img out file for write.
                img = fopen(filename, "w");

                //Increase next filename by +1
                n++;
 /*           }
            else
            {
                newimg == 1;
            }*/
        }

        //Write 512 bits to the img file.
        fwrite(buffer, 512, 1, img);

    }

    // close infile
    fclose(inptr);

    // success
    return 0;

}