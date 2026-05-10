#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "referinte.h"
int main(int argc, char *argv[])
{
        P *cap1 = NULL;
        P *cap2 = NULL;
        P *cap3 = NULL;
        FILE *in2 = fopen(argv[1],"rt");
         if(in2 == NULL)
        {
            printf("Fisierul nu se poate deschide!");
            return 0;
        }
        FILE *out2 = fopen(argv[2],"wt");
        if(out2 == NULL)
        {
            printf("Fisierul 2 nu se poate deschide!");
            return 0;
        }
        int n1=0, n2=0, n3=0, elem_coada=0, ziua=0;
        char nume1[30];
        char nume2[30];
        char nume3[30];
        char linie[30];
        float nr;
        OP* q;
        q = creare_coada();
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
            float pret1, pret2, pret3;
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
            while(q->right != NULL)
            {
                rem_coada(q, out2);
            }
        free(q);
        while(cap1!=NULL) pop(&cap1);
        while(cap2 != NULL)pop(&cap2);
        while(cap3 != NULL) pop(&cap3);
        fclose(in2);
        fclose(out2);
    return 0;
}