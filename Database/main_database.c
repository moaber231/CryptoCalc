#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc == 6)
    {
        if (strcmp(argv[1], "kv") != 0)
        {
            printf("kv needs to be as first argument");
            exit(EXIT_FAILURE);
        }
        if (strcmp(argv[2], "add") != 0)
        {
            printf("add needs to be as second argument");
            exit(EXIT_FAILURE);
        }
        if (strcmp(argv[3], "-f") != 0)
        {
            printf("-f needs to be as thrid argument");
            exit(EXIT_FAILURE);
        }
    }
    else if (argc == 7)
    {
    }
    else
    {
        printf("False number of args");
    }
    return 0;
}