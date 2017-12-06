/*        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
    */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

    // open input file
    FILE* raw = fopen(infile, "r");
    if (raw == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    uint8_t buffer[512];
    FILE* img;              // create input file
    int counter = 0;        // counter of jpg files
    bool begin = false;     // needfool for declared a first jpg-file
    //int begin = 0;        // another method
    fread(buffer, 512, 1, raw);

    while (fread(buffer, 512, 1, raw) > 0)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 &&
        buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            char filename[8];
            sprintf (filename, "%03i.jpg", counter);
            if (begin == false)
            {
                // open output file and write in it
                img = fopen(filename, "w");
                fwrite (buffer, sizeof(buffer), 1, img);
                begin = true;
            }
            if (begin == true)
            {
                fclose(img);
                img = fopen(filename, "w");
                counter++;
                fwrite (buffer, sizeof(buffer), 1, img);
            }
        }
        else if(begin == true)
        {
                fwrite (buffer, sizeof(buffer), 1, img);
        }
    }
    // close
    if(img)
    {
        fclose (img);
    }
	fclose(raw);
	return 0;
}