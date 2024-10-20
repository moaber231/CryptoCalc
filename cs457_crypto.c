#include "cs457_crypto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
void *OneTimePadKey;
char T[26][26];
char **scytale;
char **rail;
char *NotAlpha;
char *Alpha;
struct Sub
{
    char *buffer;
    int length;
    int *D;
};
struct Sub *s;

/*-------------ONE TIME PAD-------------------*/
static void OneTimePadOutput(void *buffer, int size)
{
    printf("\nDEMICAL VALUES:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", *((unsigned char *)buffer + i));
    }
    printf("\n");
}
void RandomKeyGenarator(int size)
{
    int Fd = open("/dev/urandom", O_RDONLY);
    if (Fd < 0)
    {
        perror("\n There is no such file ");
    }
    else
    {
        OneTimePadKey = malloc(size);
        read(Fd, OneTimePadKey, size);
    }
}
void one_time_pad_encr(void *PlainText, void *Key)
{
    printf("PLAIN TEXT:%s\n", (char *)PlainText);
    OneTimePadOutput(PlainText, strlen(PlainText));
    printf("\nKEY:\n");
    OneTimePadOutput(OneTimePadKey, strlen(PlainText));
    for (int i = 0; i < strlen((char *)PlainText); i++)
    {
        *((char *)PlainText + i) = (*((char *)PlainText + i) ^ *((char *)Key + i));
    }
    printf("\nCYPHER TEXT:\n%s", (char *)PlainText);
    OneTimePadOutput(PlainText, strlen(PlainText));
}

void one_time_pad_decr(void *CypherText, void *Key)
{
    for (int i = 0; i < strlen((char *)CypherText); i++)
    {
        *((char *)CypherText + i) = (*((char *)CypherText + i) ^ *((char *)Key + i));
    }
    printf("\nDECRYPTED TEXT:%s\n", (char *)CypherText);
    OneTimePadOutput(CypherText, strlen(CypherText));
    return;
}
/*-------------END-------------------*/

/*---------AFFINE------------*/
void affine_encr(void *PlaintText)
{
    int size = strlen((char *)PlaintText);
    for (int i = 0; i < size; i++)
    {
        if (*(char *)(PlaintText + i) != ' ')
        {
            int x;
            int flag = 0;
            if ((*(char *)(PlaintText + i)) >= 65 && (*(char *)(PlaintText + i)) <= 90)
            {
                x = (*(char *)(PlaintText + i)) - 65;
            }
            if ((*(char *)(PlaintText + i)) >= 97 && (*(char *)(PlaintText + i)) <= 122)
            {
                flag = 1;
                x = (*(char *)(PlaintText + i)) - 97;
            }
            *(char *)(PlaintText + i) = (5 * x + 8) % 26;
            if (flag == 0)
            {
                *(char *)(PlaintText + i) += 65;
            }
            else
            {
                *(char *)(PlaintText + i) += 97;
            }
        }
    }
}
void affine_decr(void *CypherText)
{
    int size = strlen((char *)CypherText);
    for (int i = 0; i < size; i++)
    {
        if (*(char *)(CypherText + i) != ' ')
        {
            int y;
            int flag = 0;
            if ((*(char *)(CypherText + i)) >= 65 && (*(char *)(CypherText + i)) <= 90)
            {
                y = (*(char *)(CypherText + i)) - 65;
            }
            if ((*(char *)(CypherText + i)) >= 97 && (*(char *)(CypherText + i)) <= 122)
            {
                flag = 1;
                y = (*(char *)(CypherText + i)) - 97;
            }
            *(char *)(CypherText + i) = 21 * (y - 8) % 26;
            if (y - 8 < 0)
                *(char *)(CypherText + i) += 26;
            if (flag == 0)
            {
                *(char *)(CypherText + i) += 65;
            }
            else
            {
                *(char *)(CypherText + i) += 97;
            }
        }
    }
}
/*-----------------END------------------*/

