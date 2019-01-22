// Resizes a BMP file

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage with correctly supplied iputs.
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize, scale, infile, outfile\n");
        return 1;
    }

    // Determine how much to scale up the image.
    int n = atoi(argv[1]);

    if (n < 0 || n > 100)
    {
        fprintf(stderr, "Scale must be a number less that or equal to 100");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newpadding = (4 - (bi.biWidth * 3 * n ) % 4) % 4;

    //Temporary storage.
    BITMAPINFOHEADER boutfo;
    BITMAPFILEHEADER bfile;

    // Set default output values to same as input.
    boutfo = bi;
    bfile = bf;
    boutfo.biWidth = n * bi.biWidth ;
    boutfo.biHeight = n * bi.biHeight ;

    //File size = 3 * height * width + header size + padding
    bfile.bfSize = (3 * boutfo.biWidth * abs(boutfo.biHeight)) + (abs(boutfo.biHeight) * newpadding) + 54;
    boutfo.biSizeImage = bfile.bfSize - 54;

    // SIZE: write bitmap header to outfile
    fwrite(&bfile, sizeof(BITMAPFILEHEADER), 1, outptr);

    // WIDTH & HEIGHT: write bitmap dimensions to outfile
    fwrite(&boutfo, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //Repeat for n
        for (int p = 0; p < n; p++)
        {

            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int m = 0; m < n; m++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // Add the new in padding
            for (int k = 0; k < newpadding; k++)
            {
                fputc(0x00, outptr);
            }

            //Reset where the input is read from, to account for what has already been read.
            if ( p < n - 1 )
            {
                fseek( inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
