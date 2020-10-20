#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


//Value of the occupied memory(both vitrual and physical) increased over the course of 10 seconds, then returned to normal 87.
int main()
{
    int *ptr[10];
    for(int i = 0; i < 10; i++){
        ptr[i] = malloc(10*1024*1024);
        memset(ptr[i],0,10*1024*1024);
        sleep(1);
    }
    return 0;
}
