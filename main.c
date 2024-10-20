#include "cs457_crypto.h"

#include <stdio.h>

#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#include <stdlib.h>

#define N 10000
int main(int argv, char **argc)
{
    FILE *f = NULL;
    char c;
    int option;
    char buffer[N];
    int i = 0;
    if (argv == 2)
    {
        f = fopen(argc[1], "rb+");
        if (f == NULL)
        {
            perror("\n There is no such file ");
        }
        while ((c = fgetc(f)) != EOF)
        {
            buffer[i] = c;
            i++;
        }
        fclose(f);
    }
    else if (argv == 1)
    {
        printf("Provide the text :\n");
        scanf("%[^\n]", buffer);
    }
    printf("Select Encryption/Decryption Algorith:\n(1/One Time Pad)\n(2/Affine)\n(3/Substitution)\n(4/Trimethius)\n(5/Scytale)\n(6/Rail)\n");
    scanf("%d", &option);
    switch (option)
    {
    case 1:

        RandomKeyGenarator(strlen(buffer));

        one_time_pad_encr(buffer, OneTimePadKey);

        one_time_pad_decr(buffer, OneTimePadKey);
        break;
    case 2:
        affine_encr(buffer);
        printf("\nENCRYPTED:%s\n", (char *)buffer);
        affine_decr(buffer);
        printf("\nDECRYPTED:%s\n", (char *)buffer);
        break;
    case 3:
        Substitution_decryptor(buffer);
        break;
    case 4:
        trithemius_encr((void*)&buffer);
        printf("\nENCRYPTED:\n%s", (char *)buffer);
        trithemius_decr((void*)&buffer);
        printf("\nDECYPTED:\n%s", (char *)buffer);
        break;
    case 5:
        int rods;
        printf("\nInput a greater than 0 integer:\n");
        scanf("%d", &rods);
        scytale_encr(buffer, rods);
        printf("\nencrypted:\n%s", (char *)buffer);
        scytale_decr(buffer, rods);
        printf("\ndecrypted:\n%s", (char *)buffer);
        break;
    case 6:
        int rails;
        printf("\nInput a greater than 0 integer:\n");
        scanf("%d", &rails);
        rail_fence_encr(buffer, rails);
        printf("\nencrypted:\n%s", (char *)buffer);
        rail_fence_decr(buffer, rails);
        printf("\ndecrypted:\n%s", (char *)buffer);
        break;
    default:
        break;
    }
    return 0;
}