/*----------SUBSTITUTION--------------------*/
static void findWordsOfSizeN(char *f, int n, char *str)
{
    FILE *F = fopen(f, "r");
    char *line = NULL;
    size_t size = 0;
    ssize_t s;
    while ((s = getline(&line, &size, F)) != -1)
    {
        if (s - 1 == n)
        {
            int flag = 0;
            for (int i = 0; i < strlen(str); i++)
            {
                if (str[i] != '*')
                {
                    if (tolower(str[i]) != tolower(line[i]))
                    {
                        flag = 1;
                    }
                }
            }
            if (flag == 0)
                printf("%.*s\n", n, line);
        }
    }
    free(line);
    fclose(F);
}
int N = 2;
static void SubDecoding(int c, char from, char to)
{
    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < s[i].length; j++)
        {
            if (tolower(s[i].buffer[j]) == tolower(from) && s[i].D[j] != 1)
            {
                if (isupper(s[i].buffer[j]))
                {
                    s[i].buffer[j] = toupper(to);
                }
                else
                {
                    s[i].buffer[j] = tolower(to);
                }
                s[i].D[j] = 1;
            }
            if (s[i].D[j] != 1 && s[i].buffer[j] != ' ' && s[i].buffer[j] != '\n')
            {
                printf("*");
            }
            else
            {
                printf("%c", s[i].buffer[j]);
            }
        }
        printf(" ");
    }
    char str[20];
    printf("\nEnter a partialy decrypted word:");
    scanf("%s", str);
    findWordsOfSizeN("words.txt", strlen(str), str);
}
static int DecodingDone(int counter)
{
    for (int i = 0; i < counter; i++)
    {
        for (int j = 0; j < s[i].length; j++)
        {
            if ((s[i].buffer[j] >= 65 && s[i].buffer[j] <= 90) || (s[i].buffer[j] >= 97 && s[i].buffer[j] <= 122))
            {
                if (s[i].D[j] != 1)
                    return 0;
            }
        }
    }
    return 1;
}
static int find_numbers_of_words(char *b)
{
    int counter = 0, size = strlen(b);
    int last_space = 0;
    for (int i = 0; i <= size; i++)
    {
        if (b[i] == ' ' || b[i] == '\n' || i == size)
        {
            if (i - last_space > 0)
            {
                counter++;
                struct Sub *temp = realloc(s, counter * sizeof(struct Sub));
                s = temp;
                s[counter - 1].length = i - last_space;
                s[counter - 1].D = malloc(sizeof(int) * s[counter - 1].length);
                s[counter - 1].buffer = malloc(i - last_space);
                strncpy(s[counter - 1].buffer, b + last_space, i - last_space);
                s[counter - 1].buffer[i - last_space] = '\0';
                last_space = i + 1;
            }
        }
    }
    return counter;
}
static void output_Sub(int counter)
{
    for (int i = 0; i < counter; i++)
    {
        printf("%s ", s[i].buffer);
    }
    printf("\n");
}
static void destroy_sub(int counter)
{
    for (int i = 0; i < counter; i++)
    {
        free(s[i].buffer);
        free(s[i].D);
    }
    free(s);
}
static void calculate_frequency_file(char *f, int *arr)
{
    FILE *F = fopen(f, "r");
    char c;
    int counter = 0;
    printf("\nFile:\n");
    while ((c = fgetc(F)) != EOF)
    {
        if (isalpha(c))
        {
            islower(c) ? arr[c - 97]++ : arr[c - 65]++;
            counter++;
        }
    }
    for (int i = 0; i < 26; i++)
    {
        printf("%c:%f\n", 65 + i, (double)arr[i] / (double)counter);
    }
    fclose(F);
}
static void calculate_frequency_text(char *text, int *arr)
{
    int size = strlen(text);
    printf("\nCYPHERTEXT:\n");
    for (int i = 0; i < size; i++)
    {
        islower(text[i]) ? arr[text[i] - 97]++ : arr[text[i] - 65]++;
    }
    printf("\n");
    for (int i = 0; i < 26; i++)
    {
        printf("%c:%f\n", 65 + i, (double)arr[i] / (double)size);
    }
}
void Substitution_decryptor(void *CypherText)
{
    int counter = find_numbers_of_words((char *)CypherText);
    int arr_file[26] = {0}, arr_cypher[26] = {0};
    calculate_frequency_text(CypherText, arr_cypher);
    calculate_frequency_file("words.txt", arr_file);
    while (DecodingDone(counter) != 1)
    {
        char f, t;
        printf("\n  Show a mapping\n(From/To)");
        scanf(" %c %c", &f, &t);
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        SubDecoding(counter, t, f);
    }
    printf("Decoded Text:\n");
    output_Sub(counter);
    destroy_sub(counter);
}
/*-----------END---------------*/
static void create_Trimethius()
{
    int i, j;
    for (i = 0; i < 26; i++)
    {
        for (j = 0; j < 26; j++)
        {
            T[i][j] = 65 + (i + j) % 26;
        }
    }
}
void NonAlpha(char *Text)
{
    char *d = Text, *sr = Text;
    int size = strlen(Text);
    int j = 0;
    NotAlpha = malloc(size);
    Alpha = malloc(size);
    for (int i = 0; i < size; i++)
    {
        if (isalpha(*(char *)(Text + i)))
        {
            *d++ = Text[i];
            NotAlpha[j] = (char)-1;
        }
        else
        {
            NotAlpha[j] = Text[i];
        }
        j++;
    }
    *d = '\0';
}
static void RestoreNotAlpha(char *Text)
{
    int sizej = strlen(Text);
    int sizei = strlen(NotAlpha);
    int j = 0;
    for (int i = 0; i < sizei; i++)
    {
        if (NotAlpha[i] == (char)-1)
        {
            NotAlpha[i] = Text[j];
            j++;
        }
    }
    strcpy(Text, NotAlpha);
}
void trithemius_encr(void *PlaintText)
{
    create_Trimethius();
    int j = 0;
    NonAlpha(((char *)PlaintText));
    int size = strlen((char *)PlaintText);
    for (int i = 0; i < size; i++)
    {
        int counter = i;
        char *ptr = (char *)PlaintText + i;
        *ptr = isupper(*ptr) ? T[counter % 26][*ptr - 65] : tolower(T[counter % 26][*ptr - 97]);
    }
}

