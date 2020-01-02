#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/shm.h>
#include <fcntl.h>

#define KEY 24601
#define SEG_SIZE 200

int main(int argc, char * argv[]) {

    int fd;
    int n;
    char buff[100];
    
    int shmd;
    char * data;
    char input[3];
    
    int semd;
    int v, r;
    
    if (strcmp(argv[1], "-c")==0) {
        shmd = shmget(KEY, SEG_SIZE, IPC_CREAT | 0644);
        data = shmat(shmd, 0, 0);
        printf("Created shared memory\n");
        semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
        printf("Created semaphore\n");
        fd = open("semaphone.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
        printf("Created file\n");
 
    }

    if (strcmp(argv[1], "-r")==0) {
        printf("The story so far:\n");
        fd = open("semaphone.txt", O_RDONLY);
        read(fd, buff, 100);
        printf("%s\n", buff);
        shmctl(shmd, IPC_RMID, 0);
        printf("Segment deleted\n");
        semctl(semd, IPC_RMID, 0);
        printf("Semaphore deleted\n");
    }
    
    if (strcmp(argv[1], "-v")==0) {
        printf("The story so far:\n");
        fd = open("semaphone.txt", O_RDONLY);
        read(fd, buff, 100);
        printf("%s\n", buff);
    }

}
