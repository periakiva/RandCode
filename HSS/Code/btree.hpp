#ifndef BTREE_H
#define BTREE_H
#include <math.h>
#include <string.h>

template <typename T>
void addvalue(T *array, int len, T val, T *result);

int *btree(int n)
{
	if(n%2==0){
		printf("input must be odd\n");
		exit(1);
	}

	if(n>3){
		int m = (n-1)/2;////bug!!!!
		int len=m;
		if(m<3)len=1;
		int *t1;
		t1=btree(m);
		int *t2=new int[len];
		addvalue(t1,len,m,t2);
		t1[len-1]=n;
		t2[len-1]=n;
		int *p=new int[2*len+1];
		memcpy(p,t1,len*sizeof(int));
		memcpy(p+len,t2,len*sizeof(int));
		p[2*len]=0;

		delete [] t1;
		delete [] t2;	
		return p;
	}
	else if(n==3)
	{
		int *p=new int[3];
		p[0]=3;
		p[1]=3;
		p[2]=0;
		return p;
	}
	else{
		int *p=new int[1];
		p[0]=0;
		return p;
	}
}






int *n2tree(int n)
{
	if(n%2==0){
		printf("input must be odd\n");
		exit(1);
	}
	if(n==1)
	{
		int *tr=(int *)malloc(sizeof(int));
		tr[n-1]=0;
		return tr;
	}
	else{
		int n1=pow(2,floor(log(n)/log(2)))-1;
		int *tr1=btree(n1);

		int *tr2=n2tree(n-n1-1);
		addvalue(tr2, n-n1-1, n1, tr2);
		tr1[n1-1] = n;
		tr2[n-n1-2] = n;
		int *tr=(int *)malloc(sizeof(int)*n);

		memset(tr,0,sizeof(int)*n);
		memcpy(tr,tr1,sizeof(int)*n1);
		memcpy(tr+n1,tr2,sizeof(int)*(n-n1-1));
		tr[n-1]=0;


		delete [] tr1;
		delete [] tr2;
		return tr;
	}

}

int *npart(int n, int ni, int &nNodes)
{
	int k = floor(n/ni);
  
    int mr = n % ni;

    if(mr>= ni/2){
    	++k;
    }

    int *tr=n2tree(2*k-1);
    nNodes=2*k-1;
    return tr;
}
#endif