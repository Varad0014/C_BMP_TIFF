#include "bitmap2tiff.h"

void readbmp(struct bitmapfileheader *header, struct bitmapinfoheader *dibheader, char *source_file)
{
    FILE *fp=fopen(source_file, "rb");
    fseek(fp,10,SEEK_SET);                    //skip to offset 
    fread(&header->bitoffset,sizeof(int),1,fp);
    fseek(fp,18,SEEK_SET);                   //skip to width
    fread(&dibheader->width,sizeof(int),1,fp);
    fread(&dibheader->height,sizeof(int),1,fp);
    fseek(fp,38,SEEK_SET);                  //skip to resolution of dibheader
    fread(&dibheader->Hresolution,sizeof(int),1,fp);
    fread(&dibheader->VResolution,sizeof(int),1,fp);
    fclose(fp);
}


