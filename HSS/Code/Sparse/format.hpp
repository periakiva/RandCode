#ifndef FORMAT_H_INCLUDED
#define FORMAT_H_INCLUDED

#include <vector>
#include <string>


using namespace std;

namespace format
{
    //only support double now.
    template<typename T>
    class Sparse
    {
    public:
        Sparse(string filename);
        Sparse();
        ~Sparse();

        void read(string filename);
        void eraseMatrix();
        int getNumNoneZeros();
        //Sparse operator=(Sparse B);
        //Sparse operator=(Dense B);
        T operator()(int i, int j);

        Dense& getDenseSubmatrix(vector<int> row_ind, vector<int> col_ind);

        Sparse& choleskyFactorization();

    private:
        //CSR form
        vector<T> val;
        vector<int> col_ind;
        vector<int> row_ptr;

        vector::iterator val_iter;
        vector::iterator col_iter;
        vector::iterator row_iter;
        //size of row & col
        int row_size;
        int col_size;
        int nnz;

        //low rank settings
        bool is_prox = true;
        int min_lowrank_size = 50;
        int oversample = 10;
    };
    template<typename T>
    class Dense
    {
    public:
        Dense();
        Dense(Sparse S, vector<int> ri, vector<int> ci);
        ~Dense();
        T operator()(int i, int j);
        Dense& operator*(Dense B);
    private:
        int row_size;
        int col_size;
        vector<int> row_ind;
        vector<int> col_ind;
        vector<vector<T> > val;
    };

}

#endif // FORMAT_H_INCLUDED
