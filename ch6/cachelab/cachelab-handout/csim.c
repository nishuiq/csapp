#include "cachelab.h"
#include <string.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ref https://github.com/Exely/CSAPP-Labs/blob/master/notes/cachelab.md
// ref https://zhuanlan.zhihu.com/p/28585726
#define IDX(m, n, E) m * E + n

char input[30];
int hits, misses, evictions;  // 命中、不命中、驱逐

struct Cache
{
    int valid;
    int tag;
    int count;  // 时间标记，数值越小表示距上次访问时间很久
};

int Atoi(char *s) {
    int res = 0;
    int n = strlen(s);
    for (int i = 0; i < n; i ++)
        res = res * 10 +( s[i] - '0');
    return res;
}

int hex2dec(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return 10 + c - 'A';
    if (c >= 'a' && c <= 'z') return 10 + c - 'a';
    return 0;
}

// 因为要求不能有任何Warning，所以干脆就把参数加上了，当然也可以干脆从一开始就不创建变量
void load(int tag, int groupidx, int offset, struct Cache* cache, int E, int count, int B, int size) {
    for (int i = 0; i < E; i ++) {  // 在该组中，枚举行
        if (cache[IDX(groupidx, i, E)].valid && cache[IDX(groupidx, i, E)].tag == tag) {
            cache[IDX(groupidx, i, E)].count = count;
            hits ++;
            return;
        }
    }

    misses ++;  // 没找到，则尝试找出无效位替换
    for (int i = 0; i < E; i ++) {
        if (cache[IDX(groupidx, i, E)].valid == 0) {
            cache[IDX(groupidx, i, E)].valid = 1;
            cache[IDX(groupidx, i, E)].tag = tag;
            cache[IDX(groupidx, i, E)].count = count;
            return;
        }
    }

    evictions ++;  // 需要用LRU找出最近最久的替换掉
    int min_idx = 0, min_cnt = 1e9;
    for (int i = 0; i < E; i ++) {
        if (cache[IDX(groupidx, i, E)].count < min_cnt) {
            min_cnt = cache[IDX(groupidx, i, E)].count;
            min_idx = i;
        }
    }

    cache[IDX(groupidx, min_idx, E)].valid = 1;
    cache[IDX(groupidx, min_idx, E)].tag = tag;
    cache[IDX(groupidx, min_idx, E)].count = count;
}


int main(int argc, char *argv[])
{
    int s, S, E, b, B;
    FILE *fp;
    for (int i = 1; i < argc; i ++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 's') {
                s = Atoi(argv[++i]);
                S = 1 << s;
            }
            else if (argv[i][1] == 'E') {
                E = Atoi(argv[++i]);
            }
            else if (argv[i][1] == 'b') {
                b = Atoi(argv[++i]);
                B = 1 << b;
            }
            else if (argv[i][1] == 't') {
                fp = fopen(argv[++i], "r");
            }
        }
    }
    struct Cache *cache = (struct Cache*)malloc(sizeof(struct Cache) * S * E);  // sizeof(struct Cache)
    for (int i = 0; i < S * E; i ++)
    {
        cache[i].valid = 0;
        cache[i].tag = 0;
        cache[i].count = 0;
    }

    int count = 0;  // 时间标记

    while (fgets(input, 30, fp)) {
        int op = 0;
        char c;
        int flag = 0;

        long address = 0;  // address = [Tag][groupidx][offset]
        int tag = 0;
        int groupidx = 0;
        int offset = 0;  // 实际模拟不会用到
        int size = 0;  // 实际模拟不会用到
        count ++;  // 当前时间点

        for (int i = 0; (c = input[i]) && (c != '\n'); i ++) {
            if (c == ' ') continue;
            if (c == 'I') op = 0;  // 忽略指令
            else if (c == 'L' || c == 'S') op = 1;  // 加载和存储
            else if (c == 'M') op = 2;  // 修改
            else if (c == ',') flag = 1;
            else {
                if (flag) size = hex2dec(c);
                else address = address*16 + hex2dec(c);  // 地址是64-bits
            }
        }
        // 这里看起来是把它倒转了，例如原本[100]，变成了[001]，只是改变了解释，并不影响
        // offset 我们实际上并不会使用到
        for (int i = 0; i < b; i ++) {
            offset = (offset << 1) + (address & 1);
            // offset = offset*2 + address % 2;
            address >>= 1;
        }
        for (int i = 0; i < s; i ++) {
            // groupidx = groupidx*2 + address % 2;
            groupidx = (groupidx << 1) + (address & 1);
            address >>= 1;
        }
        tag = address;
        if (op == 1) load(tag, groupidx, offset, cache, E, count, B, size);
        else if (op == 2) {
            load(tag, groupidx, offset, cache, E, count, B, size);
            hits ++;
        }
    }
    fclose(fp);
    free(cache);
    printSummary(hits, misses, evictions);
    return 0;
}