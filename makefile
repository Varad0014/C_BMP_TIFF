all_sources = main.c bgr-rgb.c create_tiff.c rbmp.c read_clrtable.c tiff_final.c
DEPS = bitmap2tiff.h
all_objs = $(all_sources:.c=.o)
my_project : $(all_objs)
	gcc -o my_project $(all_objs) -lm
%.o : %.c $(DEPS)
	gcc -c $<
source_file.o : $(all_sources)
	gcc -c $^
clean:
	rm my_project *.o
