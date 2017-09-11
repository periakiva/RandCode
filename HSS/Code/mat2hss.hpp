#ifndef MAT2HSS_H
#define MAT2HSS_H
#include "util.hpp"
#include "rQR.hpp"
#include <vector>
using namespace std;
using std::vector;


template <typename T>
void setvalue(T *array, int len, T val);
template <typename T>
void setarray(T *A, int nCols, int ibegin1, int iend1, int jbegin1, int jend1, T *B, int stride);
template <typename T>
T *transpose(T *A, int nRow, int nCol);
template <typename T>
void move(T *A, int nCol, int si1, int si2, int sj1, int sj2, int ti1, int ti2, int tj1, int tj2);



template <typename T>
struct matrix{
	T *elem;
	int nRows;
	int nCols;
};

template <typename T>
struct hss
{	
	T *D;
	T *U;
	T *V;
	T *R;
	T *W;
	T *B;
	int nNodes;

	hss(int n)
	{
		nNodes=n;
		D=new T[n];
		U=new T[n];
		V=new T[n];
		R=new T[n];
		W=new T[n];
		B=new T[n];
	}
	~hss()
	{
		delete [] D;
		delete [] U;
		delete [] V;
		delete [] R;
		delete [] W;
		delete [] B;
	}

};

typedef struct child
{
	int lchild;
	int rchild;
	bool cflag;
}tchild;



typedef struct noderange
{
	int begin;
	int end;	
}noderange;


void testprint12(tchild *ch, int len)
{
	for(int i=0;i<len;i++)
	{
		if(ch[i].cflag==false){
			printf("i=%d empty!\n",i);
		}
		else {
			printf("%d:(%d,%d)\n",i,ch[i].lchild,ch[i].rchild);
		}
	}
}


tchild *findChild(int *tr, int len)
{
	tchild *ch=(tchild *)malloc(sizeof(tchild)*len);


	for(int i=0;i<len;i++)
	{
		ch[i].lchild=-1;
		ch[i].rchild=-1;
		ch[i].cflag=false;
	}

	for(int i=0;i<len-1;i++)
	{		
		int parent=tr[i];

		// printf("i=%d %d\n", i,tr[i]);
		if(ch[parent-1].cflag==false){
			ch[parent-1].lchild=i;  // maybe a bug, 1-base index in Matlab, howeve, 0-base index in C/C++
			ch[parent-1].cflag=true;
		}
		else {
			ch[parent-1].rchild=i;
			
		}
	}

	return ch;
}

noderange *mapMatrixTotreenode(tchild *ch, int *m, int len)
{
	int lt=0;
	int it=0;

	noderange *l=(noderange *)malloc(sizeof(noderange)*len);

	for(int i=0;i<len;i++)
	{
		if(ch[i].cflag==false)
		{
			l[i].begin=lt;
			l[i].end=lt+m[it]-1;
			lt=lt+m[it];
			++it;
		}
		else {
			l[i].begin=l[ch[i].lchild].begin;
			l[i].end=l[ch[i].rchild].end;
		}
	}

	return l;
}



