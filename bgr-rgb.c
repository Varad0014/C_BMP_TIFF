#include "bitmap2tiff.h"

struct colortable **interchange(struct colortable **p, int h, int w)      //Takes a 2-D array of structure to convert BGR into RGB
{
    int i,j,k;
    for(i=0; i < h ; i++)        //Reads the row of array of structure
    {
        for(j=0;j<w;j++)        //Reads the set of BGR and swaps it with RGB
        {
            k = p[i][j].R;
            p[i][j].R = p[i][j].B;
            p[i][j].B = k;

        }
    }
    return p;     //Return the pointer to the array of structure
}