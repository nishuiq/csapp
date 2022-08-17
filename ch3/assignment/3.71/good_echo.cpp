#include <iostream>
using namespace std;

#define buf_size 20

void good_echo() {
    char buf[buf_size];
    while (!feof(stdin)) {
        if (fgets(buf, buf_size, stdin) == NULL)
            return;
        fputs(buf, stdout);
    }
}

int main()
{
    good_echo();
    return 0;
}

2-3年 78w