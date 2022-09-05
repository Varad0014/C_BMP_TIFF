#include "bitmap2tiff.h"

int main(int argc , char* argv[])
{
    
    //program to be executed as > ./my_project source_image destination_image       

    struct bitmapinfoheader bih;
    struct bitmapfileheader bfh;
    struct tiffheader th;
    struct colortable **p, **q;
    readbmp(&bfh, &bih , argv[1]);         //To read the bmp file which is taken as input
    create_tiff(&bih, &th , argv[2]);         //To create and write the header information of the tiff file
    p = read_RGB(&bfh, bih.width, bih.height , argv[1]);    //To read the color table from the bmp file
    q = interchange(p, bih.height, bih.width);      //To interchange the blue and red color which are in sets of 3, i.e, from BGR TO RGB
    write_tiff(q, bih.height, bih.width , argv[2]);    //Writing the image data in the previously created tiff file
    free_mem(p, bih.height);     //Free the memory obtained by the array of structures created to store the color data from bmp file
    return 0;
}