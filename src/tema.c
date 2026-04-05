#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Nod
{
    double valoare;
    double randament;
    struct Nod *urm;
}N;
int main(int argc, char *argv[])
{
    FILE *in = fopen(argv[1], "rt");
    int n;
    N* cap = NULL;
    N* p = NULL;
    fscanf(in,"%d",&n);
    for(int incercare = 0; incercare<n; incercare++)
    {
        N* nou = (N*)malloc(sizeof(N));
        fscanf(in, "%lf",&nou->valoare);
        nou->randament = 0;
        nou->urm = NULL;
        if(cap == NULL)
        {
            cap = nou;
            p = nou;
        }
        else
        {
            p->urm = nou;
            p = nou;
        }
    }
    return 0;
}