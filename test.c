#include<stdio.h>
#include "myfifo.h"

int main(int argc, char *argv[])
{
    struct myfifo fifo;
    unsigned int len = myfifo_alloc(&fifo,128);
    if(len <= 0){
        printf("len =%d\n", len);
        return -1;
    }

    char str[] = "hello world";
    if(myfifo_in(&fifo, str, sizeof(str)))
        printf("write to myfifo :%s\n", str);

    char buf[64] = "";
    myfifo_out(&fifo, buf, sizeof(buf));
    printf("read from myfifo :%s\n", buf);

    return 0;
}