void trithemius_decr(void *CypherText)
{
    int size = strlen((char *)CypherText);
    for (int i = 0; i < size; i++)
    {
        int counter = i;
        char *ptr = (char *)CypherText + i;
        *ptr = isupper(*ptr) ? T[25 - (i % 26)][*ptr - 65] : tolower(T[25 - (i % 26)][*ptr - 97]);
        if (*ptr == 90)
            *ptr == 65;
        else if (*ptr == 122)
            *ptr = 97;
        else
            *ptr = *ptr + 1;
    }
    RestoreNotAlpha((char *)CypherText);
    return;
}
/*-----------------END--------------------*/

static void output_scytale(void *Text, int rods)
{
    for (int i = 0; i < rods; i++)
    {
        for (int j = 0; j < rods; j++)
        {
            if (i >= (rods / 2) + 1 && j == 0)
            {
                printf("|");
            }
            if (i == (rods / 2) && (j == 0))
            {
                printf("---");
                if (scytale[i][j] == '\0')
                {
                    printf("|  ");
                }
                else
                {
                    printf("|  %c  ", scytale[i][j]);
                }
            }
            else
            {
                if (i < rods / 2)
                {
                    printf(" ");
                    printf("  |  %c ", scytale[i][j]);
                    if (j == rods - 1)
                        printf(" ");
                }
                else
                {
                    printf("  |  %c  ", scytale[i][j]);
                }
            }
            if (i >= (rods / 2) + 1 && j == rods - 1)
                printf("|");
            if (i == (rods / 2) && (j == rods - 1))
            {
                printf("|---");
            }
            if (i < rods / 2 && j == rods - 1)
            {
                printf("|  |");
            }
        }
        printf("\n");
    }
}
void scytale_encr(void *PlaintText, int rods)
{

    scytale = malloc(sizeof(char *) * rods);
    for (int i = 0; i < rods; i++)
    {
        scytale[i] = malloc(rods);
    }
    int k = 0;
    NonAlpha(((char *)PlaintText));
    int size = strlen((char *)PlaintText);
    int i = 0, j = 0;
    while (i != rods)
    {
        j = 0;
        while (j != rods)
        {
            scytale[i][j] = *(char *)(PlaintText + k);
            j++;
            k++;
            if (k >= size)
                break;
        }
        i++;
    }
    output_scytale(PlaintText, rods);
    k = 0;
    i = 0, j = 0;
    while (i != rods)
    {
        j = 0;
        while (j != rods)
        {

            if (scytale[j][i] != '\0')
            {
                *(char *)(PlaintText + k) = scytale[j][i];
            }
            j++;

            if (j != rods && scytale[j][i] != '\0')
            {
                k++;
            }
            if (k >= size)
                break;
        }
        k++;
        i++;
    }
}

