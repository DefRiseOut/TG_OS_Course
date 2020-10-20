#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <string.h>

int main()
{
    int *ptr[10];
    for(int i = 0; i < 10; i++){
        ptr[i] = malloc(10*1024*1024);
        memset(ptr[i],0,10*1024*1024);
        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        printf("%l\n",usage.ru_maxrss);
        sleep(1);
    }
    return 0;
}
