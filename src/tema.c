#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//TASK 1:
typedef struct Nod 
{
    double valoare;
    double randament;
    struct Nod *urm;
}N;

//TASK 2:
typedef struct piata
{
    int nr;
    struct piata *urm;
} P;
typedef struct Elem
{
    int zi;
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
    new->nr = n;
    new->urm = *cap;
    *cap = new;
}

//AFLARE CAP STIVA:
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
void add_coada(OP*q,int data,int v,char sir[20])
{
    NOD* new = (NOD*)malloc(sizeof(NOD));
    new->abs=v;
    strcpy(new->nume,sir);
    new->zi=data;
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
    int d, data;
    char sir[20];
    aux = q->right;
    d=aux->abs;
    strcpy(sir,aux->nume);
    data=aux->zi;
    q->right = (q->right)->urm;
    if(q->right == NULL)
    q->left = NULL;
    fprintf(out,"%d\n%d\n%s\n",data,d,sir);
    free (aux);
}

int main(int argc, char *argv[])
{
    int optiune = atoi(argv[1]);
    //TASK 1:
if(optiune==1)
{
    FILE *in1 = fopen(argv[2],"rt");
    FILE *out1 = fopen(argv[3],"wt");
    double valoare_anterioara = 0, rand_mediu = 0, volatilitate = 0, S;
    int n;
    N* cap = NULL;
    N* p = NULL;
    if(in1 == NULL)
    {
        printf("Fisierul nu se poate deschide!");
        return 0;
    }
    if(out1 == NULL)
    {
        printf("Fisierul nu se poate deschide!");
        return 0;
    }
    fscanf(in1,"%d",&n);
    for(int incercare = 0; incercare<n; incercare++)
    {
        N* nou = (N*)malloc(sizeof(N));
        fscanf(in1,"%lf",&nou->valoare);
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
    fprintf(out1,"%.3lf\n",rand_mediu);
    fprintf(out1,"%.3lf\n",volatilitate);
    fprintf(out1,"%.3lf",S);
    fclose(in1);
    fclose(out1);
    return 0;
}
    //TASK2:
    if(optiune== 2)
    {
    P *cap1 = NULL;
    P *cap2 = NULL;
    P *cap3 = NULL;
    FILE *in2 = fopen(argv[2],"rt");
    FILE *out2 = fopen(argv[3],"wt");
    int n1, n2, n3, pret1, pret2, pret3, elem_coada=0;
    char nume1[20];
    char nume2[20];
    char nume3[20];
    int nr,zi=0;
    OP* q;
    q = creare_coada();
    fscanf(in2, "%s", nume1);
    while(fscanf(in2,"%d",&nr) ==  1)
    {
        n1++;
        push(&cap1,nr);
    }
    fscanf(in2, "%s", nume2);
    while(fscanf(in2, "%d",&nr) == 1)
    {
        n2++;
        push(&cap2,nr);
    }
    fscanf(in2, "%s", nume3);
    while(fscanf(in2, "%d",&nr) == 1)
    {
        n3++;
        push(&cap3,nr);
    }
    while((n1!=0) && (n2!=0) && (n3!=0))
    {
        zi++;
        pret1 = varf(cap1);
        pret2 = varf(cap2);
        pret3 = varf(cap3);
        if((pret1 == pret2)&&(pret1!=pret3))
        {
            add_coada(q,zi,abs(pret3-pret1),nume3);
            elem_coada++;
        }
        if((pret2 == pret3)&&(pret1!=pret2))
        {
            add_coada(q,zi,abs(pret1-pret2),nume1);
            elem_coada++;
        }
        if((pret1 == pret3)&&(pret2!=pret1))
        {
            add_coada(q,zi,abs(pret2-pret1),nume2);
            elem_coada++;
        }
        pop(&cap1);
        pop(&cap2);
        pop(&cap3);
        n1--;
        n2--;
        n3--;

    }
    for(int i=0; i<elem_coada; i++)
        rem_coada(q,out2);
    fclose(in2);
    fclose(out2);
    return 0;
}
}