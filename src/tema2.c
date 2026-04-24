#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct piata
{
    //int ind;
    int nr;
    struct piata *urm;
} P;
typedef struct Elem
{
    char zi[50];
    int abs;
    char nume[20];
    struct Elem *urm;
} NOD;
typedef struct oportunitate
{
    NOD *left,*right;
} OP;

//PUSH,STIVA
void push(P**cap,int n)
{
    P* new = (P*)malloc(sizeof(P));
    //new->ind = i;
    new->nr = n;
    new->urm = *cap;
    *cap = new;
}


//DESCOPERA CAPUL STIVEI:
int varf(P *cap)
{
    if (cap == NULL) return -1;
    return cap->nr;
}


//SCOATE DIN STIVA
int pop(P **cap)
{
    if(cap == NULL)return -1;
    P *temp = (*cap);
    int aux = temp->nr;
    *cap = (*cap)->urm;
    free(temp);
    return aux;
}


//CREARE COADA
OP * creare_coada()
{
    OP *q;
    q = (OP*)malloc(sizeof(OP));
    if(q==NULL)return NULL;
    q->right=q->left=NULL;
    return q;
}


//PUSH COADA
void add_coada(OP*q,char data[50],int v,char sir[20])
{
    NOD* new = (NOD*)malloc(sizeof(NOD));
    new->abs=v;
    strcpy(new->nume,sir);
    strcpy(new->zi,data);
    new->urm = NULL;
    if(q->left == NULL)q->left = new;
    else
    {
        (q->left)->urm = new;
        (q->left)=new;
    }
    if(q->right == NULL)q->right=q->left;
}


//ELIMIN ELEM DIN COADA
void rem_coada(OP*q,FILE *out)
{
    NOD *aux;
    int d;
    char sir[20],data[50];
    aux = q->right;
    d=aux->abs;
    strcpy(sir,aux->nume);
    strcpy(data,aux->zi);
    q->right = (q->right)->urm;
    if(q->right == NULL)
        q->left = NULL;
    else
        q->right->urm = NULL;
    free (aux);
    fprintf(out,"%s\n%d\n\%s\n",data,d,sir);
}
int main()
{
    P *cap1 = NULL;
    P *cap2 = NULL;
    P *cap3 = NULL;
    FILE *in = fopen("piata.txt","rt");
    FILE *out = fopen("oportunitati.txt","wt");
    int n1, n2, n3, pret1, pret2, pret3, elem_coada=0;
    char nume1[20];
    char nume2[20];
    char nume3[20];
    int nr;
    OP* q;
    q = creare_coada();
    fscanf(in, "%s", &nume1);
    while(fscanf(in,"%d",&nr) ==  1)
    {
        n1++;
        push(&cap1,nr);
    }
    fscanf(in, "%s", &nume2);
    while(fscanf(in, "%d",&nr) == 1)
    {
        n2++;
        push(&cap2,nr);
    }
    fscanf(in, "%s", &nume3);
    while(fscanf(in, "%d",&nr) == 1)
    {
        n3++;
        push(&cap3,nr);
    }
    return 0;
}