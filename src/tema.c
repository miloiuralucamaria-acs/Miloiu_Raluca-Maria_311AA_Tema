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

N *Nou_nou(char data[5], int ad)
{
    N* nod = (N*) malloc (sizeof(N));
    nod->actiuni = (L*)malloc(sizeof(L));
    strcpy(nod->actiuni->simbol, data);
    nod->actiuni->next = NULL;
    nod->stanga = nod->dreapta = NULL;
    nod->adancime = ad;
    return nod;
}

void add_lista(N* nod, L* nou, char data[5])
{
    L *p = nod->actiuni;
    while(p->next != NULL) p = p->next;
    p->next = nou;
    p = nou;
}

N* insert(N* nod, char data[5], int ziua_finala, int actiune, float pret[50][50], int adancime)
{
    if(nod == NULL) nod = Nou_nou(data, adancime);
    else if(nod->adancime == adancime)
    {
        L* nou = (L*)malloc(sizeof(L));
        nou->next = NULL;
        strcpy(nou->simbol, data);
        add_lista(nod, nou, data);
    }
    if(adancime>=ziua_finala)return nod;
    if(pret[adancime+1][actiune] < pret[adancime][actiune]) 
        nod->stanga = insert(nod->stanga, data, ziua_finala, actiune, pret, adancime+1);
    else
        nod->dreapta = insert(nod->dreapta, data, ziua_finala, actiune, pret, adancime+1);
    return nod;
}

void traseu(N* root, char nume[11][5], int tr[11][11], int m, int indice)
{
    if(root == NULL)return;
    if(indice != 0)
    {
        L *p = root->actiuni;
        while(p!=NULL)
        {
            int i=0;
            while(i<m)
            {
                if(strcmp(nume[i], p->simbol) == 0)
                {
                    tr[(root->adancime)-1][i] = indice;
                    break;
                }
                i++;
            }
            p = p->next;
        }
    }
    traseu(root->stanga, nume, tr, m, 1);
    traseu(root->dreapta, nume, tr, m, 2);
}
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