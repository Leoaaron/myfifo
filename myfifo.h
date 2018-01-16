#ifndef _MYFIFO_H
#define _MYFIFO_H
struct myfifo{
    unsigned int in;
    unsigned int out;
    unsigned int esize;
    unsigned int len;
    void *data;
};


#define min(x,y) ((x)>(y)?(y):(x))

extern unsigned int myfifo_alloc(struct myfifo *fifo, unsigned int size);
extern void myfifo_free(struct myfifo *fifo);
extern unsigned int myfifo_in(struct myfifo *fifo, void *data, unsigned int len);
extern unsigned int myfifo_out(struct myfifo *fifo, void *data, unsigned int len);
extern int myfifo_is_empty(struct myfifo *fifo);
extern int myfifo_is_full(struct myfifo *fifo);

#endif
