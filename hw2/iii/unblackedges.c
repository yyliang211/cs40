#include <stdio.h>
#include <stdlib.h>

#include "except.h"
#include "bit2.h"
#include "list.h"
#include "seq.h"
#include "set.h"
#include "exceptions.h"
#include "scan_img.h"
#include "read_write_img.h"

//Ask about missing exception

int main (int argc, char *argv[])
{
    FILE *infile;

    /* Check that only a max of one file is given */    
    if (argc > 2) {    
        RAISE(Incorrect_Usage_Unblackedges);    
    } else if (argc == 2) {    
        /* Attempt to open given file */
        infile = fopen(argv[1], "r");

        if (infile == NULL) {        
            RAISE(Invalid_File);
        }
    } else {
        //TODO: Check if stdin works??
        /* If no file was provided read in from stdin */
        extern FILE *stdin;
        infile = stdin;
    }
    
    /* Read pbm from file  and fill 2D bit array with values */
    Bit2_T img = read_img(infile);

    /* Create list to store pixels to turn white*/
    Seq_T pixels_to_white = Seq_new(0);

    /* Create set to keep track of pixels on the queue, ensure no duplicates */
    Set_T visited = Set_new(0, cmp_pixels, hash_pixel);

    /* Start by scanning edges to find black edge pixels and add them to the list */
    scan_edges(&img, &pixels_to_white, &visited);

    /* Iterates through the list until no more pixels need to be turned white */
    while(Seq_length(pixels_to_white) != 0){
        /* Get pixel to turn white from the list */
        struct Pixel *pixel = (struct Pixel *)Seq_remlo(pixels_to_white);

        /* Turn pixel white and add its neighbors to the list */
        convert_and_push_neighbors(pixel, &img, &pixels_to_white, &visited);
    }

    /* Write image to stdout */
    extern FILE *stdout;
    write_pbm(stdout, img);
    
    /* Close input file */
    fclose(infile);    
    infile = NULL;

    /* Free data structures and pointers used */
    Set_map(visited, free_pixel, NULL);
    Seq_free(&pixels_to_white);
    Bit2_free(&img);
    Set_free(&visited);

    return EXIT_SUCCESS;
}