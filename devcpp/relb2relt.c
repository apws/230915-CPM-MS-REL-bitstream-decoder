
//
// DECODING MS LINK80 REL BITSTREAM FILE (BYTESTREAM from "rel2relb")
// https://seasip.info/Cpm/rel.html
//

#include <stdio.h>
#include <stdlib.h>

// Maximum range of bytes (64K bitstream / bytestream)
#define MAX 65536 * 8

FILE * _frelb_;
FILE * _frelt_;

int i = 0, bit = 0;
char name[9];
char line[80];


int GetByte();
int GetWord();
char GetTypeChar();
int GetLen();
char* GetName();


// Filename given as the command
// line argument
int main(int argc, char* argv[])
{
    // Pointers to the files

    // Stores the bytes to read
    char data[MAX];

    int size = 0;

    //open REL and RELB files
    _frelb_ = fopen(argv[1], "rb");
    _frelt_ = fopen(argv[2], "w");

    //get size of REL file
    fseek(_frelb_, 0L, SEEK_END);
    size = ftell(_frelb_);
    fseek(_frelb_, 0L, SEEK_SET);

    if (_frelb_ == NULL)
    {
        return 1;
    }

    while (i < size)
    {
        //ITEM BEGIN - normal/special
        bit = fgetc(_frelb_);
        i++;

        if (bit)
        {
            //1 special item, 2bit control
            int item2 = 0;
            bit = fgetc(_frelb_);
            item2 |= bit;
            item2<<=1;
            i++;
            bit = fgetc(_frelb_);
            item2 |= bit;
            i++;

            switch (item2)
            {
                case 0: //00 special link item
                {
                    //4bit control
                    int item4 = 0;
                    bit = fgetc(_frelb_);
                    item4 |= bit;
                    item4<<=1;
                    i++;
                    bit = fgetc(_frelb_);
                    item4 |= bit;
                    item4<<=1;
                    i++;
                    bit = fgetc(_frelb_);
                    item4 |= bit;
                    item4<<=1;
                    i++;
                    bit = fgetc(_frelb_);
                    item4 |= bit;
                    i++;

                    switch (item4)
                    {
                        case 0: //0000
                        {
                            char* name = GetName();
                            fprintf(_frelt_, "*SGLOBAL %s\n", name); //or DECLARE/SYMBOL? //just after the module name at the begin
                            break;
                        }
                        case 1: //0001
                        {
                            char* name = GetName();
                            fprintf(_frelt_, "*SCOMMON %s\n", name); // ??? common BLOCK, not segment
                            break;
                        }
                        case 2: //0010
                        {
                            char* name = GetName();
                            fprintf(_frelt_, "*SMODULE %s\n", name); //just one at the begin (NO, may be MORE MODULES !!!)
                            break;
                        }
                        case 3: //0011 unused
                        {
                            fprintf(_frelt_, "*S3 UNUSED\n");
                            break;
                        }
                        case 4: //0100 unused
                        {
                            fprintf(_frelt_, "*S4 UNUSED\n");
                            break;
                        }
                        case 5: //0101
                        {
                            char type = GetTypeChar();
                            int addr = GetWord();
                            char* name = GetName();
                            snprintf(line, 40, "*SCOMMSIZE %-7s %c %04X\n", name, type, addr); // common BLOCK size
                            fprintf(_frelt_, line);
                            break;
                        }
                        case 6: //0110
                        {
                            char type = GetTypeChar();
                            int addr = GetWord();
                            char* name = GetName();
                            snprintf(line, 40, "*SEXTERN %-7s %c %04X\n", name, type, addr); //at the end (chain address extern)
                            fprintf(_frelt_, line);
                            break;
                        }
                        case 7: //0111
                        {
                            char type = GetTypeChar();
                            int addr = GetWord();
                            char* name = GetName();
                            snprintf(line, 40, "*SPUBLIC %-7s %c %04X\n", name, type, addr); //unified with new zmac listing symbol-table //at the end, for each public
                            fprintf(_frelt_, line);

                            break;
                        }
                        case 8: //1000 unused
                        {
                            fprintf(_frelt_, "*S8 UNUSED\n");
                            break;
                        }
                        case 9: //1001
                        {
                            char type = GetTypeChar();
                            int addr = GetWord();
                            snprintf(line, 20, "*SOFFSET %c %04X\n", type, addr); //before address reference
                            fprintf(_frelt_, line);

                            break;
                        }
                        case 10: //1010
                        {
                            char type = GetTypeChar();
                            int addr = GetWord();
                            snprintf(line, 20, "*SDATASIZE %c %04X\n", type, addr); //after publics (A here, okay) // module data size
                            fprintf(_frelt_, line);
                            break;
                        }
                        case 11: //1011
                        {
                            char type = GetTypeChar();
                            int addr = GetWord();
                            snprintf(line, 20, "*SSECTION %c %04X\n", type, addr); //or SECTION? //cseg (prog/text) or dseg
                            fprintf(_frelt_, line);

                            break;
                        }
                        case 12: //1100
                        {
                            char type = GetTypeChar();
                            int addr = GetWord();
                            snprintf(line, 20, "*SLOCAL %c %04X\n", type, addr); //?? NOT SURE ...  LOCAL, really (??? chain address local)
                            fprintf(_frelt_, line);

                            break;
                        }
                        case 13: //1101
                        {
                            char type = GetTypeChar();
                            int addr = GetWord();
                            snprintf(line, 20, "*SCODESIZE %c %04X\n", type, addr); //after publics // module code size (here is P, may be also C as common? why not A if its SIZE ???)
                            fprintf(_frelt_, line);
                            break;
                        }
                        case 14: //1110
                        {
                            char type = GetTypeChar();
                            int addr = GetWord();
                            snprintf(line, 20, "*SEND %c %04X\n", type, addr); //just one at the end (NO, at the each MODULE END !!!)
                            fprintf(_frelt_, line);
                            break;
                        }
                        case 15: //1111
                        {
                            //char type = GetTypeChar();
                            //int addr = GetWord();
                            snprintf(line, 20, "*SEOF\n"); //???? some error? is MISSING in our files ??? (NO, MUST BE AT THE END OF FILE, specific byte??, rest ignored)
                            fprintf(_frelt_, line);
                            break;
                        }

                    }
                    break;
                }

                case 1: //01 program relative (cseg/text ??)
                {
                    int addr = GetWord();
                    char hex4[5];
                    snprintf(hex4, 4, "%04X", addr);
                    fprintf(_frelt_, "*RP %s\n", hex4);
                    break;
                }

                case 2: //10 data relative (dseg/data)
                {
                    int addr = GetWord();
                    char hex4[5];
                    snprintf(hex4, 4, "%04X", addr);
                    fprintf(_frelt_, "*RD %s\n", hex4);
                    break;
                }

                case 3: //11 common relative (??? related ONLY to common BLOCK ???
                {
                    int addr = GetWord();
                    char hex4[5];
                    snprintf(hex4, 4, "%04X", addr);
                    fprintf(_frelt_, "*RC %s\n", hex4);
                    break;
                }
            }


        }
        else
        {
            //0 normal item (byte)
            int itemB = GetByte();
            char hex2[3];
            snprintf(hex2, 2, "%02X", itemB);
            fprintf(_frelt_, "*RB %s\n", hex2);
        }

    }

    // Close the files
    fclose(_frelb_);
    fclose(_frelt_);

    return 0;
}



