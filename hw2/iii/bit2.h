/*
 *                      bit2.h
 *
 *         Assignment: CS40 HW2 -- iii
 *         Authors: Yingyang Liang & Ale Trujillo
 *         Date: Oct 4, 2021
 *
 *         This is the Bit2_T header file. Bit2_T is a  
 *         2D bit array with each bit being 0 or 1.
 */

#ifndef BIT2_INCLUDED
#define BIT2_INCLUDED

#define T Bit2_T
typedef struct T *T;

/* 
* Takes in width and height as integers, creates and returns Bit2_T
* using those dimensions.
* Raises CRE if width and height are less than 1.
*/
extern T Bit2_new(int width, int height);

/* 
* Takes in a Bit2_T and returns its width.
* Raises CRE if Bit2_T is NULL.
*/
extern int Bit2_width(T bit_array);

/* 
* Takes in a Bit2_T and returns its height.
* Raises CRE if Bit2_T is NULL.
*/
extern int Bit2_height(T bit_array);

/* 
* Takes in a Bit2_T, a 2D index as ints col, row and a bit.
* Sets bit in [col][row] to [bit] and returns the previous value of bit.
* Raises CRE if bit is not 0 or 1, if Bit2_T is NULL or if given index is
* out of bounds.
*/
extern int Bit2_put(T bit_array, int col, int row, int bit);

/* 
* Takes in a Bit2_T, a 2D index as ints col, row.
* Returns bit in [col][row].
* Raises CRE if bit is not 0 or 1, if Bit2_T is NULL or if given index is
* out of bounds.
*/
extern int Bit2_get(T bit_array, int col, int row);

/* 
* Takes in a Bit2_T, apply function and closure argument.
* Traverses 2D array in col-major order and calls apply function on 
* each element.
* Returns nothing.
* Raises CRE if Bit2_T is NULL.
*/
extern void Bit2_map_col_major(T bit_array,
    void apply(int col, int row, Bit2_T array, int bit, void *accum),
    void *cl);

/* 
* Takes in a Bit2_T, apply function and closure argument.
* Traverses 2D array in row-major order and calls apply function on 
* each element.
* Returns nothing.
* Raises CRE if Bit2_T is NULL.
*/
extern void Bit2_map_row_major(T bit_array,
    void apply(int col, int row, Bit2_T array, int bit, void *accum),
    void *cl);

/* 
* Takes in a pointer to Bit2_T.
* Frees Bit2_T.
* Returns nothing.
* Raises CRE if Bit2_T or pointer to Bit2_T is NULL.
*/
extern void Bit2_free(T *bit_array);

#undef T
#endif