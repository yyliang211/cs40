/*
 *                      read_write_img.h
 *
 *         Assignment: CS40 HW2 -- iii
 *         Authors: Yingyang Liang & Ale Trujillo
 *         Date: Oct 4, 2021
 *
 *         This file contains the functions used to read and write a pbm file 
 *         using pnmrdr. This implementation uses a 2D bit array using bit2.h 
 *         to keep track of the values of the pixels in the image.
 */

#ifndef READ_WRITE_IMG_INCLUDED
#define READ_WRITE_IMG_INCLUDED

/* 
* Takes in an opened file stream to an image and returns a 2D bit array 
* containing the values of the pixels in the image.
* Raises CRE if the file given is not a valid portable bitmap.
*/
Bit2_T read_img(FILE *fp);

/* 
* Takes in a file stream used to print the output to and a 2D bit array 
* containing the values of the pixels in an image.
* Raises CRE if width and height are less than 1 or if file stream is NULL.
*/
void write_pbm(FILE *out_file, Bit2_T img);

/* 
* Takes in an index (col, row), a 2D bit array containing the values of the 
* pixels in an image, an integer value of a bit, and an output file stream. 
* Prints the individual pixel and LF if at the end of a row.
* Raises CRE if given file stream is NULL.
*/
void print_pixel(int col, int row, Bit2_T img, int bit, void *out_file);

#endif