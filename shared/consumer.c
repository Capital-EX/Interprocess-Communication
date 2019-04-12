#include "buffer.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#define MM_SIZE sizeof(buffer_t)

int main(void) {
    int sfd =  shm_open("/shared.mm", O_CREAT | O_RDWR, 0666);
    ftruncate(sfd, MM_SIZE);
    
    buffer_t * buf = (buffer_t *) mmap(NULL, MM_SIZE, PROT_WRITE, MAP_SHARED, sfd, 0);
    sem_t *mutex = sem_open("/mutex", O_CREAT | O_RDWR, 0666, 1); 
    sem_t *empty = sem_open("/empty", O_CREAT | O_RDWR, 0666, BUFFER_MAX_SIZE); 
    sem_t *full = sem_open("/full", O_CREAT | O_RDWR, 0666, 0); 
    FILE *file = fopen("consumer.txt", "w");

    for (int i = 0; i < 100; i++) {
        int x;
        sem_wait(full);
        sem_wait(mutex);
        
        x = buffer_read(buf);

        sem_post(mutex);
        sem_post(empty);

        fprintf(file, "%d\n", x);
    }

    fclose(file);
    sem_close(mutex);
    sem_close(empty);
    sem_close(full);

    shm_unlink("/mutex.sem");
    shm_unlink("/empty.sem");
    shm_unlink("/full.sem");
    shm_unlink("/shared.mm");
    return 0;
}