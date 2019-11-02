#include <iostream>
#include <algorithm>            
#include <omp.h>
int main(int argc, char *argv[])
{
	const int row = 150;
	const int col = 128;

	double *a = new double[row*col];
	double *b = new double[row*col];

	// initialization
	for(int i = 0; i < row; ++i)
        	    for (int j = 0; j < col; ++j)
            	        a[i*col+j] = (double)(i*col+j);
        	 // copy     
	double start = omp_get_wtime();  
	for(int i = 0; i < row; i++)
	    for(int j = 0; j < col; j++)
	         b[i*col+j] = a[i*col+j];

	double end = omp_get_wtime();
                         std::cout << end-start << std::endl;
		
    return 0;
}
