/*
 *                      read_board.c
 *
 *         Assignment: CS40 HW2 -- iii
 *         Authors: Yingyang Liang & Ale Trujillo
 *         Date: Oct 4, 2021
 *
 *         This file contains the function to read in a file from a given input 
 *         stream and populates a 2D array with the values of a sudoky board. 
 *         It will raise CREs if given an invalid file and a file that does not 
 *         meet the requirements for a sudoku board. It needs uarray2.h for its 
 *         implementation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pnmrdr.h>

#include "except.h"
#include "uarray2.h"
#include "exceptions.h"

/*
 * Takes in an open file stream and a pointer to a 2D array. Uses pnmrdr to 
 * read in the values pertaining to a sudoku board and adds them to the array. 
 * Raises CREs if the pixels maximum density is not 9, if there are any pixels 
 * with density smaller than 1 or bigger than 9, and the file is not graymap 
 * file.
 */
void read_board(FILE *fp, UArray2_T *array)
{
    /* Read in file and get file type, width, height, and max val */
    Pnmrdr_T rdr = Pnmrdr_new(fp);
    Pnmrdr_mapdata map = Pnmrdr_data(rdr);
    unsigned width = map.width;
    unsigned height = map.height;
    unsigned maxval = map.denominator;
    Pnmrdr_maptype type = map.type;
    
    /* Ensure file is a pgm, is a 9x9 image and maximum pixel density is 9 */
    if ((type != 2) || (width != 9) || (height != 9) || (maxval != 9)) {
        RAISE(Invalid_File);
    }

    for (int row = 0; row < 9; row++) {

			for (int col = 0; col < 9; col++) {
                int num = (int) Pnmrdr_get(rdr);
                
                /* Check that no number is less than 1 or more than 9 */
                if (num < 1 || num > 9) {
                    RAISE(Invalid_Number);
                }

                int *elem = UArray2_at(*array, col, row);
                *elem = num;
                
            }
    }
    Pnmrdr_free(&rdr);
}