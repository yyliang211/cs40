#include "read_file.h"

// Takes in the line, separates the infused and original characters
// and stores them in strings non_dig and digits
void separate(char *line, char **non_dig, char **digits)
{
    int j = 0;
    int k = 0;
    for (int i = 0; line[i] != '\0'; i++)
    {
        //if current char is a digit
        if (line[i] <= 57 && line[i] >= 48)
        {
            *(*digits + j) = line[i];
            j++;
        }
        //if current char is infused/fake
        else
        {
            //add whitespace between numbers
            if(i != 0)
            {
                *(*digits + j) = ' ';
                j++;
            }
            *(*non_dig + k) = line[i];
            k++;
        }
    }
    *(*digits + j) = '\0';
    *(*digits + k) = '\0';
}

//Takes in file pointer, outputs populated table
Table_T read_file(FILE *fp)
{
        //strings for the line that we are reading in
        char *line;
        size_t line_size = readaline(fp, &line);
        //character array to store infused non-digits and original digits of each row
        char *non_dig;
        char *digits;
        //key for table
        const char *key;
        //value for table
        

        //table
        Table_T table = Table_new(2, NULL, NULL);

        //while still reading in lines
        while(line_size != 0)
        {
            List_T value = List_list(NULL);
            non_dig = malloc(line_size);
            digits = malloc(line_size);
            separate(line, &non_dig, &digits);
            printf("line you wrote: %s\n", line);
            printf("infused chars: %s\n", non_dig);
            printf("original chars: %s\n", digits);

            key = Atom_string(non_dig);
            printf("atom: %s\n", key);
            value = List_push(value, digits);

            //if this key is inserted before i.e. this is the key-value representing the uncorrupted data
            if(Table_get(table, key) != NULL)
            {
                printf("in conditional\n");
                //prev_value is pointer pointing to value (List)
                List_T prev_value = Table_get(table, key);
                printf("table get\n");
                prev_value = List_append(prev_value, value);
                printf("table append\n");

                char **array = (char **)List_toArray(prev_value, NULL);
                printf("1");
                printf("first element of list %s", array[0]);
                printf("second element of list %s", array[1]);
                prev_value = Table_put(table, key, prev_value);
            }
            else
            {
                Table_put(table, key, value);
            }
            free(line);
            free(non_dig);
            free(digits);
            List_free(&value);
            line_size = readaline(fp, &line);
        }
        return table;
}