#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Incorrect usage!\n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(argv[1], "r");

    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    // Create a buffer of 521 bytes.
    unsigned char buffer[512];
    int filecount = 0;

    // Pointer to outfile
    FILE *img = NULL;
    char filename[8];

    //Check if in a jpeg already (false)
    int inimage = 0;

    //Check that there is enough space in file for it to be a jpeg.
    while (fread(buffer, 512, 1, inptr) == 1)
    {
        //check if currently at the start of a jpeg.
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //If at start, and an outfile is open, close it. << Else segmentation error :(
            if (inimage == 1)
            {
                // close outfile
                fclose(img);
            }
            else
            {
                //Now the inimage tag can be set to 'true'
                inimage = 1;
            }

            //print out the jpeg to a new file, with ascending name.
            sprintf(filename, "%03i.jpg", filecount);

            //Open img out file for write.
            img = fopen(filename, "w");
            filecount++;
        }

        //Only write the infile to the outfile if it's a jpeg.
        if (inimage == 1)
        {
            fwrite(buffer, 512, 1, img);
        }
    }

    // close outfile
    fclose(img);

    // close infile
    fclose(inptr);

    // success
    return 0;
}