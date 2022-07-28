#include <iostream>
using namespace std;

/*
double（52位小数）可容下int
float（23位小数）容不下int

A. (float) x == (float) dx 
    总为真，不管如何，最终都转化成float，同样的精度同样损失

B. dx - dy == (double) (x - y) 
    不总为真，当 y = INT_MIN， x-y 溢出

C. (dx + dy) + dz == dx + (dy + dz) 
    总为真，不会溢出

D. (dx * dy) * dz == dx * (dy * dz) 
    不总为真，只要求值超过2^54就会出现四舍五入

E. dx/dx == dz/dz
    不总为真
    当 dx = 0， dz = 1
    dx/dx = NAN
*/

int D(double x, double y, double z) {
    return (x * y) * z == x * (y * z);
}

int main()
{
    /* Create some arbitrary values */
    int x = (1 << 30) + 1;
    int y = (1 << 23) + 1;
    int z = 4444;
    double dx = (double)x;
    double dy = (double)y;
    double dz = (double)z;

    cout << D(dx, dy, dz) << endl;
}