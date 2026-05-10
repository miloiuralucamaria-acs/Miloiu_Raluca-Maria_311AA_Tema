#include "referinte.h"
//TASK2:

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
void add_coada(OP*q,int data,float v, char sir[30])
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
    fprintf(out,"ziua %d - %.2f - %s",data,d,sir);
    free (aux);
}

//TASK3:


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