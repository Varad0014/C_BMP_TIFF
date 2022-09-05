Student Name/ID
Kritin Potluru IMT2020027
Riddhi Chatterjee IMT2020094
Manas Agrawal IMT2020059
Pratham Dandale IMT2020038
Saket Gurjar IMT2020520
Varad Badhe IMT2020048
--------------------------------
How to build:
1. Write "make my_project". This will create executable "my_project".
2.Run command "./my_project <source_image> <destination_image>"
3.Write "make clean". This will remove the executable "my_project" and all the .o files.
4. Destination image is generated in the specified directory.
 (or)
1.Write "make source_file.o". This will create object files(.o) from source files(.c).
2.Write "make my_project". This will use all the .o files to make the executable.
3.Run command "./my_project <source_image> <destination_image>"
4.Write "make clean". This will remove the executable "my_project" and all the .o files.
5.Destination image is generated in the specified directory.

--------------------------------

Work Distribution:
Reading BMP header and DIB_HEADER,researching TIFF tags - Kritin Potluru(IMT2020027)
Writing the TIFF Header and tags,researching TIFF header,pointers and unions - Manas Agrawal(IMT2020059)
Reading the colour table from BMP image,free memory function,researching colourtable format of BMP - Varad Badhe(IMT2020048)
Converting BGR colour format to RGB,researching TIFF colourtable - Pratham Dandale(IMT2020038)
Writing colour table into TIFF file,creating makefile,Initial header file containing structures - Riddhi Chatterjee(IMT2020094)
Implementing command line arguments, main function and research about BMP format - Saket Gurjar(IMT2020520)


