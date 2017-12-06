/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    float n = atof(argv[1]);
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

    // read infile's BITMAPFILEHEADER and BITMAPINFOHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
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
    // Height, width, padding, size and sizeinfo for outfile
    bi_out.biWidth = floor (bi.biWidth * n);
    bi_out.biHeight = floor (bi.biHeight * n);
    int padding_out = (4 - (bi_out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi_out.biSizeImage = (bi_out.biWidth * sizeof(RGBTRIPLE) + padding_out) * abs(bi_out.biHeight);
    bf_out.bfSize = bi_out.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER and BITMAPINFOHEADER
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);

    // create an arrey of pixels
    RGBTRIPLE triple_arr[abs(bi.biHeight)][bi.biWidth];

    //write pisxels of infile to an arrey of pixels
    for (int i = 0; i < abs(bi.biHeight); i++)
        {
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                fread (&triple, sizeof(RGBTRIPLE), 1, inptr);
                triple_arr[i][j] = triple;
            }
        fseek(inptr, padding, SEEK_CUR);
        }

    // iterate over infile's scanlines and write RGB to outfile
    for (int i = 0; i < abs(bi_out.biHeight); i++)
    {
            int row = i / (n);  //definition which rows of pixels must be copied to outfile
            // iterate over pixels in scanline
            for (int j = 0; j < bi_out.biWidth; j++)
            {
                int col = j / (n); //definition which pixels in row must be copied to outfile
                RGBTRIPLE triple_out = triple_arr[row][col];
                // write RGB triple to outfile
                fwrite(&triple_out, sizeof(RGBTRIPLE), 1, outptr);
            }
            // write padding in outfile
            for (int p = 0; p < padding_out; p++)
            {
                fputc(0x00, outptr);
            }
    }
    // close infile and outfile
    fclose(inptr);
    fclose(outptr);

    // if success
    return 0;
}