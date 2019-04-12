#include <semaphore.h>
#include <stdbool.h>
#define BUFFER_MAX_SIZE 10

typedef struct {
    int data[BUFFER_MAX_SIZE];
    int in;
    int out;
    int size;
} buffer_t;

void buffer_write(buffer_t *, int);
int buffer_read(buffer_t *);