/*
* @Author: Bangtian Liu
* @Date:   2017-08-24 17:05:59
* @Last Modified by:   labuser
* @Last Modified time: 2017-09-03 01:10:02
*/

#include <stdio.h>
#include <iostream>
#include <fstream>
// #include "util.hpp"
#include "btree.hpp"
#include "mat2hss.hpp"


int main(int argc, char *argv[])
{
	FILE *fin;
	char *infile= argv[1];	
	int N=atoi(argv[2]);
	// int nCols=atoi(argv[3]);

	fin=fopen(infile,"r");
	assert(fin);

	double *matrix1=(double *)malloc(sizeof(double)*N*N);


	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
	{
		fscanf(fin,"%lf", &matrix1[i*N+j]); // need to check the storage format here.
	}

	

	int r=16; // HSS block size. 

	double tol=1e-6;

	int Nnodes=0;
	
	int *m;

    int mlen=partition(&m, N, r);

    int *tr=npart(N,r,Nnodes);

    // for(int i=0;i<Nnodes;i++)
    // {
    // 	printf("Test: %d %d\n", i, tr[i]);
    // }
    // mat2hss(matrix,N,N,);
    // 
    hss< matrix<double> > tHss=mat2hss(matrix1,N,N,tr,Nnodes,m,mlen,tol);



	fclose(fin);
	return 0;
}