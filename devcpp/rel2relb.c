
//
// CONVERTING MS LINK80 REL BITSTREAM TO BYTESTREAM
// https://seasip.info/Cpm/rel.html
//

#include <stdio.h>
#include <stdlib.h>

// Maximum range of bytes
#define MAX 65536

// Filename given as the command
// line argument
int main(int argc, char* argv[])
{
    // Pointers to the files
    FILE* _frel_;
    FILE* _frelb_;

    char byte;
    // Stores the bytes to read
    char data[MAX];

    int i = 0, j = 0, bit = 0, value = 0, size = 0;

    //open REL and RELB files
    _frel_ = fopen(argv[1], "rb");
    _frelb_ = fopen(argv[2], "wb");

    //get size of REL file
    fseek(_frel_, 0L, SEEK_END);
    size = ftell(_frel_);
    fseek(_frel_, 0L, SEEK_SET);

    if (_frel_ == NULL)
    {
        return 1;
    }

    while (i < size)
    {
        byte = fgetc(_frel_);
        bit = 128;
        while (bit > 0)
        {
            value = bit & byte;
            if (value)
                fputc((char)01, _frelb_);
            else
                fputc((char)00, _frelb_);
            bit = bit >> 1;
        }
        i++;
    }

    // Close the files
    fclose(_frel_);
    fclose(_frelb_);

    return 0;
}
