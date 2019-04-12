#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <mqueue.h>
#include <unistd.h>
#include <fcntl.h>

#define MSG_EMPTY 0
#define MSG_NUMBER 1

void producer(mqd_t queue);
void consumer(mqd_t queue);
typedef struct { char type; int value; } message_t;
typedef union { message_t message; char buffer[sizeof(message_t)]; } packet_t;

int main(void) {
    struct mq_attr attr = {
        .mq_flags = 0,
        .mq_maxmsg = 10,
        .mq_msgsize = sizeof(message_t),
        .mq_curmsgs = 0,
    };
    mqd_t queue = mq_open("/mq_project", O_CREAT | O_RDWR, 0666, &attr);
    pid_t pid = fork();

    if (pid > 0) { producer(queue); }
    else { consumer(queue); }
}

void producer(mqd_t queue) {
    packet_t packet;
    FILE *f = fopen("producer.txt", "w");
    
    for (int i = 0; i < 100; i++) {
        packet.message.type = MSG_NUMBER;
        packet.message.value = rand();
        mq_send(queue, packet.buffer, sizeof(message_t), 0);
        fprintf(f, "%d\n", packet.message.value);
    }
    packet.message.type = MSG_EMPTY;
    mq_send(queue, packet.buffer, sizeof(message_t), 0);

    mq_close(queue);
    fclose(f);
    wait(NULL);
}

void consumer(mqd_t queue) {
    packet_t packet;
    FILE *f = fopen("consumer.txt", "w");

    mq_receive(queue, packet.buffer, sizeof(message_t), 0);
    while (packet.message.type != MSG_EMPTY) {
        fprintf(f, "%d\n", packet.message.value);
        mq_receive(queue, packet.buffer, sizeof(message_t), 0);
    }

    mq_close(queue);
    fclose(f);
    mq_unlink("/mq_project");
}