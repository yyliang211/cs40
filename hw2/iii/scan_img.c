/*
 *                      scan_img.c
 *
 *         Assignment: CS40 HW2 -- iii
 *         Authors: Yingyang Liang & Ale Trujillo
 *         Date: Oct 4, 2021
 *
 *         This file contains the functions used to analyze an image for the 
 *         unblackedges program. It contains the Pixel struct, used to store a 
 *         pixel's index (col, row). Functions in this file include pushing 
 *         pixels to a queue used to store pixels that need to be turned white, 
 *         a function to scan the edges, and a function to turn the pixels 
 *         white and check on the pixel's neighbors. It also contains the 
 *         compare and hash functions used by the Hanson set. 
 */

#include <stdio.h>
#include <stdlib.h>

#include "mem.h"
#include "bit2.h"
#include "seq.h"
#include "set.h"
#include "except.h"
#include "exceptions.h"

/* 
 * Struct used to track pixel in the image to turn white, hidden from the 
 * client.
 */
struct Pixel {
    int row;
    int col;
};

/* 
 * Compare function used by the Hanson set. Function takes in two pixels and 
 * returns 0 if they are equal and 1 if they are not.
 */
int cmp_pixels(const void *p1, const void *p2) {
        struct Pixel *pixel1 = (struct Pixel *)p1;
        struct Pixel *pixel2 = (struct Pixel *)p2;

        if (pixel1 != NULL && pixel2 != NULL) {
            if ((pixel1->col == pixel2->col) && (pixel1->row == pixel2->row)) {
                return 0;
            } else {
                return 1;
            }
        } else {
            RAISE(Input_Null);
        }
        return 1;
}

/* 
 * Hash function used by the Hanson set. Function takes in a pixel and returns  * a unique unsigned int that is used as a key to map the values inside the set.
 */
unsigned hash_pixel(const void *pixel) {
        struct Pixel *p = (struct Pixel *)pixel;
        if (p != NULL) {
            int col = p->col;
            int row = p->row;
            /* Hash using Szudzik's function that maps 2 ints to 1 int. */
            return (col >= row ? col * col + col + row : col + row * row);
        } else {
            RAISE(Input_Null);
        }
        return -1;
}


/*
 * This function takes in an image, queue, set, and index (as col and row).
 * It uses the image to find the pixel based on the index. It will then only 
 * add it to the queue to turn white if it is black and is not yet in the set. 
 */
void push_pixel(Bit2_T *img, int col, int row, Seq_T *queue, Set_T *visited)
{
    int width = Bit2_width(*img);
    int height = Bit2_height(*img);

    /*
     * Check current pixel is within width and height, if not: return (do not 
     * exit).
     */
    if ((col >= width) || (col < 0) || (row >= height) || (row < 0)) {
        return;
    }

    int pixel_value = Bit2_get(*img, col, row);

    /*
     * Check to see if pixel is black, if it is create a struct Pixel, which 
     * can be added to the set and queue if needed.
     */
    if ((pixel_value == 1)) {
        struct Pixel *pixel;
        NEW(pixel);

        if (pixel == NULL) {
            RAISE(Malloc_Fail);
        }

        pixel->col = col;
        pixel->row = row;

        /*
         * Add it to both the queue and the set only if it has not been visited 
         * (i.e. is not a member of the set)
         */
        if ((Set_member(*visited, pixel) != 1)) {
            Seq_addhi(*queue, pixel);
            Set_put(*visited, pixel);
        } else {
            /* If we already visited it, we can get rid of it and free it. */
            FREE(pixel);
        }
    }
}

/*
 * This function takes in an image, a queue, and a set. It will get the width 
 * and height of the image so it can go though all the pixels on the edges. We 
 * call on a function to put the pixels on the queue if they are black and have 
 * not seen them yet (i.e. are not part of the set, here called visited)
 */
void scan_edges(Bit2_T *img, Seq_T *queue, Set_T *visited)
{
    int width = Bit2_width(*img);
    int height = Bit2_height(*img);
    
    /* Adds pixels on horizontal edges to queue */
    for (int col = 0; col < width; col++) {
        push_pixel(img, col, 0, queue, visited);
        push_pixel(img, col, height - 1, queue, visited);
    }

    /* Adds pixels on vertical edges to queue */
    for (int row = 0; row < height; row++) {
        push_pixel(img, 0, row, queue, visited);
        push_pixel(img, width - 1, row, queue, visited);
    }
}


/* 
 * This funcion takes in a pixel that was just popped off the queue, an image, 
 * a queue, and a set. It will take the pixel, turn it white and then call on 
 * all its neighbors to be pushed on the queue if they are also black and have 
 * not been visited yet.
 */
void convert_and_push_neighbors(struct Pixel *pixel,
                                Bit2_T *img,
                                Seq_T *queue, 
                                Set_T *visited)
{
    int row = pixel->row;
    int col = pixel->col;
    /* Turn pixel white by changing its value to 0. */
    Bit2_put((Bit2_T)*img, col, row, 0);

    /* Check if all the neighbors have to be turned white. */
    push_pixel(img, col - 1, row, queue, visited);
    push_pixel(img, col + 1, row, queue, visited);
    push_pixel(img, col, row - 1, queue, visited);
    push_pixel(img, col, row + 1, queue, visited);
}

/*
 * Function used by the Set_map to free all the pixels after the end of the 
 * program.
 */
void free_pixel(const void *pixel, void *cl) {
    (void)cl;
    free((struct Pixel *)pixel);
}