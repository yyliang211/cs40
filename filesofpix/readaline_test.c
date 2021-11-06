#include "readaline.c"

int main(int argc, char *argv[])
{
    char **datapp;
        if (argc == 1) {
                int num = readaline(stdin, datapp);
        } else {
                for (int i = 1; i < argc; i++) {
                        FILE *fp = fopen(argv[i], "r");
                        if (fp == NULL) {
                                fprintf(stderr, 
                                        "%s: %s %s %s\n",
                                        argv[0], "Could not open file ",
                                        argv[i], "for reading");
                                exit(1);
                        }
                        do_something(fp);
                        fclose(fp);
                }
        }
        return EXIT_SUCCESS;
}