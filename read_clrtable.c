#include "bitmap2tiff.h"

struct colortable **read_RGB(struct bitmapfileheader *bitmapfile, int w, int h, char *source_file)  /*function which returns pointer to 
							 2D array of structures*/
{
    FILE *fpt;
    fpt = fopen(source_file, "rb"); 
    fseek(fpt, bitmapfile->bitoffset, SEEK_SET);   
    struct colortable **ptr = (struct colortable **) malloc(h * sizeof(struct colortable*)); /*memory allocation for array*/
    for (int i = h-1 ; i>=0 ; i--)
    {
        ptr[i] = (struct colortable *) malloc(w * sizeof(struct colortable));
        fread(ptr[i], 3, w, fpt);
        if (w%4 != 0)    /*in case of padding*/
            fseek(fpt, 4-((w*3)%4), SEEK_CUR); /*ignore the padded bytes*/
    }
    fclose(fpt);
    return ptr;
}

void free_mem(struct colortable **pt, int ht)
{
    for (int i=ht-1 ; i>=0 ; i--)
        free (pt[i]);
    free(pt);
}
