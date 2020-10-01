#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_new_jpeg(unsigned char bytes[]);

int main(int argc, char *argv[])
{
    int BUFFER_SIZE = 512;
    int bytes_read = 0;
    unsigned char bytes[BUFFER_SIZE]; //making a buffer of size 512

    if (argc != 2) //error checking
    {
        return 1;
    }

    FILE *file = fopen(argv[1], "r"); //opening the given raw file
   
    bool found_first_jpg = false;
    int count = 0;
    FILE *ofile; //initializing ofile
    while (fread(bytes, BUFFER_SIZE, 1, file)) //reading the infile till the file ends
        if (is_new_jpeg(bytes)) // if new jpeg found
        {
            if (!found_first_jpg)
            {
                found_first_jpg = true;
            }
            else
            {
                fclose(ofile);
            }
            char filename[8];
            sprintf(filename, "%03i.jpg", count); //giving ofile name
            ofile = fopen(filename, "w");//opening ofile to write data
           
            fwrite(bytes, BUFFER_SIZE, 1, ofile); //writing data to ofile
        }
        else if (found_first_jpg) //if no new jpeg is found
        {
            fwrite(bytes, BUFFER_SIZE, 1, ofile); //continue wtiting to the same file
        }
   
}

bool is_new_jpeg(unsigned char bytes[]) //function to check jpeg headers
{
    return (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0);

}
