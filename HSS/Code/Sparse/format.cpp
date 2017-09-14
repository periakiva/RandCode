#include "format.hpp"
#include "hss.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <stdlib.h>

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

    template<typename T>
    void Sparse<T>::read(string filepath)
    {
        fstream fp;
        fp.open(filepath.c_str(), fstream::in);
        if(!fp.is_open())
        {
            cout<<"Cannot open file: "<<filepath<<endl;
            Sparse<T>();
            return;
        }

        //read indices & vals into buffer.

        //...
    }

    template<typename T>
    T Sparse<T>::operator()(int i, int j)
    {
        T entry;
        return entry;
        //vector::iterator beg = row_ptr.
    }

    template<typename T>
    void Sparse<T>::eraseMatrix()
    {
        Sparse<T>();
    }

    template<typename T>
    void Sparse<T>::Sparse(string filepath)
    {
        Sparse<T>();
        read(filepath);
    }

    template<typename T>
    Dense<T>& Sparse<T>::getDenseSubmatrix(vector<int> row_ind, vector<int> col_ind)
    {
        Dense<T> M = new Dense<T>(this, row_ind, col_ind);
        return &M;
    }



    //cholesky fac
    template<typename T>
    Sparse<T>& Sparse::choleskyFactorization(int level = 0)
    {
        //...
        //Gen etree


        //pushing fronts into stacks

        //HSS
    }

    template<typename T>
    Dense::Dense()
    {
        row_size = 0;
        col_size = 0;
        row_ind.resize(row_size);
        col_ind.resize(col_size);
        val = new T[row_size * col_size];
    }

    template<typename T>
    Dense::Dense(Sparse<T> S, vector<int>ri, vector<int> ci)
    {
        row_size = ri.size();
        //Need to remove zero cols?
        col_size = ci.size();

        //malloc space for mat
        val = (T*)malloc(sizeof(T) * row_size * col_size);

        //copy row&col indices
        row_ind = ri;
        col_ind = ci;

        //...
        T* d_ptr = val;
        for(unsigned i = 0; i < row_ind.size(); i++)
        {
            int row_num = ri[i];
            vector::iterator s_iter = S.val.begin() + S.row_ptr[row_num];
            vector::iterator s_iter_end = S.val.begin() + S.row_ptr[row_num + 1];
            for(int j = 0; j < col_ind.size(); j++)
            {
                if()
            }
        }

    }

    Vector::Vector()
    {
        dim = 0;
    }

    template<typename T>
    Vector::Vector(int n, bool rand_init)
    {
        dim = n;
        val = new T[n];

        if(!rand_init)
        {
            for(int i=0; i<dim; i++)
            {
                val[i] = 0.0;
            }
            return;
        }

        //gen random numbers obey uniform dist(0,1)
        default_random_engine generator;
        uniform_real_distribution<T> dist(0.0, 1.0);

        for(int i=0; i<dim; i++)
        {
            val[i] = dist(generator);
        }
    }

    Vector::~Vector()
    {
        if(val != NULL)
        {
            free(val);
        }
    }


    //extensive add
    template<typename T>
    Vector<T>& Vector::operator+(Vector v)
    {
        int minDim = min(this->dim , v.dim);
        int maxDim = max(this->dim , v.dim);
        Vector* longer = (this->dim >= v.dim) ? this : &v;
        Vector* sv = new Vector<T>(maxDim);

        for(int i = 0; i< minDim; i++)
        {
            sv->val[i] = this->val[i] + v.val[i];
        }

        for(int i = minDim; i<maxDim; i++)
        {
            sv->val[i] = longer->val[i];
        }

        return sv;
    }

    Vector& Vector<T>::operator-(Vector v)
    {
        int minDim = min(this->dim , v.dim);
        int maxDim = max(this->dim , v.dim);

        Vector* sv = new Vector<T>(maxDim);

        for(int i = 0; i< minDim; i++)
        {
            sv->val[i] = this->val[i] - v.val[i];
        }

        if(this->dim >= v.dim)
        {
            for(int i = minDim; i<maxDim; i++)
            {
                sv->val[i] = longer->val[i];
            }
        }else
        {
            for(int i = minDim; i<maxDim; i++)
            {
                sv->val[i] = -(longer->val[i]);
            }
        }
        return sv;
    }

    //Inner product
    T& Vector<T>::operator*(Vector v)
    {
        if(this->dim != v.dim)
        {
            cout<<"Dimension between vectors are not matching!"<<endl;
            return 0;
        }
        T* product = new T;

        *product = 0.0;

        for(int i=0; i<this->dim; i++)
        {
            *product += (this->val[i]) * (v.val[i]);
        }

        return product;
    }
}
