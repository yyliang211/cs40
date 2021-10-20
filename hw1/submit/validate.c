#include <stdlib.h>
#include <stdio.h>
#include <pnmrdr.h>

void validate(FILE *fp)
{
        Pnmrdr_T image = Pnmrdr_new(fp);
        Pnmrdr_mapdata map = Pnmrdr_data(image);
        int num_pixels = map.height * map.width;
        printf("height: %d\n", map.height);
        printf("width: %d\n", map.width);
	printf("Number is pixels is %d\n", num_pixels);
        for(int i = 0; i < num_pixels; i++)
        {
                char temp = Pnmrdr_get(image);
                printf("%d ", temp);
        }
        Pnmrdr_free(&image);
}

int main(int argc, char *argv[])
{
        if (argc == 1) {
                validate(stdin);
        } else {
                for (int i = 1; i < argc; i++) {
                        FILE *fp = fopen(argv[i], "r");
                        if (fp == NULL) {
                                fprintf(stderr, 
                                        "%s: %s %s %s\n",
                                        argv[0], "Could not open file ",
                                        argv[i], "for reading");
                                exit(1);
                        }
                        validate(fp);
                        fclose(fp);
                }
        }
        return EXIT_SUCCESS;
}