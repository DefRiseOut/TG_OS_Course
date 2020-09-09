#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>


int main() {
    int n;
    n = fork();
    if(n != 0){
        printf("Hello from parent ");
        printf("%d\n", getpid() - n);
    }
    else{
        sleep(0.4);
        printf("Hello from child ");
        printf("%d\n", getpid() - n);
        exit(0);
    }
    sleep(0.4);
    return 0;
}