void scytale_decr(void *CypherText, int rods)
{
    int k = 0;
    int size = strlen((char *)CypherText);
    int i = 0, j = 0;
    k = 0;
    i = 0, j = 0;
    while (i != rods)
    {
        j = 0;
        while (j != rods)
        {

            if (scytale[i][j] != '\0')
            {
                *(char *)(CypherText + k) = scytale[i][j];
            }
            j++;

            if (j != rods && scytale[i][j] != '\0')
            {
                k++;
            }
            if (k >= size)
                break;
        }
        k++;
        i++;
    }
    for (int i = 0; i < rods; i++)
    {
        free(scytale[i]);
    }
    RestoreNotAlpha((char *)CypherText);
    free(scytale);
    return;
}
/*-------------END-------------------------*/
/*------------------RAIL FENCE------------------*/
void rail_fence_encr(void *PlaintText, int rails)
{
    NonAlpha((char *)PlaintText);
    int size = strlen((char *)PlaintText);
    char *alpha = malloc(size);
    int kk = 0;
    for (int i = 0; i < size; i++)
    {
        alpha[kk] = *((char*)PlaintText + i);
        kk++;
    }
    rail = malloc(sizeof(char *) * rails);
    for (int i = 0; i < rails; i++)
        rail[i] = malloc(size);
    int k = 0;
    int flag = 0;
    int rail_counter = 0;
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < rails; i++)
        {
            if (i == k)
            {
                rail[i][j] = alpha[rail_counter];
                rail_counter++;
            }
            else
            {
                rail[i][j] = '.';
            }
            if (rail_counter >= size)
                break;
        }
        if (k == 0)
        {
            flag = 0;
        }
        if (k == rails - 1)
        {
            flag = 1;
        }
        if (flag == 0)
        {
            k++;
        }
        else
        {
            k--;
        }
    }
    for (int i = 0; i < rails; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%c ", rail[i][j]);
        }
        printf("\n");
    }
    rail_counter = 0;
    for (int i = 0; i < rails; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (rail[i][j] != '.')
            {
                alpha[rail_counter] = rail[i][j];
                rail_counter++;
            }
        }
    }
    rail_counter = 0;
    for (int i = 0; i < size; i++)
    {
        *((char*)PlaintText + i) = alpha[rail_counter];
        rail_counter++;
    }
    free(alpha);
}

void rail_fence_decr(void *CypherText, int rails)
{

    int size = strlen((char *)CypherText);
    int counter = 0;
    int rail_counter = 0;
    for (int j = 0; j < counter; j++)
    {
        for (int i = 0; i < rails; i++)
        {
            if (rail[i][j] != '.')
            {
                *(char *)(CypherText + rail_counter) = rail[i][j];
                rail_counter++;
            }
        }
    }
    for (int i = 0; i < rails; i++)
        free(rail[i]);

    RestoreNotAlpha((char *)CypherText);
    //free(rail);
}