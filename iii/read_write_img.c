/*
 *                      read_write_img.c
 *
 *         Assignment: CS40 HW2 -- iii
 *         Authors: Yingyang Liang & Ale Trujillo
 *         Date: Oct 4, 2021
 *
 *         This file contains the functions used to read and write a pbm file 
 *         using pnmrdr. This implementation uses bit2.h to keep track of the 
 *         values of the pixels in the image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pnmrdr.h>

#include "bit2.h"
#include "except.h"
#include "exceptions.h"

/* 
 * This function takes in a an open file stream containing an image and returns 
 * a bit 2D array filled with the values of the image's pixels. It uses pnmrdr 
 * to read the file's header and raster. It will raise a CRE if it is not a 
 * portable bitmap file, if either the width or height are 0, and of a pixel is 
 * not either 1 or 0. 
 */
Bit2_T read_img(FILE *fp)
{
    /* Read in file and get file type, width, and height */
    Pnmrdr_T rdr = Pnmrdr_new(fp);

    if (rdr == NULL) {
        RAISE(Invalid_File);
    }

    Pnmrdr_mapdata map = Pnmrdr_data(rdr);
    int width = (int)map.width;
    int height = (int)map.height;
    Pnmrdr_maptype type = map.type;

    /* Ensure file is a pbm (type 1) */
    if ((type != 1) || (width <= 0) || (height <= 0)) {
        RAISE(Invalid_File);
    }

    Bit2_T bit_array = Bit2_new(width, height);

    /* Goes through pixels one by one and adds them to the bit 2D array */
    for (int row = 0; row < height; row++) {

			for (int col = 0; col < width; col++) {
                int num = (int)Pnmrdr_get(rdr);
                
                /* Check that no number is either 1 or 0 */
                if (num != 1 && num != 0) {
                    RAISE(Invalid_Number);
                }

                Bit2_put(bit_array, col, row, num);
            }
    }

    /* Close the reader and return the array */
    Pnmrdr_free(&rdr);
    return bit_array;
}

/*
 * Function used by the Bit2_map function that prints every individual pixel. 
 * It will also add LF at the end of every row except for the last row.
 * Takes in the index (col, row) of a pixel, an image ina 2D bit array format, 
 * and a file stream to print the output to.
 */
void print_pixel(int col, int row, Bit2_T img, int bit, void *out_file)
{
    int width = Bit2_width(img);
    int height = Bit2_height(img);
    char bit_ch;

    if (out_file == NULL) {
        RAISE(Input_Null);
    }

    /* Get the character pertaining to the bit value. */
    if (bit == 1) {
        bit_ch = '1';
    } else {
        bit_ch = '0';
    }

    fprintf((FILE *)out_file, "%c ", bit_ch);
    
    /*
     * Prints new line at the end of each row and omits newline at the end of 
     * the last row
     */
    if ((col == width - 1) && (row != height - 1)) {
        fprintf((FILE *)out_file, "\n");
    }
    
}

/*
 * Takes in a file stream and a bit 2D array and prints to the given stream a 
 * plain format portable bit map based on the values of the pixels stored in 
 * the array. Raises CREs if given file stream is NULL or width or height are 0.
 */
void write_pbm(FILE *out_file, Bit2_T img)
{
    int width = Bit2_width(img);
    int height = Bit2_height(img);

    if (out_file == NULL) {
        RAISE(Input_Null);
    }

    /* Ensure array's width and height is not 0. */
    if ((width == 0) || (height == 0)) {
        RAISE(Input_Null);
    }

    /* Print pbm header */
    fprintf(out_file, "P1\n%d %d\n", width, height);
    /* Print pixels */
    Bit2_map_row_major(img, print_pixel, out_file);
}