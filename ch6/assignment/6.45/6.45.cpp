#include <iostream>
using namespace std;

void transposeV1(int *dst, int *src, int dim){
    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            dst[j * dim + i] = src[i * dim + j];
        }
    }
}

/*
    ref https://www.cnblogs.com/liqiuhao/p/8009769.html

    需要注意的是，我们是用指针+偏移来访问数组 src[N][N] dst[N][N]，其中 N = dim 为转置矩阵的大小
    [ 0] [ 1] [ 2] [ 3]
    [ 4] [ 5] [ 6] [ 7]
    [ 8] [ 9] [10] [11]
    [12] [13] [14] [15]

    [0][0] [0][1] [0][2] [0][3] 
    [1][0] [1][1] [1][2] [1][3] 
    [2][0] [2][1] [2][2] [2][3] 
    [3][0] [3][1] [3][2] [3][3]

    让我们思考 B = 16 字节的情况，即高速缓存一行能存放 4 个 int 元素
    转置矩阵，即让每行=每列
    例如：
    dst[0][0] dst[0][1] dst[0][2] dst[0][3]
    src[0][0] src[1][0] src[2][0] src[3][0]

    我们让其访问 dst[0][0] 时就能让缓存存放 dst[0][0] dst[0][1] dst[0][2] dst[0][3]
    [0][0] -> [0][1] [0][2] [0][3] 
    [1][0] -> [1][1] [1][2] [1][3] 
    [2][0] -> [2][1] [2][2] [2][3] 
    [3][0] -> [3][1] [3][2] [3][3]

    src 则会因为第一次行迭代后 [0] [4] [8] [12]
    把src[0] src[1] src[2] src[3] 都放到缓存中，之后都会命中
*/

// ref https://www.cnblogs.com/liqiuhao/p/8009769.html
#define B 16
void faster_transpose(int *dst, int *src, int dim)
{
    long limit = dim * dim;
    for (int i = 0; i < dim; i += B)
    {
        for (int j = 0; j < dim; j += B)
        {
            /* Using blocking to improve temporal locality */
            for (int k = i; k < i+B; ++k)  // k 和 l 可调换
            {
                for (int l = j; l < j+B; ++l)
                {
                    /* independent calculations */
                    int d = l*dim + k;
                    int s = k*dim + l;
                    if (s < limit && d < limit)
                    {
                        dst[d] = src[s];  // dst[j*dim + i] = src[i*dim + j]
                    }
                }
            }
        }
    }
}

/*
当 B = 16 时，对于 dst[d] = src[s] 可看成：
    for (i = 0; i < dim - 3; i += 4) {
        for (j = 0; j < dim - 3; j += 4) {
            dst[j*dim+i] = src[i*dim+j];
            dst[j*dim+i+1] = src[(i+1)*dim+j];
            dst[j*dim+i+2] = src[(i+2)*dim+j];
            dst[j*dim+i+3] = src[(i+3)*dim+j];

            dst[(j+1)*dim+i] = src[i*dim+j+1];
            dst[(j+1)*dim+i+1] = src[(i+1)*dim+j+1];
            dst[(j+1)*dim+i+2] = src[(i+2)*dim+j+1];
            dst[(j+1)*dim+i+3] = src[(i+3)*dim+j+1];

            dst[(j+2)*dim+i] = src[i*dim+j+2];
            dst[(j+2)*dim+i+1] = src[(i+1)*dim+j+2];
            dst[(j+2)*dim+i+2] = src[(i+2)*dim+j+2];
            dst[(j+2)*dim+i+3] = src[(i+3)*dim+j+2];

            dst[(j+3)*dim+i] = src[i*dim+j+3];
            dst[(j+3)*dim+i+1] = src[(i+1)*dim+j+3];
            dst[(j+3)*dim+i+2] = src[(i+2)*dim+j+3];
            dst[(j+3)*dim+i+3] = src[(i+3)*dim+j+3];
        }
    }
*/