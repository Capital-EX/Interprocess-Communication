#include "buffer.h"

void buffer_write(buffer_t *buffer, int value) {
    buffer->data[buffer->in] = value;
    buffer->in = (buffer->in + 1) % BUFFER_MAX_SIZE;
    buffer->size = buffer->size + 1;
}

int buffer_read(buffer_t *buffer) {
    int value = buffer->data[buffer->out];
    buffer->out = (buffer->out + 1) % BUFFER_MAX_SIZE;
    buffer->size = buffer->size - 1;
    return value;
}