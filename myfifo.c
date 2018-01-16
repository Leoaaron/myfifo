
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include"myfifo.h"

unsigned int myfifo_alloc(struct myfifo *fifo, unsigned int size)
{
    if(!fifo)
        return -EINVAL;
    if(size < 2)
        return -EINVAL;

    fifo->in = 0;
    fifo->out = 0;
    fifo->esize = 1;
    fifo->data = malloc(fifo->esize * size);
    if(!fifo->data)
        return -ENOMEM;

    fifo->len = size;
    return size;
}


void myfifo_free(struct myfifo *fifo)
{
    free(fifo->data);
    fifo->len = 0;
    fifo->data = NULL;
}


inline static unsigned int myfifo_use(struct myfifo *fifo)
{

    return fifo->in - fifo->out;
}


inline static unsigned int myfifo_unuse(struct myfifo *fifo)
{    
    return fifo->len - myfifo_use(fifo);
}


static void copy_to_fifo(struct myfifo *fifo, void *data, unsigned int len, unsigned int off)
{
    off %= fifo->len;
    unsigned int l = fifo->len - off;
    l = min(l,len);

    memcpy(fifo->data+off, data, l);
    memcpy(fifo->data, data+l, len - l);
}


unsigned int myfifo_in(struct myfifo *fifo, void *data, unsigned int len)
{
    if(!fifo || !data || !len)
        return 0;

    unsigned int l = myfifo_unuse(fifo);
    if(len > l)
        len = l;

    copy_to_fifo(fifo, data, len, fifo->in);
    fifo->in += len;

    return len;
}


static void copy_from_fifo(struct myfifo *fifo, void *data, unsigned int len, unsigned int off)
{
    off %= fifo->len;
    unsigned int l = fifo->len - off;
    l = min(l, len);
    
    memcpy(data, fifo->data+off, l);
    memcpy(data+l, fifo->data, len - l);
}


unsigned int myfifo_out(struct myfifo *fifo, void *data, unsigned int len)
{
    if(!fifo || !data || !len)
        return 0;
    
    unsigned int l = myfifo_use(fifo);
    if(len > l)
        len = l;

    copy_from_fifo(fifo, data, len, fifo->out);
    fifo->out += len;

    return len;
}
