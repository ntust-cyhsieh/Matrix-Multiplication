// cpp program, matrix multiplication
// returns the elapsed time of the loop iterations measured by omp_get_wtime()

#include <iostream>
#include <algorithm>            // std::min
#include <omp.h>

int main(int argc, char *argv[])
{

    // matrix dimensions
    const int row = 128;
    const int col = 128;

    // matrix stored as an array of size 1000*1000
    // temp will be b transposed, recommendation from the article mentioned above
    // res is of double precision, I ran into errors displaying the data when using a different data type
    int *a = new int[row*col];
    int *b = new int[row*col];
    int *temp = new int[row*col];
    double *res = new double[row*col];

    // initialization
    for(int i = 0; i < row; ++i){
        for (int j = 0; j < col; ++j) {
            a[i*col+j] = i*col+j;
            b[i*col+j] = i*col+j;
        }
    }

    // transposition of b
 /*   for(int i = 0; i < row; ++i){
        for (int j = 0; j < col; ++j) {
            temp[i*col+j] = b[j*col+i];
        }
    }
*/

    int i,j,k,x,y,z;

// "naive" matrix multiplication
/*     double start = omp_get_wtime();
     for (i = 0; i < row; ++i) {
         for (j = 0; j < col; ++j) {
             for (k = 0; k < row; ++k) {
                 res[ i * col + j ] +=  a[ i * col + k ] * b[ k * col + j ];      
             }
         } 
     }
     double end = omp_get_wtime();
     std::cout << end-start << std::endl;
*/


// "transposed" matrix multiplication
        // for (i = 0; i < row; ++i) {
           //  for (j = 0; j < col; ++j) {
                // for (k = 0; k < row; ++k) {
                   // res[ i * col + j ] +=  a[ i * col + k ] * temp[ k  + j * col  ];      
                // }
            // } 
        // }

// tiled (parallel) matrix multiplication
// from /sys/devices/system/cpu/cpu0/cache/index0
// cat coherency_line_size returns 64;
// thus I will use 64 as the blocking size;


    double start = omp_get_wtime();  
    int incr = 32;
    for (i = 0; i < row; i += incr) {
         for (j = 0; j < col; j += incr) {
             for (k = 0; k < row; k += incr) {
                 for (x = i; x < (i + incr) && x < row; x++) {
                     for (y = j;  y < (j + incr) && y < col; y++) {
                         for (z = k;  z < ( k + incr) && z < row; z++) {

                             res[ x * col + y ] +=  a[ x * col + z ] * b[ z * col  + y  ];

                         }
                     } 
                 }
             }
         }
     }
     double end = omp_get_wtime();
     std::cout << end-start << std::endl;

     return 0;
}
