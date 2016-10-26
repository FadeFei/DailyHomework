/*
*   常用的成熟的生成高斯分布随机数序列的方法由Marsaglia和Bray在1964年提出，C++版本
*   加了 X = X * V + E;之后，即可生成期望为E，方差为V的高斯分布随机函数
*/


#include <stdlib.h>
#include <math.h>
 
double gaussrand()
{
    static double V1, V2, S;
    static int phase = 0;
    double X;
     
    if ( phase == 0 ) {
        do {
            double U1 = (double)rand() / RAND_MAX;
            double U2 = (double)rand() / RAND_MAX;
             
            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        } while(S >= 1 || S == 0);
         
        X = V1 * sqrt(-2 * log(S) / S);
    } else
        X = V2 * sqrt(-2 * log(S) / S);
         
    phase = 1 - phase;
    
    X = X * V + E;

    return X;
}