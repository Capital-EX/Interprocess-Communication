#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand(time(NULL));

    int fd[2];
    if (pipe(fd) == -1) 
        return -1;

    pid_t pid = fork();
    if (pid == 0) {
        int output;
        FILE *file = fopen("producer.txt", "w");

        close(fd[0]);
        for (int i = 0; i < 100; i++) {
            output = rand();
            write(fd[1], &output, sizeof(int));
            fprintf(generate, "%d\n", output);
        }
        fclose(file);
        close(fd[1]);
        wait(NULL);
    } else {
        FILE *file = fopen("consumer.txt", "w");
        int input = 0;

        close(fd[1]);
        while(read(fd[0], &input, sizeof(int)) != 0) {
            fprintf(consumed, "%d\n", input);
        }
        fclose(file);
        close(fd[0]);
    }
}