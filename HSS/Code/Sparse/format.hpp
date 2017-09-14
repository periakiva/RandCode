#ifndef FORMAT_H_INCLUDED
#define FORMAT_H_INCLUDED

#include <vector>
#include <string>


using namespace std;

namespace format
{
    //pre declaration
    template<typename T> class Sparse;
    template<typename T> class Dense;
    template<typename T> class Vector;

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
        Vector<T>& operator*(Vector<T> v);

        Dense<T>& getDenseSubmatrix(vector<int> row_ind, vector<int> col_ind);

        Sparse<T>& choleskyFactorization();

    private:
        //CSR form
        vector<T> val;
        vector<int> col_ind;
        vector<int> row_ptr;

        typename vector<T>::iterator val_iter;
        vector<int>::iterator col_iter;
        vector<int>::iterator row_iter;
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
        Dense(Sparse<T>& S, vector<int> ri, vector<int> ci);
        ~Dense();
        T operator()(int i, int j);
        Dense<T>& operator*(Dense<T>& B);
        Vector<T>& operator*(Vector<T>& v);
    private:
        int row_size;
        int col_size;
        vector<int> row_ind;
        vector<int> col_ind;
        T* val;
    };

    template<typename T>
    class Vector
    {
    public:
        Vector();
        Vector(int n, bool rand_init = true);
        ~Vector();


        //extensive add
        Vector& operator+(Vector v);
        Vector& operator-(Vector v);

        //Inner product
        T& operator*(Vector v);

        int dim;
        T* val;
    };

}

#endif // FORMAT_H_INCLUDED
