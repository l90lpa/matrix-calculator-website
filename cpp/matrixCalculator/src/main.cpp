//
//  main.cpp
//  matrixCalculator
//
//  Created by Liam on 09/02/2017.
//  Copyright © 2017 Liam. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "include/D_Base_Matrix.h"

/* The argument vectors of argv should be in the order;
*     - file name,
*     - operation,
*     - A row dimension,
*     - A column dimension,
*     - A matrix elements given in row order i.e. all the first row from 0 to n
*       then all the second row from 0 to n etc,
*     - B row dimension,
*	  - B column dimension,
*     - B matrix  elements given in row order i.e. all the first row from 0 to n
*       then all the second row from 0 to n etc,
*/






int main(int argc, const char * argv[])
{
    // Convert row dim to numeric value.
    std::stringstream rowDimA(argv[2]);
    int rowsA;
    rowDimA >> rowsA;
    
    // Convert column dim to numeric value.
    std::stringstream colDimA(argv[3]);
    int colsA;
    colDimA >> colsA;

    
    // Set up vector to store the matrix elements.
    int matrixSizeA = rowsA * colsA;
    std::vector<int> matrixA;
    matrixA.resize(matrixSizeA);

    int matrixAStartIndex = 4;
    int matrixAFinishIndex = matrixSizeA + 3;
    // Convert string char to numeric values to be the row elements.
    for(int i = matrixAStartIndex; i <= matrixAFinishIndex; ++i)
    {
        std::stringstream sA((argv[i]));
        sA >> matrixA[i - matrixAStartIndex];
    }
    
    //0 = program
    //1 = operation
    //2 = rowsA
    //3 = colsB
    //4 = matrixA[0]
    
    int rowsBIndex = 4 + matrixSizeA;
    int colsBIndex = 5 + matrixSizeA;
    int matrixBStartIndex = 6 + matrixSizeA;
    
    // Convert row dim to numeric value.
    std::stringstream rowDimB(argv[rowsBIndex]);
    int rowsB;
    rowDimB >> rowsB;
    
    // Convert column dim to numeric value.
    std::stringstream colDimB(argv[colsBIndex]);
    int colsB;
    colDimB >> colsB;
    
    // Set up vector to store the matrix elements.
    int matrixSizeB = rowsB * colsB;
    std::vector<int> matrixB;
    matrixB.resize(matrixSizeB);
    
    // Convert string char to numeric values to be the row elements.
    for(int i = matrixBStartIndex; i < argc; ++i)
    {
        std::stringstream sB((argv[i]));
        sB >> matrixB[i - matrixBStartIndex];
    }

    
    
    
    D_Base_Matrix<int> A{rowsA,colsA};
    A = matrixA;
    
    D_Base_Matrix<int> B{rowsB,colsB};
    B = matrixB;
    
    D_Base_Matrix<int> C{rowsA,colsB};
    
    const char op = *(argv[1]);
    switch(op) 
    {
    	case '+':
    		C = A + B;
    		break;
    	case '-':
    		C = A - B;
    		break;
    	case '*':
    		C = A * B;
    		break;
    }
    
    std::cout << op << ",";
    std::cout << C.getRowDim() << ",";
    std::cout << C.getColDim() << ",";
    
    C.outputCSV();

    return 0;
}
