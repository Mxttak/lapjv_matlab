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