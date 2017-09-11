#ifndef _RQR_H
#define _RQR_H
#include <stdlib.h>
#include <cmath>
#include <algorithm>
#include <cstring>
#include "util.hpp"
using namespace std;

template <typename T>
struct QResult
{
	T *Q;
	T *R;

	int nRow;
	int rk;
	int nCol;
};

template <typename T>
T fmax(T *vn, int len, int &index)
{
	T max=abs(vn[0]);
	index=0;
	for(int i=1;i<len;i++)
	{
		if(std::abs(vn[i])>max){
			max=std::abs(vn[i]);
			index=i;
		}
	}

	return max;
}


template <typename T>
T norm(T *A, int nRow, int nCol, int j)
{
	T norm=0;
	for(int i=0;i<nRow;i++)
	{
		norm+=A[i*nCol+j]*A[i*nCol+j];
	}

	norm=std::sqrt(norm);
	return norm;
}

template <typename T>
void normalCol(T *A, int nRow, int nCol,int j, T val)
{
	for(int i=0;i<nRow;i++)
	{
		A[i*nCol+j]=A[i*nCol+j]/val;
	}
}
template <typename T>
void swapCols(T *A, int nRow, int nCol, int col1, int col2)
{
	T tmp;
	for(int i=0;i<nRow;i++)
	{
		tmp=A[i*nCol+col1];
		A[i*nCol+col1]=A[i*nCol+col2];
		A[i*nCol+col2]=tmp;
	}
}

template <typename T>
QResult<T> megclpv(T *A, int nRow, int nCol,  T par)
{
	int mn=std::min(nRow,nCol);
	// printf("%s,%d\n", __FUNCTION__,__LINE__);
	int *piv=new int[mn];
	memset(piv,0,sizeof(int)*mn);
	// printf("%s,%d\n", __FUNCTION__,__LINE__);
	T *vn=new T[nCol];
	memset(vn,0,sizeof(T)*nCol);
	// printf("%s,%d\n", __FUNCTION__,__LINE__);
	T *R=new T[mn*nCol];
	memset(R,0,sizeof(T)*nCol*mn);
	for(int i=0;i<nCol;i++)
	{	
		T norm=0;
		for(int j=0;j<nRow;j++)
		{	
			norm+=(A[j*nCol+i]*A[j*nCol+i]);
			// printf("INTO TEST=%.10f %.10f\n", A[j*nCol+i],norm);
		}
		// printf("norm=%.10f\n", norm);
		vn[i]=norm;
	}

//	 testprint(vn,nCol);
	int rk=mn;
	int iii=mn;


	for(int i=0;i<mn;i++)
	{
		T vmax;
		int imax=0;
		vmax=fmax(vn+i,nCol-i,imax);
		imax=imax+i;
		if(imax>i)
		{
			swapCols(A, nRow,nCol,i,imax);
//			swapCols(R, i-1,nCol,i,imax);
            swapCols(R, i,nCol,i,imax);
            piv[i] = imax;
			vn[imax]=vn[i];
		}
		R[i*nCol+i]=norm(A,nRow,nCol,i);

		normalCol(A,nRow,nCol,i,R[i*nCol+i]);
		vn[i] = R[i*nCol+i];

		for(int s=i+1;s<nCol;s++) // R(i,i+1:n) = A(1:m,i)'*A(1:m,i+1:n); 
		{
			T tmp=0;
			for(int t=0;t<nRow;t++)
			{
				tmp+=(A[t*nCol+i]*A[t*nCol+s]);
			}
			R[i*nCol+s]=tmp;
		}

		for(int s=0;s<nRow;s++) // A(1:m,i+1:n) = A(1:m,i+1:n)-A(1:m,i)*R(i,i+1:n);
		{
			for(int t=i+1;t<nCol;t++)
			{
//				A[s*nRow+t]=A[s*nRow+t]-A[s*nRow+i]*R[i*nCol+t];  bug!!
                A[s*nCol+t]=A[s*nCol+t]-A[s*nCol+i]*R[i*nCol+t];
			}
		}

		for(int s=i+1;s<nCol;s++) // vn(i+1:n)-abs(R(i,i+1:n)).^2;
		{
			vn[s]-=(R[i*nCol+s]*R[i*nCol+s]);
		}

		if(R[i*nCol+i]<par*R[0])
		{
			rk=i;
			iii=i;
			break;
		}
	}

    rk=rk+1;

    T *Q=new T[rk*nRow];
	for(int s=0;s<nRow;s++)
	{
		for(int t=0;t<rk;t++)
		{
			Q[s*rk+t]=A[s*nRow+t];
		}
	}

	T *R1=new T[rk*nCol];

	for(int s=0;s<rk;s++)
	{
		for(int t=0;t<nCol;t++)
		{
			R1[s*nCol+t]=R[s*nCol+t];
		}
	}

	for(int s=iii;s>=0;s--)
	{
		int imax=piv[s];
		mn = std::min(rk,rk*imax);
		if(mn>0){
			swapCols(R,mn,nCol,s,imax);
		}
	}


	QResult<T> QR;
	QR.Q=Q;
	QR.R=R1;
	QR.nRow=nRow;
	QR.rk=rk;
	QR.nCol=nCol;


//	delete [] piv;
//	delete [] R;
//	delete [] vn;

	return QR;
}






#endif