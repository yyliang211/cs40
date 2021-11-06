#include "read_file.h"
#include <string.h>

/* separate
 * purpose: read in a line and separate the line into 
 *           non digit bytes and digit bytes
 * arguments: char *line is the line read from readaline
 *            char **digit is the double pointer to store the digit bytes
 *            char **non_digit is the double pointer to store the non digits
 *            size_t line_size is the size of the line
 * return: nothing
 */
void separate(char *line, char **digit, char **non_digit, size_t line_size)
{
    int index     = 0;
    int currn     = 0;
    int currd     = 0;
    *digit        = malloc(line_size);
    *non_digit    = malloc(line_size);

    // while the characters being read is not the terminating character
    // continue to read
    while (line[index] != '\0') {

        // if the character is a digit store into digit
        if ((line[index] <= 57) && (line[index] >= 48)) {
            *(*digit + currd) = line[index];
            currd++;            
        }

        // if the character is a non digit store into non digit
        else {
            if (line[index] != '\n') {
                *(*non_digit + currn) = line[index];
                currn++;
            } 

            // add whitespace between numbers
            // there will be no whitespaces before the first number
            if (currd != 0 && line[index+1] <= 57 && line[index+1] >= 48) {
                *(*digit + currd) = ' ';
                currd++;
            } 
        }
        index++;
    }
    // add terminating characters at the last index
    *(*digit + currd)     = ' ';
    currd++;
    *(*digit + currd)     = '\0';
    *(*non_digit + currn) = '\0';
}


/* elements
 * purpose: counts the numbers in a row of the original image (i.e. width)
 * arguments: char *digits is a string that holds the digits with space in btw
 * return: int elements which is the width of the original image row
 */
int elements(char *digits)
{
    int i = 0;
    int counter = 0;
    while(digits[i] != '\0') 
    {
        if (digits[i] == ' ')
        {
            counter++;
        }
        i++;
    }
    return counter;
    
    // int number   = 0;
    // int elements = 0;
    // while((number = (int) strtol(digits, &digits, 10))) {
    //     elements++;
    // };

    // return elements;
}

/* digitArray
 * purpose: creates an integer array from the digits stored in the string
 * arguments: char *digits is a string that holds the digits with space in btw
 *            int **arr is a pointer that holds the array of digits 
 *            int num_elements is the width of the original image
 * return: nothing
 */
void digitArray(char *digits, int **arr, int num_elements)
{
    
    // int number = 0;
    // int index  = 0;
    // char *pEnd = digits;
    // *arr = malloc(num_elements * sizeof(int));
    // while((number = (int) strtol(pEnd, &pEnd, 10))) {
        // *(*arr + index) = number;
    //     index++;
    // };

    *arr = malloc(num_elements * sizeof(int));
    int index = 0;
    char c_arr[4];
    //counter for digits
    int i = 0;
    //counter for char array
    int j = 0;
    int num;
    while(digits[i] != '\0')
    {
        if (digits[i] != ' ')
        {
            c_arr[j] = digits[i];
            i++;
            j++;
        }
        else
        {
            c_arr[j] = '\0';
            num = atoi(c_arr);
            *(*arr + index) = num;
            memset(c_arr, 0, 4);
            j = 0;
            index++;
            i++;
        }
    }
}

/* read_file
 * purpose: uses hanson table, hanson atom, and hanson sequence. The key of 
 *          table is atom string of non digit bytes and value is an integer 
 *          array storing the digit bytes. 
 * arguments: FILE *fp is a file pointer to be read
 *            int *width is pointer to the width of the raster
 *            int *height is pointer to the height of the raster
 * return: a sequence back to main holding the entire raster in the end
 */
Seq_T read_file(FILE *fp, int *width, int *height)
{
    assert(fp);

    char *line      = NULL;
    char *digit     = NULL;
    char *non_digit = NULL;
    int *value      = NULL;
    int *last_value = NULL; 
    int *prev_array = NULL;
    int num_elem    = 0;

    // store the read line into *line 
    size_t line_size = readaline(fp, &line);
    // printf("printing line: %s\n", line);
    
    // create table
    Table_T mytable = Table_new(2, NULL, NULL);

    // create sequence
    Seq_T myseq = Seq_new(10);
    
    while (line_size != 0) {
        // separate the read line into digits and non digits
        separate(line, &digit, &non_digit, line_size);
        // printf("digits: %s\n", digit);
        // printf("non-digits: %s\n", non_digit);
        
        // creating an integer array that stores the digits 
        // which are values for table
        num_elem = elements(digit);
        digitArray(digit, &value, num_elem);

        // printf("number of digits: %d\n", num_elem);
        // printf("printing value: ");
        // for (int i = 0; i < num_elem; i++)
        // {
        //     printf("%d ", value[i]);
        // }
        // printf("\n");
        
        // create atom string which are keys for table
        const char *key = Atom_string(non_digit);

        // if the key doesn't exist add in the key value pair
        // if the key does exist add in the new value and return the previous
        if (Table_get(mytable, key) == NULL) {
            Table_put(mytable, key, value);
            // printf("inserting first row: ");
            // for (int i = 0; i < num_elem; i++)
            // {
            // printf("%d ", value[i]);
            // }
            // printf("\n");
        
        } else {
            prev_array = Table_put(mytable, key, value);
            Seq_addhi(myseq, prev_array);
            last_value = Table_get(mytable, key);
        }

        // free(line);
        // free(digit);
        // free(non_digit);
        line_size = readaline(fp, &line);
        // *(line + (int)line_size - 1) = '\0';
    }
    // printf("After storing into table the value in table becomes the following:");
    // for (int i = 0; i < num_elem; i++) {
    //     int *val = Table_get(mytable, key);
    //     printf("%d ", val[i]);
    // }
    Seq_addhi(myseq, last_value); 

    int length = Seq_length(myseq);
    *height    = length;
    *width     = num_elem; 

    // printf("\n%s: %d\n", 
    //        "The number of rows in the original image is", length);
   
    // for (int i = 0; i < length; i++) {
    //     printf("The digits in the %d index of the sequence is: ", i);
    //     for (int j = 0; j < num_elem; j++) {
    //         int *all = Seq_get(myseq, i);
    //         printf("%d ", *(all + j));
    //     }
    //     printf("\n");
    // }
    


    free(line);
    free(digit);
    free(non_digit);
    return myseq;
    // Seq_free(&myseq);
    // Table_free(&mytable);
}

