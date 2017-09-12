#include "format.hpp"
#include <string>
#include <fstream>

using namespace std;

namespace format
{

    Sparse::Sparse()
    {
        nnz = 0;
        row_size = 0;
        col_size = 0;
        val.resize(m);
        col_ind.resize(m);
        row_ptr.resize(m);
        val_iter = val.begin();
        col_iter = col_ind.begin();
        row_iter = row_ptr.begin();
    }

    void Sparse::read(string filepath)
    {
        fstream fp;
        fp.open(filepath.c_str(), fstream::in);
        if(!fp.is_open())
        {
            cout<<"Cannot open file: "<<filepath<<endl;
            Sparse();
            return;
        }

        //read indices & vals into buffer.

        //...
    }

    template<class T>
    T Sparse::operator()(int i, int j)
    {
        vector::iterator beg = row_ptr.
    }

    void Sparse::earseMatrix()
    {
        Sparse();
    }

    void Sparse::Sparse(string filepath)
    {
        Sparse();
        read(filepath);
    }

    Dense& Sparse<T>::getDenseSubmatrix(vector<int> row_ind, vector<int> col_ind)
    {
        Dense M = new Dense(this, row_ind, col_ind);
        return &M;
    }



    //cholesky fac
    Sparse& Sparse::choleskyFactorization()
    {
        //...
        //Gen etree

        //pushing fronts into stacks

        //HSS
    }


    Dense::Dense()
    {
        row_size = 0;
        col_size = 0;
        row_ind.resize(row_size);
        col_ind.resize(col_size);
        val.resize(row_size);
    }

    Dense::Dense(Sparse S, vector<int>ri, vector<int> ci)
    {
        row_size = ri.size();
        //Need to remove zero cols?
        col_size = ci.size();

        //copy row&col indices
        row_ind = ri;
        col_ind = ci;

        //...

    }
}
