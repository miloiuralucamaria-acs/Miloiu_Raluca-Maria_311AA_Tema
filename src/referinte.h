#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct piata
{
    float nr;
    struct piata *urm;
} P;
typedef struct Elem
{
    int zi;
    float abs;
    char nume[30];
    struct Elem *urm;
} NOD;
typedef struct oportunitate
{
    NOD *left,*right;
} OP;
void push(P**cap,float n);
float varf(P *cap);
float pop(P **cap);
OP * creare_coada();
void add_coada(OP*q,int data,float v,char sir[30]);
void rem_coada(OP*q,FILE *out);