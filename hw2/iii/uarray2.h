#ifndef UARRAY2_INCLUDED
#define UARRAY2_INCLUDED

#define T UArray2_T
typedef struct T *T;

/*
 * Creates a new 2D array based on the width and height given and allocates 
 * enough space based on the size of the elements provided.
 * Width, height, and size should all non-negative integers. The function will 
 * return a pointer to a UArray2_T.
 */ 
extern T UArray2_new(int width, int height, int size);

/*
 * Takes in a UArray2_T and returns its width, which corresponds to the columns.
 * The input array must not be NULL and it will return a non-negative integer.
 */
extern int UArray2_width(T uarray2);

/*
 * Takes in a UArray2_T and returns its height, which corresponds to the rows.
 * The input array must not be NULL and it will return a non-negative integer.
 */
extern int UArray2_height(T uarray2);

/*
 * Takes in a UArray2_T and returns the size of a element.
 * The input array must not be NULL and it will return a non-negative integer.
 */
extern int UArray2_size(T uarray2);

/*
 * Takes in a UArray2_T and returns a pointer to an element at (width, height).
 * The input array must not be NULL, and the column and row should be non-
 * negative and within the array's dimensions.
 */
void *UArray2_at(T uarray2, int col, int row);

/*
 * Takes in a UArray2_T, a function pointer and a closure argument and applies 
 * the function to every element in the array given. Row indices vary more 
 * rapidly than column indices.
 * The input array must not be NULL, the function must take in two integers, 
 * referred to as i and j which stand for the indices, a UArray2_T, a pointer 
 * to an element in the array, and a pointer to the closure argument of the 
 * funcition. The closure argument given to UArray2_map_col_major may be NULL 
 * if there is not need to accumulate data. 
 */
extern void UArray2_map_col_major(T uarray2,
                                  void apply(int col,int row, T uarray2, void *elem, void *accum),
                                  void *cl);

/*
 * Takes in a UArray2_T, a function pointer and a closure argument and applies 
 * the function to every element in the array given. Column indices vary more 
 * rapidly than row indices.
 * The input array must not be NULL, the function must take in two integers, 
 * referred to as i and j which stand for the indices, a UArray2_T, a pointer 
 * to an element in the array, and a pointer to the closure argument of the 
 * funcition. The closure argument given to UArray2_map_col_major may be NULL 
 * if there is not need to accumulate data. 
 */
extern void UArray2_map_row_major(T uarray2,
                                  void apply(int col,int row, T uarray2, void *elem, void *accum),
                                  void *cl);

/*
 * Takes in a pointer to a UArray_T and deallocates and clears it.
 * Both the pointer to and the input array must not be NULL.
 */
extern void UArray2_free(T *uarray2);

#undef T
#endif
