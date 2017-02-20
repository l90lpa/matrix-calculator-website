//
//  D_Base_Matrix.h
//  matrixCalculator
//
//  Created by Liam on 09/02/2017.
//  Copyright © 2017 Liam. All rights reserved.
//

#ifndef D_Base_Matrix_h
#define D_Base_Matrix_h



#include <iostream>
#include <vector>
#include <initializer_list>

// Matrix and vector class implemented using a 1 dimensional std::vector.

/*Current functionality:    Default initialize with zero matrix.
 *                          Initialize with uniform initializer list.
 *                          Copy constructor.
 *                          Overloaded operator=.
 *                          "        " operator+.
 *                          "        " operator-.
 *                          "        " operator*.
 *                          "        " operator(). Access matrix elements as a 2D matrix.
 *                          "        " operator<<. Output the matrix graphically as a 2D matrix.
 *                          transpose function.
 *							outputCSV function. Output the matrix to a std::ostream in CSV format.
 *							getColRow function.
 *							getColDim function.
 */


//Forward declartion for class Matrix so that we can create only a specific
//implementation of the friend function operator+.
template<typename T>
class D_Base_Matrix;

template<typename T>
std::ostream& operator<< (std::ostream& out, const D_Base_Matrix<T> &a);

template<typename T>
D_Base_Matrix<T> operator+ (const D_Base_Matrix<T> &a, const D_Base_Matrix<T> &b);

template<typename T>
D_Base_Matrix<T> operator- (const D_Base_Matrix<T> &a, const D_Base_Matrix<T> &b);

template<typename T>
D_Base_Matrix<T> operator* (const D_Base_Matrix<T> &a, const D_Base_Matrix<T> &b);

template<typename T>
class D_Base_Matrix
{
private:
    std::vector<T>m_matrix;
    int m_rows;
    int m_cols;
    int m_size;
public:
    //Initialize as a zeros matrix.
    D_Base_Matrix(int rows, int cols) : m_rows{rows}, m_cols{cols}, m_size{rows * cols}
    {
        m_matrix.resize(m_size);
        for(auto &x : m_matrix)
        {
            x = 0;
        }
    }
    
    //Copy constructor.
    D_Base_Matrix(const D_Base_Matrix& C) : m_matrix{C.m_matrix}, m_rows{C.m_rows}, m_cols{C.m_cols}, m_size{C.m_size} 
    {
        //std::cout << "Copy constructor called." << '\n';
    }
    
    //Destructor
    ~D_Base_Matrix()
    {
    }
    
    D_Base_Matrix& operator= (const D_Base_Matrix &matrix);
    
    D_Base_Matrix& operator= (std::initializer_list<T> list);
    
    D_Base_Matrix& operator= (std::vector<T> vec);
    
    //Used to access elements of the matrix.
    T& operator() (int row, int col);
    
    D_Base_Matrix& transpose();
    
    int getRowDim();
    
    int getColDim();
    
    void outputCSV(std::ostream& out = std::cout);
    
    friend std::ostream& operator<< <T> (std::ostream& out, const D_Base_Matrix &a);
    
    friend D_Base_Matrix operator+ <T> (const D_Base_Matrix &a, const D_Base_Matrix &b);
    
    friend D_Base_Matrix operator- <T> (const D_Base_Matrix &a, const D_Base_Matrix &b);
    
    friend D_Base_Matrix operator* <T> (const D_Base_Matrix &a, const D_Base_Matrix &b);
};


template<typename T>
D_Base_Matrix<T>& D_Base_Matrix<T>::operator= (const D_Base_Matrix<T> &A)
{
    if (this == &A)
        return *this;
    
    // do the copy
    m_rows = A.m_rows;
    m_cols = A.m_cols;
    m_matrix = A.m_matrix;
    
    // return the existing object so we can chain this operator
    return *this;
}

template<typename T>
D_Base_Matrix<T>& D_Base_Matrix<T>::operator= (std::initializer_list<T> list)
{
    m_matrix = list;
    
    // return the existing object so we can chain this operator
    return *this;
}

template<typename T>
D_Base_Matrix<T>& D_Base_Matrix<T>::operator= (std::vector<T> vec)
{
    m_matrix = vec;
    
    // return the existing object so we can chain this operator
    return *this;
}

template<typename T>
T& D_Base_Matrix<T>::operator() (int row, int col)
{
    return m_matrix[(row * (m_cols - 1)) + row + col];
}

template<typename T>
D_Base_Matrix<T>& D_Base_Matrix<T>::transpose()
{
    std::vector<T>tempMatrix;
    tempMatrix.resize(m_size);
    tempMatrix[0] = m_matrix[0];
    tempMatrix[(m_size - 1)] = m_matrix[(m_size - 1)];
    for(int i = 1; i < (m_size - 1); ++i)
    {
        tempMatrix[i] = m_matrix[(m_cols * i)%(m_size - 1)];
    }
    m_matrix = tempMatrix;
    
    int temp = m_cols;
    m_cols = m_rows;
    m_rows = temp;
    
    return *this;
}

template<typename T>
int D_Base_Matrix<T>::getRowDim()
{
    return m_rows;
}

template<typename T>
int D_Base_Matrix<T>::getColDim()
{
    return m_cols;
}

template<typename T>
void D_Base_Matrix<T>::outputCSV(std::ostream& out)
{
    int lastComma = (m_cols * m_rows) - 1;
    int k = 0;
    for(int i = 0; i < m_rows; ++i)
    {
        for(int j = 0; j < m_cols; ++j)
        {
            out << m_matrix[(i * (m_cols - 1)) + i + j];
            if(k != lastComma)
            {
                out << ',';
            }
            k++;
        }
    }
}

template<typename T>
std::ostream& operator<< (std::ostream& out, const D_Base_Matrix<T> &a)
{
    for(int i = 0; i < a.m_rows; ++i)
    {
        out << '|';
        for(int j = 0; j < a.m_cols; ++j)
        {
            out << a.m_matrix[(i * (a.m_cols - 1)) + i + j] << '\t';
        }
        out << '|' << '\n';
    }
    return out;
}


template<typename T>
D_Base_Matrix<T> operator+
(const D_Base_Matrix<T> &a, const D_Base_Matrix<T> &b)
{
    D_Base_Matrix<T>temp{a.m_rows, a.m_cols};
    for(int i = 0; i < a.m_size; ++i)
    {
        temp.m_matrix[i] = a.m_matrix[i] + b.m_matrix[i];
    }
    return temp;
}


template<typename T>
D_Base_Matrix<T> operator-
(const D_Base_Matrix<T> &a, const D_Base_Matrix<T> &b)
{
    D_Base_Matrix<T>temp{a.m_rows, a.m_cols};
    for(int i = 0; i < a.m_size; ++i)
    {
        temp.m_matrix[i] = a.m_matrix[i] - b.m_matrix[i];
    }
    return temp;
}

template<typename T>
D_Base_Matrix<T> operator*
(const D_Base_Matrix<T> &a, const D_Base_Matrix<T> &b)
{
    D_Base_Matrix<T>temp{a.m_rows, b.m_cols};
    for(int aRow = 0; aRow < a.m_rows; ++aRow)
    {
        for(int bCol = 0; bCol < b.m_cols; ++bCol)
        {
            for(int k = 0; k < a.m_cols; ++k)
            {
                temp.m_matrix[aRow * b.m_cols + bCol] += a.m_matrix[aRow * a.m_cols + k] * b.m_matrix[bCol + k * b.m_cols];
            }
        }
    }
    return temp;
}

#endif /* D_Base_Matrix_h */
