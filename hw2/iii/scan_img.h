/*
 *                      scan_img.h
 *
 *         Assignment: CS40 HW2 -- iii
 *         Authors: Yingyang Liang & Ale Trujillo
 *         Date: Oct 4, 2021
 *
 *         This file contains the declaration for the functions used to analyze 
 *         an image for the unblackedges program. This file need the bit2.h 
 *         file for its implementation.
 */


#ifndef SCAN_IMG_INCLUDED
#define SCAN_IMG_INCLUDED

typedef struct Pixel *Pixel;

/*
 * Compare function that takes in two pixels and return 0 if they are equal and 
 * 1 otherwise.
 */
int cmp_pixels(const void *p1, const void *p2);

/*
 * Hash function that takes in a pixel and returns a unique unsigned number 
 * that can be used as a unique key.
 */
unsigned hash_pixel(const void *pixel);

/* Takes in a pixel and a closure argument (can be NULL). Frees given pixel. */
void free_pixel(const void *pixel, void *cl);

/* 
 * Takes in a 2D bit array containing the values of pixels in an image, a 
 * queue, and a set. It will go through the edge pixels and call the push_pixel 
 * function on each. 
 */
void scan_edges(Bit2_T *img, Seq_T *queue, Set_T *visited);

/*
 * Takes in a 2D bit array containing the values of pixels in an image, an 
 * index (col,row), a queue, and a set (visited). It pushes pixels into add 
 * the queue and "visited" set if they are not already in the set and are black.
 * Raises CRE if it is not able to allocate memory for a new pixel.
 */
void push_pixel(Bit2_T *img, int col, int row, Seq_T *queue, Set_T *visited);

/*
 * Takes in a pixel, a 2D bit array, a queue, and a set. Turns the pixel white 
 * and calls the push_pixel function on all its neighbors (one row above and 
 * below, one column more and less).
 */
void convert_and_push_neighbors(struct Pixel *pixel,
                                Bit2_T *img,
                                Seq_T *queue,
                                Set_T *visited);

#endif