#include <iostream>
using namespace std;

/*
A.因为sizeof返回无符号数，进行减法操作时返回无符号数，而无符号数显然>=0
B.
*/
void copy_int(int val, void *buf, int maxbtyes) {
    /* buggy
    if (maxbtyes - sizeof(val) >= 0)
        memcpy(buf, (void *) &val, sizeof(val));
    */

    /* solution 1 */
    // if (val < 0) return;
    // if ((unsigned) maxbtyes >= sizeof(val))
    //     memcpy(buf, (void *) &val, sizeof(val));

    /* solution 2 */
    if (maxbtyes >= (int) sizeof(val))
        memcpy(buf, (void *) &val, sizeof(val));
}

int main()
{
    int maxbytes = sizeof(int) * 10;
    void* buf = malloc(maxbytes);
    int val;

    val = 0x12345678;
    copy_int(val, buf, maxbytes);
    assert(*(int*)buf == val);

    val = 0xAABBCCDD;
    copy_int(val, buf, 0);
    assert(*(int*)buf != val);
    free(buf);
    return 0;
}