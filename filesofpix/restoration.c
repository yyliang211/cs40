#include "read_file.h"

/* print_seq
 * purpose: printing out the raster to stdout
 * arguments: Seq_T seq is a pointer to the hanson sequence
 *            int height is the number of rows of the raster
 *            int width is the number of columns of the raster
 * return: nothing
 */
void print_seq(Seq_T seq, int height, int width)
{
        // printf("printing original sequence: \n");
        for (int i = 0; i < height; i++)
        {
                for (int j = 0; j < width; j++)
                {
                int *all = Seq_get(seq, i);
                printf("%c", *(all + j));
                }
        }
}

/* convert
 * purpose: Takes in a sequence consisting of values of 0-255
 *          representing the raster rows of a P2 pgm
 *          converts it to P5 format and outputs to stdout
 * arguments: Seq_T seq is a pointer to the hanson sequence
 *            int height is the number of rows of the raster
 *            int width is the number of columns of the raster
 * return: nothing
 */
void convert(Seq_T seq, int height, int width)
{
        //header
        printf("P5\n");
        printf("%d %d\n", width, height);
        printf("%d\n", 255);
        //raster
        print_seq(seq, height, width);
}

int main(int argc, char *argv[])
{
        Seq_T seq;
        int width, height;
        if (argc == 1) 
        {
                seq = read_file(stdin, &width, &height);
        }
        else if (argc == 2)
        {
                FILE *fp = fopen(argv[1], "r");
                        if (fp == NULL) {
                                fprintf(stderr, 
                                        "%s: %s %s %s\n",
                                        argv[0], "Could not open file ",
                                        argv[1], "for reading");
                                exit(1);
                        }
                        seq = read_file(fp, &width, &height);
                        fclose(fp);
        }
        else
        {
                fprintf(stderr, "This program takes in at most one file\n");
                exit(1);
        }
        // printf("The height is: %d\nThe width is: %d\n", height, width);
        convert(seq, height, width);
        
        Seq_free(&seq);
        return EXIT_SUCCESS;
}