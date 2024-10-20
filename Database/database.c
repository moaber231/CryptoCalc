#include "database.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <openssl/evp.h>

void AES_ADD(char* file,int key,int value)
{
    FILE *f=fopen(file,"a+");
    flcose(f);
    return;
}

void AES_READ(char* file,int key,int value)
{
    FILE *f=fopen(file,"a+");
    flcose(f);
    return;
}

void AES_RANGE_READ(char* file,int key,int value)
{
    FILE *f=fopen(file,"a+");
    flcose(f);
    return;
}