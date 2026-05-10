#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1],"rt");
    FILE *g = fopen(argv[2],"wt");
    if(f == NULL)
    {
        printf("Eroare la deschiderea fisierului 1");
        return 0;
    }
    if(g == NULL)
    {
        printf("Eroare la deschiderea fisierului 2");
        return 0;
    }
    char sir[100],nume[11][5];
    fscanf(f,"%s",sir);
    char *element = strtok(sir, ",");
    float pret[50][50];
    N *root = NULL;
    int n, m=0;

    //CITIRE VECTOR CU NUME-ACTIUNI:
    while(element != NULL)
    {
        strcpy(nume[m], element);
        element = strtok(NULL, ",");
        m++;
    }

    //CITIRE MATRICE CU PRETURI:
    n = 0;
    while(fscanf(f, "%s", sir) != EOF)
    {
        m = 0;
        element = strtok(sir, ",");
        while(element != NULL)
        {
            pret[n][m] = atof(element);
            element = strtok(NULL, ",");
            m++;
        }
        n++;
    }
    fclose(f);
    fclose(g);
    return 0;
}