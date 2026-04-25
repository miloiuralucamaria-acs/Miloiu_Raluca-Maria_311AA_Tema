#include "referinte.h"
/*//TASK 1:
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
*/
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
