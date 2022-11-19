#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // take one argument
    if (argc != 2)
    {
        printf("Correct Input : ./recover filename");
        return 1;
    }

    // if image can`t be read return 1
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file");
        return 1;
    }

    // create a buffer where to store a block
    BYTE buffer[BLOCK];
    int count = 0;
    char output_name[8];
    FILE *output;

    while (fread(&buffer, BLOCK, 1, file) > 0)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // assign 3 decimal digits of number to the output_name
            sprintf(output_name, "%03d.jpg", count);

            // close a file from the 2nd loop
            if (count > 0)
            {
                fclose(output);
            }

            // count
            count++;

            // open a file to write
            output = fopen(output_name, "w");
        }

        if (count > 0)
        {
            fwrite(buffer, BLOCK, 1, output);
        }
    }

    fclose(output);
    fclose(file);
    return 0;
}