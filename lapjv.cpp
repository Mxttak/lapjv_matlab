/*
    Matlab interface for the Linear Assignment Problem algorithm from
    R. Jonker and A. Volgenant, "A Shortest Augmenting Path Algorithm 
    for Dense and Sparse Linear Assignment Problems," Computing 38, 
    325-340, 1987
    
    Build: 
        mex lapjv.cpp lapjv/lap.cpp
    
        tested with Matlab R2015b on Win10 x64
    
    Usage:
        [minCost,col] = lapjv(costs)
        
        - costs: cost matrix
        - minCost: minimal cost
        - col: columns order (access of the elements in the cost matrix, e.g., diag(costs(1:m,col)))
        
    Warning: no builtin checks 
    
    I modified "lap.h". The original code is available at 
    http://www.magiclogic.com/assignment.html
            
    Harold Cooper gives some more info on the original code at
    https://github.com/hrldcpr/pyLAPJV
    
    Maxim Dolgov
    Mai 10, 2016
    
    Provided as is. No warranty, no commercial usage.
*/

#include "lapjv/lap.h"
#include <mex.h>

void mexFunction(int nlhs, mxArray* plhs[],			// output arguments
				int nrhs, const mxArray* prhs[]) {	// input arguments
	
    // get the distance matrix and create a 2D array pointing to it
	double* dist = mxGetPr(prhs[0]);
    size_t m = mxGetM(prhs[0]);
    
    double** B =(double**) mxMalloc(m*sizeof(double**));
    for(size_t i = 0;i<m;i++)
        B[i] = dist+i*m;
    
    // dual variables
    cost *u = (cost*) mxMalloc(m*sizeof(cost));
    cost *v = (cost*) mxMalloc(m*sizeof(cost));
    
    // output minimal distance
    plhs[0] = mxCreateDoubleMatrix(1,1, mxREAL);
    double* out = mxGetPr(plhs[0]);
    
    // output assignments
    int arraySize[2];
    arraySize[0] =(int) m; arraySize[1] = 2;
    plhs[1] = mxCreateNumericMatrix(1,m, mxINT32_CLASS, mxREAL);
    row *colsol = (int*) mxGetData(plhs[1]);
    col *rowsol = (col*) mxMalloc(m*sizeof(int));
    
    // call lapjv
    *out = lap(m,B,rowsol,colsol,u,v);
    
    for(size_t i=0;i<m;i++)
        colsol[i]++;     
    
    mxFree(B);  mxFree(u);  mxFree(v);  mxFree(rowsol);
    return;
}