#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//TASK2:
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


//TASK3:
typedef struct Lista
{
    char simbol[5];
    int ziua;
    struct Lista *next;
}L;

typedef struct Nod
{
    L *actiuni;
    struct Nod *stanga;
    struct Nod *dreapta;
    int adancime;
}N;
N *Nou_nou(char data[5], int ad);
void add_lista(N* nod, L* nou, char data[5]);
N* insert(N* nod, char data[5], int ziua_finala, int actiune, float pret[50][50], int adancime);
void traseu(N* root, char nume[11][5], int tr[11][11], int m, int indice);


