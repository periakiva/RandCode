#ifndef UTIL_h
#define UTIL_h
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "mat2hss.hpp"


template <typename T>
void setvalue(T *array, int len, T val)
{
	for(int i=0;i<len;i++)
	{
		array[i]=val;
	}
}


template <typename T>
void addvalue(T *array, int len, T val, T *result)
{
	for(int i=0;i<len;i++){
		result[i]=array[i]+val;
	}
}

int partition(int **m, int n, int ni)
{
	int k=floor(n/ni);

	int mr = n % ni;

	if(mr>=(ni/2)){
		++k;
		*m=(int *)malloc(sizeof(int)*k);
		setvalue(*m, k, ni);
		(*m)[k-1]=mr;
	}
	else {
		*m=(int *)malloc(sizeof(int)*k);
		setvalue(*m, k, ni);
		(*m)[k-1]+=mr;
	}
	return k;
}


template <typename T>
void setarray(T *A, int nCols, int ibegin1, int iend1, int jbegin1, int jend1, T *B, int stride)
{
	for(int i=ibegin1;i<=iend1;i++)
	{
		int s=i-ibegin1;
		for(int j=jbegin1; j<=jend1;j++)
		{
			int t=j-jbegin1;

//			B[s*stride+t] = A[j*nCols+i];// bug
            B[s*stride+t] = A[i*nCols+j];

		}
	}
}


template <typename T>
T *transpose(T *A, int nRow, int nCol)
{
	T *tmp=new T[nRow*nCol];
	for(int i=0;i<nRow;i++)
	{
		for(int j=0;j<nCol;j++)
		{
			tmp[j*nRow+i]=A[i*nCol+j];
		}
	}
	return tmp;
}


template <typename T>
void move(T *A, int nCol, int si1, int si2, int sj1, int sj2, int ti1, int ti2, int tj1, int tj2)
{
	assert((si2-si1)==(ti2-ti1));
	assert((sj2-sj1)==(tj2-tj1));


	int nR=si2-si1+1;
	int nC=sj2-sj1+1;

	T *tmp=new T[nR*nC];

	setarray(A,nCol, si1, si2,sj1,sj2, tmp, nC);

	for(int i=0;i<nR;i++)
	{
		int rIndex=i+ti1;
		for(int j=0;j<nC;j++)
		{
			int cIndex=j+tj1;

			A[rIndex*nCol+cIndex]=tmp[i*nC+j];
		}
	}

	delete [] tmp;
}

template <typename T>
void testprint(T *a, int len)
{
	if(sizeof(T)==4){
		for(int i=0;i<len;i++)
		{
			printf("%d\n", a[i]);
		}
	}
	else {
		for(int i=0;i<len;i++)
		{
			printf("i=%d %.20f\n", i,a[i]);
		}

	}
}





void testMatrix(double *a, int stride, int ibegin1, int ibegin2, int jbegin1, int jbegin2)
{
	for(int i=ibegin1;i<=ibegin2;i++)
	{
		for(int j=jbegin1;j<=jbegin2;j++)
		{
			std::cout<<a[i*stride+j]<<" ";
		}
		std::cout<<"\n"<<std::endl;
	}
}


#endif 