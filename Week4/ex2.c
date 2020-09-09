#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{   
    int pid;
    for(int i = 0; i<5; ++i){
        pid = fork();
    }
    sleep(5);
    return 0;
}
