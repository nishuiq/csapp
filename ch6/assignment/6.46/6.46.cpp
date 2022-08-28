void convert(int *src, int N) {
    int i, j;

    for (i = 0; i <= N - 1; i++)
        for (j = 0; j <= N - 1; j++)
            src[j * N + i] = src[i * N + j] || src[j * N + i];
}

// ref https://www.cnblogs.com/liqiuhao/p/8009769.html
/*
与6.45 类似，也是用 k=i l=j 进行迭代，而 i、j 则是枚举块
注意到是邻接矩阵，则可以枚举对角线一半的内容，即让 j = i 开始以实现枚举一半
*/
#define B 16
void faster_col_convert(int *G, int dim)
{
    long limit = dim * dim;
    for (int i = 0; i < dim; i += B)
    {
        for (int j = i; j < dim; j += B)
        {
            /* Using blocking to improve temporal locality */
            for (int k = i; k < i+B; ++k)
            {
                for (int l = j; l < j+B; ++l)
                {
                    /* independent calculations */
                    int d = l*dim + k;
                    int s = k*dim + l;
                    if (s < limit && d < limit)
                    {
                        bool temp = G[d] || G[s];
                        G[d] = temp;
                        G[s] = temp;
                    }
                }
            }

        }
    }
}