#include <stdio.h>
extern void *OneTimePadKey;


void one_time_pad_encr(void *PlaintText, void *Key);

void one_time_pad_decr(void *CypherText, void *Key);

void affine_encr(void *PlaintText);

void affine_decr(void *CypherText);

void Substitution_decryptor(void *CypherText);

void trithemius_encr(void *PlaintText);

void trithemius_decr(void *CypherText);

void scytale_encr(void *PlaintText, int rods);

void scytale_decr(void *CypherText, int rods);

void rail_fence_encr(void *PlaintText, int rails);

void rail_fence_decr(void *CypherText, int rails);