#include "bitmap2tiff.h"

void write_tiff(struct colortable **p, int height, int width, char *name)  //Takes input of a 2-D array of structures and the height and width of the image
{
    int i,j;
    FILE *fp;
    fp = fopen(name, "ab");  //Opens the target file and stores the FILE pointer
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            fwrite((*(p+i)+j),sizeof(*(*(p+i)+j)),1,fp);  //Writes each structure of the 2-D array into the target file
        }
    }
    fclose(fp);  //Closes the target file 
}
