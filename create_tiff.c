#include "bitmap2tiff.h"

void insert_s(char *array, int start, int num)
{
    union short_char sc;
    sc.sn = num;
    for(int i=0;i<2;i++)
        *(array + start + i) = sc.s[i];
}

void insert_i(char *array, int start, int num)
{
    union int_char ic;
    ic.in = num;
    for(int i=0;i<4;i++)
        *(array + start + i) = ic.i[i];
}
void create_tiff(struct bitmapinfoheader *bih, struct tiffheader *th , char *name)
{
    FILE *fp;
    int i;
    th->length = bih->height;
    th->width = bih->width;
    th->bits_per_pixel = 182;    //This value is a pointer to the actual value of BitsPerSample..
    th->stripoffset = 204;   //This is the byte from where the image data starts..
    th->XResolution = 188;     //This value is a pointer to the actual value of XResolution..
    th->YResolution = 196;    //This value is a pointer to the actual value of YResolution..
    fp = fopen(name , "wb");
    char *array;
    array = (char *)malloc(sizeof(char) * 13);
            //TIFF File header..
    /*  LSB is stored first..  */
    *(array + 0) = 0x49;
    *(array + 1) = 0x49;         

    /*  TIFF Version Number..  */
    *(array + 2) = 0x2A;  
    *(array + 3) = 0x00;

    /*  Offset to the first IFD..  */
    *(array + 4) = 0x08; 
    for(int i=5;i<8;i++)         
        *(array + i) = 0x00;       
      // here the header ends..
    
    insert_s(array, 8, 14);   // next 2 bytes == no. of IFD in the tiff file = 14 in this file..
    fwrite(array, 1, 10, fp);
    
        // Tag Name : NewSubfileType
    insert_s(array, 0, 254);  // First IFD..
    insert_s(array, 2, 4);
    insert_i(array, 4, 1);
    insert_i(array, 8, 0);
    fwrite(array, 1, 12, fp);
    
        // Tag Name : ImageWidth
    insert_s(array, 0, 256);
    insert_s(array, 2, 3);
    insert_i(array, 4, 1);
    insert_i(array, 8, th->width);
    fwrite(array, 1, 12, fp);
    
        // Tag Name : ImageLength
    insert_s(array, 0, 257);
    insert_s(array, 2, 3);
    insert_i(array, 4, 1);
    insert_i(array, 8, th->length);
    fwrite(array, 1, 12, fp);
    
        // Tag Name : BitsPerSample
    insert_s(array, 0, 258);
    insert_s(array, 2, 3);
    insert_i(array, 4, 3);
    insert_i(array, 8, th->bits_per_pixel);
    fwrite(array, 1, 12, fp);
    
        // Tag Name : Compression
    insert_s(array, 0, 259);
    insert_s(array, 2, 3);
    insert_i(array, 4, 1);
    insert_i(array, 8, 1);
    fwrite(array, 1, 12, fp);
    
        // Tag Name : PhotometricInterpretation
    insert_s(array, 0, 262);
    insert_s(array, 2, 3);
    insert_i(array, 4, 1);
    insert_i(array, 8, 2);
    fwrite(array, 1, 12, fp);

        // Tag Name : StripOffsets
    insert_s(array, 0, 273);
    insert_s(array, 2, 3);
    insert_i(array, 4, 1);     // StripsPerImage = 1
    insert_i(array, 8, th->stripoffset);
    fwrite(array, 1, 12, fp);

        // Tag Name : SamplesPerPixel
    insert_s(array, 0, 277);
    insert_s(array, 2, 3);
    insert_i(array, 4, 1);
    insert_i(array, 8, 3);
    fwrite(array, 1, 12, fp);

       // Tag Name : RowsPerStrip
    insert_s(array, 0, 278);
    insert_s(array, 2, 4);
    insert_i(array, 4, 1);
    insert_i(array, 8, th->length);
    fwrite(array, 1, 12, fp);

       // Tag Name : StripByteCounts
    insert_s(array, 0, 279);
    insert_s(array, 2, 4);
    insert_i(array, 4, 1);    //StripsPerImage = 1
    insert_i(array, 8, th->length * th->width * 3);
    fwrite(array, 1, 12, fp);

       // Tag Name : XResolution
    insert_s(array, 0, 282);
    insert_s(array, 2, 5);
    insert_i(array, 4, 1);
    insert_i(array, 8, th->XResolution);
    fwrite(array, 1, 12, fp);

       // Tag Name : YResolution
    insert_s(array, 0, 283);
    insert_s(array, 2, 5);
    insert_i(array, 4, 1);
    insert_i(array, 8, th->YResolution);
    fwrite(array, 1, 12, fp);

       // Tag Name : PlanarConfiguration
    insert_s(array, 0, 284);
    insert_s(array, 2, 3);
    insert_i(array, 4, 1);
    insert_i(array, 8, 1);
    fwrite(array, 1, 12, fp);
   
       // Tag Name : ResolutionUnit
    insert_s(array, 0, 296);
    insert_s(array, 2, 3);
    insert_i(array, 4, 1);
    insert_i(array, 8, 2);
    fwrite(array, 1, 12, fp);

     // Adding 0's to file which mark the ending of the IFD..
    for(i=0;i<12;i++)
        *(array + i) = 0x00;
    fwrite(array, 1, 4, fp);

     // Adding the actual value for BitsPerSample as 8,8,8 .. 
    for(i=0;i<6;i+=2)
        insert_s(array, i, 8);
    fwrite(array, 1, 6, fp);
    
     // Adding the actual value of XResolution..
    insert_i(array, 0, ceil(bih->Hresolution * 39.37));
    insert_i(array, 4, 1);
    fwrite(array, 1, 8, fp);

     // Adding the actual value of YResolution..
    insert_i(array, 0, ceil(bih->VResolution * 39.37));
    insert_i(array, 4, 1);
    fwrite(array, 1, 8, fp);
    fclose(fp);
}