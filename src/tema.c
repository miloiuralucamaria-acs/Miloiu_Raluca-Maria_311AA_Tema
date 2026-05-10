#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "referinte.h"

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
    int n, m=0, adancime = 0, tr[11][11];
    //FIXARE MATRICE TRASEU CU 0:
    for(int i=0;i<m;i++)
        for(int j=0;j<n-1;j++)tr[i][j]=0;
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

    //CREARE ARBORE:
    for(int j=0;j<m;j++)
        root = insert(root, nume[j],n-1,j,pret,adancime);

    //AFISARE LEGATURI:
    traseu(root,nume,tr,m,0);

    for(int i=0;i<m;i++)
        for(int k=i+1;k<m;k++)
        {
            int egal = 0;
            for(int j=0;j<n-1;j++)
            {
                if(tr[j][i] == tr[j][k])
                {
                    egal = 1;
                    continue;
                }
            }
            if(egal == 0)fprintf(g,"%s-%s\n",nume[i],nume[k]);
        }
    fclose(f);
    fclose(g);
    return 0;
}