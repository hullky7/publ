/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    int n = atoi(argv[1]);
    if(n < 0 || n > 100)
	{
		printf("The index of resize must be a positive integer <= 100.\n");
		return 2;
	}

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
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
        return 5;
    }

    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    BITMAPFILEHEADER bf_out;
    bf_out = bf;
    BITMAPINFOHEADER bi_out;
    bi_out = bi;

    bi_out.biWidth = bi.biWidth * n;
    bi_out.biHeight = bi.biHeight * n;
    int padding_out = (4 - (bi_out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi_out.biSizeImage = (bi_out.biWidth * sizeof(RGBTRIPLE) + padding_out) * abs(bi_out.biHeight);
    bf_out.bfSize = bi_out.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER and BITMAPINFOHEADER
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int m = 0; m < n; m++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int k = 0; k < n; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over padding in infile
            fseek(inptr, padding, SEEK_CUR);
            // write padding in outfile
            for (int l = 0; l < padding_out; l++)
            {
                fputc(0x00, outptr);
            }
            // return to begin of scanline
            fseek(inptr, -(bi.biWidth * 3 + padding ), SEEK_CUR);
        }
    // go to the end of scanline
    fseek(inptr, bi.biWidth * 3 + padding, SEEK_CUR);
    }

    // close infile and outfile
    fclose(inptr);
    fclose(outptr);

    // if success
    return 0;
}