int GetByte()
{
    int bit;
    int itemB = 0;
    bit = fgetc(_frelb_);
    itemB |= bit;
    itemB<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemB |= bit;
    itemB<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemB |= bit;
    itemB<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemB |= bit;
    itemB<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemB |= bit;
    itemB<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemB |= bit;
    itemB<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemB |= bit;
    itemB<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemB |= bit;
    i++;
    return itemB;
}

int GetWord()
{
    int bit;
    int itemW = 0;
    bit = fgetc(_frelb_);
    itemW |= bit;
    itemW<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemW |= bit;
    itemW<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemW |= bit;
    itemW<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemW |= bit;
    itemW<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemW |= bit;
    itemW<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemW |= bit;
    itemW<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemW |= bit;
    itemW<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemW |= bit;
    itemW<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemW |= bit;
    itemW<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemW |= bit;
    itemW<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemW |= bit;
    itemW<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemW |= bit;
    itemW<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemW |= bit;
    itemW<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemW |= bit;
    itemW<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemW |= bit;
    itemW<<=1;
    i++;
    bit = fgetc(_frelb_);
    itemW |= bit;
    i++;
    int addr = (itemW << 8) & 0xFFFF | (itemW >> 8); //REL is little-endian, real address output !!!
    return addr;
}

char GetTypeChar()
{
    int bit;
    int item2 = 0;
    bit = fgetc(_frelb_);
    item2 |= bit;
    item2<<=1;
    i++;
    bit = fgetc(_frelb_);
    item2 |= bit;
    i++;
    char ch = ' ';
    switch(item2)
    {
        case 0: //00 absolute
        {
            ch = 'A';
            break;
        };
        case 1: //01 program relative
        {
            ch = 'P';
            break;
        };
        case 2: //10 data relative
        {
            ch = 'D';
            break;
        };
        case 3: //11 common relative
        {
            ch = 'C';
            break;
        };
    }
    return ch;
}


int GetLen()
{
    int bit;
    int item3 = 0;
    bit = fgetc(_frelb_);
    item3 |= bit;
    item3<<=1;
    i++;
    bit = fgetc(_frelb_);
    item3 |= bit;
    item3<<=1;
    i++;
    bit = fgetc(_frelb_);
    item3 |= bit;
    i++;
    return item3;
}

char* GetName()
{
    int len = GetLen();
    //char name[9];

    int j = 0;
    while (j < len)
    {
        char ch = GetByte();
        name[j] = ch;
        j++;
    }
    name[j] = 0;
    return name;
}

