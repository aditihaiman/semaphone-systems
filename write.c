#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/shm.h>

#define SHMKEY 24601
#define SEMKEY 24602
#define SEG_SIZE 200

int main(){
    
    int fd;
    int n;
    char buff[100];
    
    int shmd;
    char * data;
    char input[3];
    
    int semd;
    int v, r;

    
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = -1;
    printf("Trying to get in\n");
    semd = semget(SEMKEY, 1, 0);
    semop(semd, &sb, 1);
    shmd = shmget(SHMKEY, SEG_SIZE, 0);
    fd = open("semaphone.txt", O_WRONLY | O_APPEND);
    
    data = shmat(shmd, 0, 0);
    printf("Last addition: %s\n", data);
    
    printf("Your new addition: ");
    fgets(buff, sizeof(buff), stdin);
    write(fd, buff, sizeof(buff));
    strcpy(data, buff);
    shmdt(data);
    sb.sem_op = 1;
    semop(semd, &sb, 1);
    
    return 0;
    
}
