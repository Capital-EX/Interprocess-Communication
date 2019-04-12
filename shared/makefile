buffer.o: buffer.c
    gcc -Wall -c buffer.c

consumer.o: consumer.c
    gcc -Wall -c consumer.c

producer.o: producer.c
    gcc -Wall -c producer.c

build: buffer.o consumer.o producer.o
    gcc -o consumer consumer.o buffer.o -lrt -pthread 
    gcc -o producer producer.o buffer.o -lrt -pthread 

clean:
    rm -f *.o consumer producer