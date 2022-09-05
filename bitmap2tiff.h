        /* Include this file as #include "bitmap2tiff.h" */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// Defining structures and unions.

struct bitmapfileheader             // Structure for the bitmap file header
{
    int bitoffset;
};

struct bitmapinfoheader         // Structure for the bitmap information header
{
    int width, height;
    unsigned int Hresolution, VResolution;
};

struct colortable         // Color Table from the bitmap file
{
    unsigned char B, G, R;
};

struct tiffheader       // Structure for the tiff header
{
    short lsb;
    int bits_per_pixel, length, width, stripoffset;
    unsigned int XResolution, YResolution;
};

// Defining the union to insert the information in the file..

union short_char
{
    short sn;
    char s[2];
};

union int_char
{
    int in;
    char i[4];
};


void create_tiff(struct bitmapinfoheader *, struct tiffheader * , char *);
void insert_s(char *, int, int);
void insert_i(char *, int, int);
void readbmp(struct bitmapfileheader *, struct bitmapinfoheader *, char *);
void write_tiff(struct colortable **,int ,int , char *);
struct colortable **interchange(struct colortable **,int ,int);
struct colortable **read_RGB(struct bitmapfileheader *, int , int, char *);
void free_mem(struct colortable **, int);