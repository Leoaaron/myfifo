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

    for(int i=0;i<12;i++)
        myfifo_in(&fifo, str, strlen(str));
    
    unsigned int l = 0;
    char bbuf[256] = "";
    l = myfifo_out(&fifo, bbuf, sizeof(bbuf));
    printf("l=%d, data:%s\n", l, bbuf);
   
    myfifo_free(&fifo);
    return 0;
}
