#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>

int main(){
    
    int semd;
    int r;
    int v;

    semd = semget(KEY, 1, 0);
    struct sembuf sb;
    sb.sem_num = 0;
    
    printf("Trying to get in\n");
    
    
}