template <typename T>
hss< matrix<T> > mat2hss(T *A, int nRows, int nCols, int *tr, int nNodes, int *m, int mlen, T par)
{
	tchild *ch=findChild(tr,nNodes);
	// testprint12(ch,nNodes);

	noderange *l=mapMatrixTotreenode(ch,m,nNodes);
	printf("test1\n");
	

	hss< matrix<T> > tHss(nNodes);
    printf("test2\n");
	
	// vector<int> ws1;
	// vector<int> ws2;
	// vector<int> ls1;
	// vector<int> ls2;

	// ls1.push_back(0);
	// ls2.push_back(0);
	// ws1.push_back(l[0].end+1);
	// ws2.push_back(l[0].end+1);

    int *ls1=new int[nNodes];
    int *ls2=new int[nNodes];
    int *ws1=new int[nNodes];
    int *ws2=new int[nNodes];

    memset(ls1,0,sizeof(int)*nNodes);
    memset(ls2,0,sizeof(int)*nNodes);
    memset(ws1,0,sizeof(int)*nNodes);
    memset(ws2,0,sizeof(int)*nNodes);

    ls1[0]=0;
    ls2[0]=0;
    ws1[0]=l[0].end+1;
    ws2[0]=l[0].end+1;

	printf("test3\n");
	int ns1=0;
	int ns2=0;
	// int **D=(int *)malloc(sizeof(int *)*nNodes);

	T *T1;
	T *T2;

	int r1;
	int r2;

	QResult<T> QRow,QCol;

	int nR,nC;

	
	for(int i=0;i<nNodes;i++)
	{
		tchild tch = ch[i];
		printf("test HSS %d\n", i);
		if(tch.cflag==false){
            printf("Child %d\n",__LINE__);
		  	int begin=l[i].begin;
		  	int end=l[i].end;
		  	
		  	T *D=(T *)malloc(sizeof(T)*(end-begin+1)*(end-begin+1));

		  	int index=0;
	
		  	for(int s=begin;s<=end;s++)
		  	{	
		  		for(int t=begin;t<=end;t++)
		  		{
		  			D[index++]=A[s*nCols+t];		
		  		}
		  	}
		  
		  	// testMatrix(D,end-begin+1,0,end-begin,0,end-begin);

		  	tHss.D[i].elem=D;
		  	tHss.D[i].nRows=end-begin+1;
		  	tHss.D[i].nCols=end-begin+1;

	
            if(ns1==0){
		  		nR=l[i].end-l[i].begin+1;
		  		nC=nCols-1-l[i].end;
		  		T1=new T[nR*nC];
                setarray(A,nCols,l[i].begin,l[i].end,l[i].end+1,nCols-1, T1, nC);
		  		r1=nR;
		  	}
		  	else{

		  	    nR=l[i].end-l[i].begin+1;
		  		nC=ls2[ns2]-1+nCols-l[i].end;

		  		T1=new T[nR*nC];

		  		for(int s=ws2[ns2-1];s<=ws2[ns2-1]+l[i].end-l[i].begin;s++)
		  		{
		  			int rIndex=s-ws2[ns2-1];
		  			for(int t=0;t<=ls2[ns2]-1;t++)
		  			{
		  				int cIndex=t;

		  				T1[rIndex*nC+cIndex]=A[s*nCols+t];

		  			}
		  		}

		  		for(int s=l[i].begin;s<=l[i].end;s++)
		  		{
		  			int rIndex=s-l[i].begin;
		  			for(int t=l[i].end+1;t<=nCols-1;t++)
		  			{
		  				int cIndex=t-l[i].end-1+ls2[ns2];

		  				T1[rIndex*nC+cIndex]=A[s*nCols+t];
		  			}
		  		}
		 		r1=nR;
		  	}

       	  	testMatrix(T1,nC,0,nR-1,0,nC-1);
		  	QRow = megclpv(T1,nR,nC,par);
		  	printf("%d\n",__LINE__);
		  	tHss.U[i].elem=QRow.Q;
		  	tHss.U[i].nRows=QRow.nRow;
		  	tHss.U[i].nCols=QRow.rk;
		  	printf("%d rk=%d\n",__LINE__,QRow.rk);
		  	T1=QRow.R;
		  	r1=r1-QRow.rk;
		  	
		  	ls1[ns1+1]=ls1[ns1]+QRow.rk;
		  	// printf("test __LINE__ %d\n", QRow.rk);
		  	// ls1.push_back(ls1[ns1]+QRow.rk);

		  	ws1[ns1]=l[i].end+1;

		  	for(int s=ls1[ns1];s<=ls1[ns1+1]-1;s++)
		  	{
		  		int rIndex=0;
		  		for(int t=l[i].end+1;t<=nCols-1;t++)
		  		{
		  			A[s*nCols+t]=T1[rIndex*QRow.nCol+t];

		  		}
		  		rIndex++;
		  	}
			if(ns2==0)
			{
				nR = nCols-1-l[i].end;
				nC = l[i].end-l[i].begin+1;

				T2=new T[nR*nC];

				setarray(A,nCols,l[i].end+1,nCols-1,l[i].begin,l[i].end, T2, nC);

				r2=nC;

			}
			else {

				nC=l[i].end-l[i].begin+1;
				
		  		nR=ls2[ns1]-2+nCols-l[i].end;

		  		T2=new T[nR*nC];


		  		for(int s=0;s<ls1[ns1]-1;s++)
		  		{
		  			int rIndex=s;
		  			for(int t=ws1[ns1-1];t<=ws1[ns1-1]+l[i].end-l[i].begin;t++)
		  			{
		  				int cIndex=t-ws1[ns1-1];
		  				T2[rIndex*nC+cIndex]=A[s*nCols+t];
		  			}
		  		}

		  		for(int s=l[i].end+1;s<=nCols-1;s++)
		  		{
		  			int rIndex=ls1[ns1];
		  			for(int t=l[i].begin;t<=l[i].end;t++)
		  			{
		  				int cIndex=t-l[i].begin;

		  				T2[rIndex*nC+cIndex]=A[s*nCols+t];
		  			}
		  			rIndex++;
		  		}


                transpose(T2,nR,nC);
		  		r2=nC;

			}

			T *tT2=transpose(T2,nR,nC);
//            testMatrix(tT2,nR,0,nC-1,0, nR-1);
			QCol = megclpv(tT2,nC,nR,par);

			tHss.V[i].elem=QCol.Q;
			tHss.V[i].nRows=QCol.nRow;
			tHss.V[i].nCols=QCol.rk;

			T2=transpose(QCol.R,QCol.rk,QCol.nCol);

			r2=r2-QCol.rk;

			ls2[ns2+1]=ls2[ns2] + QCol.rk;
			// ls2.push_back(ls2[ns2]+QCol.rk);
			ws2[ns2]=l[i].end+1;


			for(int s=l[i].end+1;s<=nCols-1;s++) // A(l(i,2)+1:N,ls2(ns2):ls2(ns2+1)-1) = T2(end-(N-l(i,2))+1:end,:);
			{
//				int rIndex=s; // bug

                int rIndex=QCol.nCol-1-(nCols-1-s);

                for(int t=ls2[ns2];t<=ls2[ns2+1]-1;t++)
				{
					int cIndex=t-ls2[ns2];

					A[s*nCols+t]=T2[rIndex*QCol.rk+cIndex];

				}
			}
			++ns1;
			++ns2;
		}
		else {

			nR=ls1[ns1-1]-ls1[ns1-2];
			nC=ws1[ns1-1]-ws1[ns1-2];

			T *B1=new T[nR*nC];
			setarray(A,nCols, ls1[ns1]-2,ls1[ns1-1]-1,ws1[ns1-2],ws1[ns1-1]-1, B1, nC);


			tHss.B[tch.lchild].elem=B1;
			tHss.B[tch.lchild].nRows=nR;
			tHss.B[tch.lchild].nCols=nC;

			nR = ws2[ns2-1]-ws2[ns2-2];
			nC = ls2[ns2-1]-ls2[ns2-2];

			T *B2=new T[nR*nC];

			setarray(A, nCols, ws2[ns2-2],ws2[ns1-1]-1,ls2[ns2-2], ls2[ns2-1]-1, B2, nC);



			tHss.B[tch.rchild].elem=B2;
			tHss.B[tch.rchild].nRows=nR;
			tHss.B[tch.rchild].nCols=nC;
			if(i==nNodes-1)break;

			if(ns1==2){
				nR=ls1[ns1]-ls1[ns1-2];
				nC=nCols-l[i].end;
				T1=new T[nR*nC];
				for(int s=ls1[ns1-2];s<=ls1[ns1]-1;s++)
				{
					int rIndex=s-ls1[ns1-2];
					for(int t=l[i].end+1;t<=nCols-1;t++)
					{
						int cIndex=t-l[i].end-1;

						T1[rIndex*nC+cIndex]=A[s*nCols+t];

					}
				}

				r1=nR;

			}
			else {

				nR = ws2[ns2-1]-ws2[ns2-3];
				nC = ls2[ns2-2]+(nCols-l[i].end);
				T1=new T[nR*nC];

				for(int s=ws2[ns2-3];s<=ws2[ns2-1]-1;s++)
				{	
					int rIndex=s-ws2[ns2-3];
					int cIndex=0;	
					for(int t=0;t<=ls2[ns2-2]-1;t++)
					{
						T1[rIndex*nC+t]=A[s*nCols+t];
					}

					cIndex=ls2[ns2-2];
					for(int t=l[i].end+1;t<=nCols-1;t++)
					{
						T1[rIndex*nC+cIndex]=A[s*nCols+t];
						++cIndex;
					}
				}
				r1=nR;
			}
			// printf("TEST %d\n", __LINE__);
            printf("parent line %d\n", __LINE__);
			QRow=megclpv(T1,nR,nC,par);

			tHss.U[i].elem=QRow.Q;
		  	tHss.U[i].nRows=QRow.nRow;
		  	tHss.U[i].nCols=QRow.rk;

		  	T1=QRow.R;
		  	r1 = r1-QRow.rk;

		  	ls1[ns1-1] = ls1[ns1-2]+QRow.rk;
//		  	printf("TEST %s %d\n", __FUNCTION__, __LINE__);
//
//		  	printf("%d %d %d %d\n", ls1[ns1-2],ls1[ns1-1],l[i].end+1,nCols-1);
		  	testprint(ls1,4);
		  	for(int s=ls1[ns1-2];s<=ls1[ns1-1];s++)
		  	{
		  		int rIndex=s-ls1[ns1-2];
		  		int cIndex=QRow.nCol-1-(nCols-1-l[i].end)+1;
		  		for(int t=l[i].end+1;t<=nCols-1;t++)
		  		{
		  			

		  			A[s*nCols+t]=T1[rIndex*QRow.nCol+cIndex];
		  			++cIndex;

		  		}
		  	}	

		  	printf("TEST %d\n", __LINE__);
		  	if(ns2==2){
		  		nR=nCols-l[i].end-1;
		  		nC=ls2[ns2]-ls2[ns2-2];
		  		T2=new T[nR*nC];

		  		for(int s=l[i].end+1;s<=nCols-1;s++)
		  		{
		  			int rIndex=s-l[i].end-1;
		  			for(int t=ls2[ns2-2];t<=ls2[ns2]-1;t++)
		  			{
		  				int cIndex=t-ls2[ns2-2];

		  				T2[rIndex*nC+cIndex]=A[s*nRows+t];

		  			}
		  		}

		  		r2=nC;
		  	}
		  	else {
		  		nR=ls1[ns1-2]-1+(nCols-l[i].end-1);
		  		nC=ws1[ns1-1]-ws1[ns1-3];

		  		for(int s=0;s<=ls1[ns1-2]-1;s++)
		  		{
		  			int rIndex=s;
		  			for(int t=ws1[ns1-3];t<=ws1[ns1-1]-1;t++)
		  			{
		  				int cIndex=t-ws1[ns1-3];

		  				T2[rIndex*nR+cIndex]=A[s*nCols+t];

		  			}
		  		}

		  		for(int s=l[i].end+1;s<=nCols-1;s++)
		  		{
		  			int rIndex=ls1[ns1-2];
		  			for(int t=ls2[ns2-2];t<=ls2[ns2]-1;t++)
		  			{
		  				int cIndex=t-ls2[ns2-2];
		  				T2[rIndex*nR+cIndex]=A[s*nCols+t];
		  			}
		  			++rIndex;
		  		}

		  		r2=nC;
		  	}

		  	T *tT2=transpose(T2,nR,nC);
			QCol = megclpv(tT2,nC,nR,par);

			tHss.V[i].elem=QCol.Q;
			tHss.V[i].nRows=QCol.nRow;
			tHss.V[i].nCols=QCol.rk;

			T2=transpose(QCol.R, QCol.rk,QCol.nCol);

			r2=r2-QCol.rk;

			ls2[ns2-1] = ls2[ns2-2] + QCol.rk;

			for(int s=l[i].end+1;s<=nCols-1;s++)
			{
				int rIndex=s;
				for(int t=ls2[ns2-2];t<=ls2[ns2-1]-1;t++)
				{
					int cIndex=t-ls2[ns2-2];
					A[s*nCols+t]=T2[rIndex*QCol.rk+cIndex];
				}
			}

			--ns1;
			--ns2;

		}

		if(ns2>=3)
		{
			for(int j=0;j<=ns2-2;j++)
			{
				move(A,nCols,ws2[j]+r1,ws2[ns1-2]+r1-1,ls2[j],ls2[j+1]-1,ws2[j],ws2[ns2-2]-1,ls2[j],ls2[j+1]-1);
				ws2[j]=ws2[j]+r1;		
			}
		}
		ws2[ns2-1]=l[i].end+1;

		if(ns2>1)
		{

			nR=QRow.rk;
			nC=QRow.nCol;
			for(int s=ws2[ns2-2]+r1;s<=ws2[ns2-1]-1;s++)
			{
				int rIndex=s-ws2[ns2-2]-r1;
				for(int t=0;t<=ls2[ns1-1]-1;t++)
				{
					int cIndex=t;
					A[s*nCols+t]=T1[rIndex*nC+cIndex];

				}
			}

			ws2[ns2-2]=ws2[ns2-2]+r1;
		}

		if(ns1>=3)
		{
			for(int j=0;j<=ns2-2;j++)
			{
				// move(A,nCols,ws2[j]+r1,ws2[ns1-2]+r1-1,ls2[j],ls2[j+1]-1,ws2[j],ws2[ns2-2]-1,ls2[j],ls2[j+1]-1);
				move(A,nCols,ls1[j],ls1[j+1]-1,ws1[j]+r2,ws1[ns2-2]+r2-1,ls1[j],ls1[j+1]-1,ws1[j],ws1[ns1-2]-1);
				ws1[j]=ws1[j]+r2;		
			}
		}

		ws1[ns1-1]=l[i].end+1;

		if(ns1>1)
		{
			nR=QCol.nCol;
			nC=QCol.rk;
			for(int s=0;s<=ls1[ns1-1];s++)
			{
				int rIndex=s;
				for(int t=ws1[ns1-2]+r2;t<=ws1[ns1-1]-1;t++)
				{
					int cIndex=t-ws1[ns1-2]-r2;

					A[s*nCols+t]=T2[rIndex*nC+cIndex];

				}
			}
			ws1[ns1-2]=ws1[ns1-2]+r1;
		}


	}


	for(int i=nNodes-2;i>=0;i--)
	{
		tchild tch=ch[i];
		if(tch.cflag!=false)
		{
			int sz=tHss.U[tch.lchild].nCols;
			int nR=tHss.U[tch.lchild].nRows;

			T *tmp=new T[sz*sz];
			T *tmp1=new T[(nR-sz)*sz];
			memcpy(tmp,tHss.U[tch.lchild].elem,sizeof(T)*sz*sz);
			memcpy(tmp1,tHss.U[tch.lchild].elem+sz*sz,sizeof(T)*(nR-sz)*sz);

			tHss.R[tch.lchild].elem=tmp;
			tHss.R[tch.lchild].nRows=sz;
			tHss.R[tch.lchild].nCols=sz;

			tHss.R[tch.rchild].elem=tmp1;
			tHss.R[tch.rchild].nRows=nR-sz;
			tHss.R[tch.rchild].nCols=sz;

			delete [] tHss.U[i].elem;
			tHss.U[i].nRows=0;
			tHss.U[i].nCols=0;

			sz=tHss.V[tch.lchild].nCols;
			nR=tHss.V[tch.lchild].nRows;

			T *tmp2=new T[sz*sz];
			T *tmp3=new T[(nR-sz)*sz];

			memcpy(tmp2,tHss.V[tch.lchild].elem,sizeof(T)*sz*sz);
			memcpy(tmp3,tHss.V[tch.lchild].elem+sz*sz,sizeof(T)*(nR-sz)*sz);

			tHss.W[tch.lchild].elem=tmp2;
			tHss.W[tch.lchild].nRows=sz;
			tHss.W[tch.lchild].nCols=sz;

			tHss.W[tch.rchild].elem=tmp3;
			tHss.W[tch.rchild].nRows=nR-sz;
			tHss.W[tch.rchild].nCols=sz;

			delete [] tHss.V[i].elem;
			tHss.V[i].nRows=0;
			tHss.V[i].nCols=0;
		}
	}



	return tHss;


}

#endif