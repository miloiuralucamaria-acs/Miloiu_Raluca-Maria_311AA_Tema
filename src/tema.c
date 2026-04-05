#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct Nod
{
    double valoare;
    double randament;
    struct Nod *urm;
}N;
int main(int argc, char *argv[])
{
    FILE *in = fopen(argv[1],"rt");
    FILE *out = fopen(argv[2],"wt");
    double valoare_anterioara = 0, rand_mediu = 0, volatilitate = 0, S;
    int n;
    N* cap = NULL;
    N* p = NULL;
    if(in == NULL)
    {
        printf("Fisierul nu se poate deschide!");
        return 0;
    }
    if(out == NULL)
    {
        printf("Fisierul nu se poate deschide!");
        return 0;
    }
    fscanf(in,"%d",&n);
    for(int incercare = 0; incercare<n; incercare++)
    {
        N* nou = (N*)malloc(sizeof(N));
        fscanf(in,"%lf",&nou->valoare);
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
            p->randament = ((p->valoare - valoare_anterioara)/valoare_anterioara);
            rand_mediu = rand_mediu + p->randament;
        }
        valoare_anterioara = p->valoare;
    }
    rand_mediu = (rand_mediu/(n-1));
    p = cap->urm;
    for(int incercare = 1; incercare<n; incercare++)
    {
        volatilitate = (volatilitate + (pow((p->randament - rand_mediu), 2)));
        p = p->urm;
    }
    volatilitate = (sqrt(volatilitate/(n-1)));
    S = trunc((rand_mediu/volatilitate)*1000)/1000.0;
    rand_mediu = trunc(rand_mediu*1000)/1000.0;
    volatilitate = trunc(volatilitate*1000)/1000.0;
    fprintf(out,"%.3lf\n",rand_mediu);
    fprintf(out,"%.3lf\n",volatilitate);
    fprintf(out,"%.3lf",S);
    fclose(in);
    fclose(out);
    return 0;
}