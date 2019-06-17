#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
static int success;

void breakAndSort(int Set[], int size, int Negset[], int Posset[]);
void genSubsets(int Ps[], int Psize, int Ns[], int Nsize);
void zeroSubset(int Ps[], int Pt[], int Psize, int PTsize, int Psum, int PnodeCount, int Ns[], int Nt[], int Nsize, int NTsize, int Nsum, int NnodeCount);

int main()
{
    int size, i, k=0, h=0;
    scanf("%d", &size);
    int Set[size];
    for (i=0; i<size; i++)
    {
        scanf("%d", &(Set[i]));
    }
    for (i=0; i<size; i++)
    {
        if (Set[i]==0)
        {
            printf("Poaibis: {%d}\n", Set[i]);
            success=1;
        }
    }
    if (success != 1)
    {
        for (i=0; i<size; i++)
        {
            if (Set[i]<0)
            {
                k++;
            }
            else
                h++;
        }
        if (k!=0&&h!=0)
        {
            int *Negset=(int*)malloc(k*sizeof(int));
            int *Posset=(int*)malloc(h*sizeof(int));
            breakAndSort(Set, size, Negset, Posset);
            genSubsets(Posset, h, Negset, k);
            free(Negset);
            free(Posset);
        }

    }

    if(success == 1)
    {
        printf("Yra netuscias poaibis, kurio elementu suma lygi nuliui");
    }
    if(success == 0)
    {
        printf("Nera netuscio poaibio, kurio elementu suma lygi nuliui");
    }
    return 0;
}

void breakAndSort(int Set[], int size, int Negset[], int Posset[])
{
    int x, i, j, h=0, k=0;

    for (i=0; i<size; i++)
    {
        if (Set[i]<0)
        {
            Negset[k]=Set[i];
            k++;
        }
        else
        {
            Posset[h]=Set[i];
            h++;
        }
    }
    qSort(Negset, 0, k-1);
    qSort(Posset, 0, h-1);
    return;
}

void qSort(int Set[], int low, int high)
{
    if (low<high)
    {
        int pivotPosition=partition(Set, low, high);
        qSort(Set, low, pivotPosition-1);
        qSort(Set, pivotPosition+1, high);
    }
}
int partition(int Set[], int low, int high)
{
    int pivot=Set[low];
    int i=low;
    int j=high;
    while (true)
    {
        if (Set[0]<0)
        {
            while (Set[i]>pivot)
            {
                i++;
            }
            while (Set[j]<pivot)
            {
                j--;
            }
        }
        else{
            while (Set[i]<pivot)
            {
                i++;
            }
            while (Set[j]>pivot)
            {
                j--;
            }
        }
        if (i<j)
        {
            swap(&Set[i], &Set[j]);
        }
        else
        {
            return j;
        }
    }
}
void swap(int *a, int *b)
{
    int t=*a;
    *a=*b;
    *b=t;
}

void genSubsets(int Ps[], int Psize, int Ns[], int Nsize)
{
    int *tupleVectorPos = (int*)malloc(Psize*sizeof(int));
    int *tupleVectorNeg = (int*)malloc(Nsize*sizeof(int));
    zeroSubset(Ps, tupleVectorPos, Psize, 0, 0, 0, Ns, tupleVectorNeg, Nsize, 0, 0, 0);
    free(tupleVectorPos);
    free(tupleVectorNeg);
}

void zeroSubset(int Ps[], int Pt[], int Psize, int PTsize, int Psum, int PnodeCount, int Ns[], int Nt[], int Nsize, int NTsize, int Nsum, int NnodeCount)
{
    int i;
    if (success == 0)
    {
        if (Psum+Nsum == 0&&PTsize != 0&&NTsize != 0)
        {
            printf("\nPoaibis lygus 0: {");
            for (i=0; i<NTsize; i++)
            {
                printf("%d, ", Nt[i]);
            }
            for (i=0; i<PTsize-1; i++)
            {
                printf("%d, ", Pt[i]);
            }
            printf("%d}\n", Pt[i]);
            success=1;
            return;
        }
        else
        {
            if (Nsum*-1 >Psum)
            {
                for (i=PnodeCount; i<Psize; i++)
                {
                    Pt[PTsize]=Ps[i];
                    zeroSubset(Ps, Pt, Psize, PTsize+1, Psum+Ps[i], i+1, Ns, Nt, Nsize, NTsize, Nsum, NnodeCount);
                }
            }
            else
            {
                for (i=NnodeCount; i<Nsize; i++)
                {
                    Nt[NTsize]=Ns[i];
                    zeroSubset(Ps, Pt, Psize, PTsize, Psum, PnodeCount, Ns, Nt, Nsize, NTsize+1, Nsum+Ns[i], i+1);
                }
            }
        }
    }
    return;
}
