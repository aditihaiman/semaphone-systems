#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#define KEY 24601
#define SEG_SIZE 200

int main(int argc, char * argv[]) {

    int shmd;
    char * data;
    char input[3];
    
    if (strcmp(argv[1], "-c")==0) {
        shmd = shmget(KEY, SEG_SIZE, IPC_CREAT | 0644);
        data = shmat(shmd, 0, 0);
        
        printf("Created semaphore and shared memory\n");
        
 
    }

    if (strcmp(argv[1], "-r")==0) {
        printf("Removing semaphore\n");
        shmctl(shmd, IPC_RMID, 0);
        printf("Segment deleted\n");
    }
    
    if (strcmp(argv[1], "-v")==0) {
        printf("The story so far:\n%s\n", data);
    }

}
