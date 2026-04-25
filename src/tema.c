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

//PUSH,STIVA
void push(P**cap,float n)
{
    P* new = (P*)malloc(sizeof(P));
    new->nr = n;
    new->urm = *cap;
    *cap = new;
}


//DESCOPERA CAPUL STIVEI:
float varf(P *cap)
{
    if (cap == NULL) return -1;
    return cap->nr;
}


//SCOATE DIN STIVA
float pop(P **cap)
{
    if(cap == NULL)return -1;
    P *temp = (*cap);
    float aux = temp->nr;
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
void add_coada(OP*q,int data,float v,char sir[30])
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
    float d;
    char sir[30];
    int data;
    aux = q->right;
    d=aux->abs;
    strcpy(sir,aux->nume);
    data = aux->zi;
    q->right = (q->right)->urm;
    if(q->right == NULL)
        q->left = NULL;
    fprintf(out,"ziua %d - %.2f -  %s",data,d,sir);
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
}
    //TASK2:
    if(optiune== 2)
    {
    P *cap1 = NULL;
    P *cap2 = NULL;
    P *cap3 = NULL;
    FILE *in2 = fopen(argv[2],"rt");
    FILE *out2 = fopen(argv[3],"wt");
    int n1=0, n2=0, n3=0, elem_coada=0, ziua=0;
    float pret1, pret2, pret3;
    char nume1[30];
    char nume2[30];
    char nume3[30];
    char linie[30];
    float nr;
    OP* q;
    q = creare_coada();
     if(in2 == NULL)
    {
        printf("Fisierul nu se poate deschide!");
        return 0;
    }
     if(out2 == NULL)
    {
        printf("Fisierul nu se poate deschide!");
        return 0;
    }
    fgets(nume1,30,in2);    
    while(fgets(linie,30,in2)!= NULL)
    {
        if(linie[0]>='0' && linie[0]<='9')
        {
            n1++;
            nr = atof(linie);
            push(&cap1,nr);

        }
        else

        {
            strcpy(nume2,linie);
            break;
        }
    }
    while(fgets(linie,30,in2)!= NULL)
    {
        if(linie[0]>='0' && linie[0]<='9')
        {
            n2++;
            nr = atof(linie);
            push(&cap2,nr);
        }
        else
        {
        strcpy(nume3,linie);
        break;
        }
    }
    while(fgets(linie,30,in2)!= NULL)
    {
        if(linie[0]>='0' && linie[0]<='9')
        {
            n3++;
            nr = atof(linie);
            push(&cap3,nr);
        }
    }

    while((n1!=0) && (n2!=0) && (n3!=0))
    {
        ziua++;
        pret1 = varf(cap1);
        pret2 = varf(cap2);
        pret3 = varf(cap3);
        if((pret1 == pret2)&&(pret1!=pret3))
        {   
            add_coada(q,ziua,fabs(pret3-pret1),nume3);
            elem_coada++;
        }
        if((pret2 == pret3)&&(pret1!=pret2))
        {   
            add_coada(q,ziua,fabs(pret1-pret2),nume1);
            elem_coada++;
        }
        if((pret1 == pret3)&&(pret2!=pret1))
        {
            add_coada(q,ziua,fabs(pret2-pret1),nume2);
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
}
    return 0;
}