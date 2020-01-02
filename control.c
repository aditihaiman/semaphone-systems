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

#define SHMKEY 24601
#define SEMKEY 24602
#define SEG_SIZE 200

int main(int argc, char * argv[]) {

    int fd;
    int n;
    char buff[100];
    
    int shmd;
    char * data;
    
    int semd;
    int v, r;
    
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = -1;
    
    if (strcmp(argv[1], "-c")==0) {
        shmd = shmget(SHMKEY, SEG_SIZE, IPC_CREAT | 0644);
        data = shmat(shmd, 0, 0);
        printf("Created shared memory\n");
        semd = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
        printf("Created semaphore\n");
        fd = open("semaphone.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
        printf("Created file\n");
 
    }

    if (strcmp(argv[1], "-r")==0) {
        semd = semget(SEMKEY, 1, 0);
        semop(semd, &sb, 1);
        shmd = shmget(SHMKEY, SEG_SIZE, 0);
        printf("The story so far:\n");
        fd = open("semaphone.txt", O_RDONLY);
        read(fd, buff, 100);
        printf("%s\n", buff);
        shmctl(shmd, IPC_RMID, 0);
        printf("Segment deleted\n");
        semctl(semd, IPC_RMID, 0);
        printf("Semaphore deleted\n");
        remove("semaphone.txt");
        printf("File deleted\n");
    }
    
    if (strcmp(argv[1], "-v")==0) {
        printf("The story so far:\n");
        fd = open("semaphone.txt", O_RDONLY);
        read(fd, buff, 100);
        printf("%s\n", buff);
    }
    
    return 0;

}
